#include "Genetic.hh"
#include "Bin.hh"
#include "Item.hh"
#include <algorithm>
#include <iostream>
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
    std::random_device randomDevice;
    thread_local std::mt19937_64 engine(randomDevice());
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
} // namespace

namespace knapsack::algorithm
{
Genetic::Genetic(Bin &bin, const items_t &items, const Parameters &parameters)
    : bin_{bin}, items_{items}, parameters_{parameters}

{
}

Genetic::chromosome_t Genetic::generateDefaultListOfChromosomes(const items_t &items) const
{
    auto defaultChromosomeList = chromosome_t();
    defaultChromosomeList.reserve(items.size());
    std::for_each(std::cbegin(items), std::cend(items), [&defaultChromosomeList](const auto &gene) {
        defaultChromosomeList.emplace_back(false, gene);
    });
    return defaultChromosomeList;
}

Genetic::population_t Genetic::generateInitialPopulation(const items_t &items) const
{
    auto population = population_t();
    population.reserve(parameters_.amountOfChromosomes.value().value);
    const auto defaultListChromosome = generateDefaultListOfChromosomes(items);
    for (auto i{parameters_.amountOfChromosomes.value().value}; i not_eq 0; --i)
    {
        auto chromosome = defaultListChromosome;
        const auto max = chromosome.size() - 1;
        for (const auto &j : ::random(0, max, ::random(0, max)))
        {
            chromosome.at(j).first = true;
        }
        population.emplace_back(std::move(chromosome));
    }
    return population;
}

Genetic::parents_t Genetic::selectTwoRandomChromosomes(const population_t &population) const
{
    auto temp = population_t();
    std::sample(std::begin(population), std::end(population), std::back_inserter(temp), 2,
                randomEngine());
    return {temp.at(0), temp.at(1)};
}

Value Genetic::fitness(const chromosome_t &chromosome) const
{
    auto onlyChosenGenes = [this](const chromosome_t &chosen) {
        auto temp = items_t();
        for (const auto &[flag, gene] : chosen)
        {
            if (flag)
            {
                temp.push_back(gene);
            }
        }
        return temp;
    }(chromosome);
    Bin tempBin(bin_.capacity(), onlyChosenGenes);
    return (tempBin.weight() > bin_.capacity()) ? Value{0} : tempBin.value();
}

Genetic::chromosome_t Genetic::singlePointCrossover(const parents_t &parent) const
{
    auto chromosome1 = chromosome_t();
    auto chromosome2 = chromosome_t();
    auto max = parent.first.size();
    for (auto i = 0ULL; i < (max / 2); ++i)
    {
        chromosome1.push_back(parent.first.at(i));
        chromosome2.push_back(parent.first.at(max - i - 1));
    }
    for (auto i = max / 2; i < max; ++i)
    {
        chromosome1.push_back(parent.first.at(i));
        chromosome2.push_back(parent.second.at(max - i));
    }
    if (fitness(chromosome1) > fitness(chromosome2))
    {
        return chromosome1;
    }
    return chromosome2;
}

Genetic::population_t Genetic::generatePopulation(const population_t &population) const
{
    auto newPopulation = population;
    newPopulation.erase(
        std::remove_if(newPopulation.begin(), newPopulation.end(),
                       [this](const auto chromosome) { return fitness(chromosome) == 0; }));
    auto parents = selectTwoRandomChromosomes(newPopulation);
    for (auto i{parameters_.amountOfChromosomes.value().value}; i not_eq 0; --i)
    {
        newPopulation.emplace_back(singlePointCrossover(parents));
    }
    return newPopulation;
}

void Genetic::solve()
{
    auto temp = generateInitialPopulation(items_);

    for (auto i{parameters_.iteration}; i not_eq 0; --i)
    {
        temp=generatePopulation(temp);
    }
    Value v=0;
    for(auto i : temp)
    {
        if(auto f = fitness(i);v<f)
        {
            v=f;
        }
    }
    std::cerr<<"value"<<v.value;
}
} // namespace knapsack::algorithm