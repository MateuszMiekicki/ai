#include "Genetic.hh"
#include "Bin.hh"
#include "Item.hh"
#include <algorithm>
#include <execution>
#include <iostream>
#include <mutex>
#include <random>
#include <unordered_set>

namespace
{
auto &randomEngine()
{
    std::random_device randomDevice;
    thread_local std::mt19937_64 engine(randomDevice());
    return engine;
}

auto random(const std::size_t min, const std::size_t max)
{
    // todo: max, change range to random
    std::uniform_int_distribution<std::mt19937_64 ::result_type> dist(min, max);
    return dist(randomEngine());
}

auto random(const std::size_t min, const std::size_t max, const std::size_t count)
{
    std::unordered_set<std::size_t> selected;
    while (selected.size() < count)
    {
        selected.insert(random(min, max));
    }
    return selected;
}

auto drawProbability()
{
    std::uniform_real_distribution<long double> uniformRealDistribution(0.0L, 1.0L);
    return (uniformRealDistribution(randomEngine()));
}

auto value = [](const auto &chromosome) {
    return std::accumulate(std::cbegin(chromosome), std::cend(chromosome), knapsack::Value{0},
                           [](const auto &lhs, const auto &rhs) {
                               return lhs + (rhs.first ? rhs.second.value() : knapsack::Value{0});
                           });
};

auto weight = [](const auto &chromosome) {
    return std::accumulate(std::cbegin(chromosome), std::cend(chromosome), knapsack::Weight{0},
                           [](const auto &lhs, const auto &rhs) {
                               return lhs + (rhs.first ? rhs.second.weight() : knapsack::Weight{0});
                           });
};
} // namespace

namespace knapsack::algorithm
{
Genetic::Genetic(Bin &bin, const items_t &items, const Parameters &parameters)
    : bin_{bin}, items_{items}, parameters_{parameters}

{
    prepareItems(items_, bin_.capacity(), random);
}

Genetic::chromosome_t Genetic::generateChromosome(const items_t &items,
                                                  const std::size_t amountOfGenes) const
{
    auto chromosome = [](const items_t &itemsToConvert) {
        auto tempChromosome = chromosome_t();
        tempChromosome.reserve(itemsToConvert.size());
        for (const auto item : itemsToConvert)
        {
            tempChromosome.emplace_back(false, item);
        }
        return tempChromosome;
    }(items);

    for (auto &&index : ::random(0, amountOfGenes, ::random(0, amountOfGenes)))
    {
        chromosome.at(index).first = true;
    }
    return chromosome;
}

Genetic::population_t Genetic::generatePopulation(const items_t &items) const
{
    auto population = population_t();
    population.reserve(parameters_.amountOfChromosomes.value());
    for (auto i{parameters_.amountOfChromosomes.value()}; i not_eq 0; --i)
    {
        population.emplace_back(generateChromosome(items, ::random(0, items.size() - 1)));
    }
    return population;
}

void Genetic::removeWeakest(population_t &population) const
{
    std::nth_element(std::execution::par, std::begin(population), std::begin(population) + 1,
                     std::end(population),
                     [](const auto &lhs, const auto &rhs) { return value(lhs) < value(rhs); });
    population = population_t(population.begin() + 2, population.end());
}

Genetic::population_t Genetic::generatePopulation(population_t population) const
{
    //    fitness(population);
    auto parents = selection(population, rankingMethod);
    parents = evolutionOperator(parents, onePointCrossover);
    mutation(parents);
    population.push_back(parents.first);
    population.push_back(parents.second);
    removeWeakest(population);
    //        fitness(population);
    return population;
}

void Genetic::removeOverWeightGene(population_t &population) const
{
    population.erase(
        std::remove_if(std::execution::par, std::begin(population), std::end(population),
                       [this](auto chromosome) { return (weight(chromosome) > bin_.capacity()); }),
        std::end(population));
}

Genetic::parents_t Genetic::selection(population_t population,
                                      const selectionMethod_t &selectionMethod) const
{
    return selectionMethod(population);
}

Genetic::parents_t Genetic::rankingMethod(population_t population)
{
    std::nth_element(std::begin(population), std::begin(population) + 1, std::end(population),
                     [](const auto &lhs, const auto &rhs) { return value(lhs) > value(rhs); });
    return {population.at(0), population.at(1)};
}

Genetic::chromosome_t Genetic::fitness(const Genetic::population_t &population) const
{
    std::mutex m;
    auto bestChromosome = chromosome_t();
    auto bestValue = Value{0};
    std::for_each(
        std::execution::par, std::begin(population), std::end(population), [&](auto &&chromosome) {
            std::lock_guard<std::mutex> guard(m);
            if (const auto currentWeight = weight(chromosome); currentWeight <= bin_.capacity())
            {
                if (const auto currentValue = value(chromosome); currentValue > bestValue)
                {
                    bestValue = currentValue;
                    bestChromosome = chromosome;
                }
            }
        });

    return bestChromosome;
}

Genetic::parents_t Genetic::evolutionOperator(parents_t parents,
                                              const evolutionMethod_t &evolutionMethod) const
{
    return evolutionMethod(parents);
}

Genetic::parents_t Genetic::onePointCrossover(parents_t parents)
{
    for (auto i = ::random(0, parents.first.size() - 1); i not_eq 0; --i)
    {
        std::swap(parents.first.at(i), parents.second.at(i));
    }
    return {parents.first, parents.second};
}

Genetic::parents_t Genetic::uniformCrossover(parents_t parents)
{
    for (std::size_t i{0}; i < parents.first.size(); ++i)
    {
        if (drawProbability() > 0.5L)
        {
            std::swap(parents.first.at(i), parents.second.at(i));
        }
    }
    return parents;
}

void Genetic::mutation(chromosome_t &chromosome) const
{
    for (auto &gene : chromosome)
    {
        gene.first = (drawProbability() <= parameters_.probabilityOfMutation.value())
                         ? (not gene.first)
                         : gene.first;
    }
}

void Genetic::mutation(parents_t &parents) const
{
    mutation(parents.first);
    mutation(parents.second);
}

void Genetic::solve()
{
    auto population = generatePopulation(items_);
    auto bestChromosome = chromosome_t{};
    auto pmcounter = 0;
    for (auto i{parameters_.iteration}; i not_eq 0; --i)
    {
        auto currentBestChromosome = fitness(population);
        if (value(bestChromosome) == value(currentBestChromosome))
        {
            pmcounter++;
            if (pmcounter == std::round(parameters_.iteration * 0.5L))
            {
                std::cerr << "iteracja " << i;
                break;
            }
            continue;
        }
        if (value(currentBestChromosome) > value(bestChromosome))
        {
            bestChromosome = currentBestChromosome;
        }
        population = generatePopulation(population);
    }
    auto itemsForBin = [](auto &&best) {
        auto items = items_t();
        for (auto &&chromosome : best)
        {
            if (chromosome.first)
            {
                items.emplace_back(chromosome.second);
            }
        }
        return items;
    }(bestChromosome);
    bin_ = Bin(bin_.weight(), itemsForBin);
}
} // namespace knapsack::algorithm