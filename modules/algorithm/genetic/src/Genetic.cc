#include "Genetic.hh"
#include "Bin.hh"
#include "Item.hh"
#include <algorithm>
#include <random>

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
    std::uniform_int_distribution<std::mt19937_64 ::result_type> dist(min, max);
    return dist(randomEngine());
}
} // namespace

namespace knapsack::algorithm
{
Genetic::Genetic(Bin &bin, const items_t &items, const Parameters &parameters)
    : bin_{bin}, items_{items}, parameters_{parameters}

{
}

Genetic::population_t Genetic::generatePopulations(const population_t &population) const
{
    auto newPopulation = population_t();
    newPopulation.reserve(parameters_.amountOfChromosomes.value().value);
    for (auto i{parameters_.amountOfChromosomes.value().value / 2}; i not_eq 0; --i)
    {
        auto &&[first, second] = tournamentSelection(population);

    }
}

Genetic::chromosome_t Genetic::crossover(const chromosome_t &first, const chromosome_t &second) const
{

}


Genetic::population_t Genetic::generateInitialPopulations(const items_t &items) const
{
    auto population = population_t();
    population.reserve(parameters_.amountOfChromosomes.value().value);
    for (auto i{parameters_.amountOfChromosomes.value().value}; i not_eq 0; --i)
    {
        auto chromosome = chromosome_t();
        const auto amountOfGenes{::random(0, items.size())};
        std::sample(std::begin(items), std::end(items), std::back_inserter(chromosome),
                    amountOfGenes, randomEngine());
        population.emplace_back(std::move(chromosome));
    }
    return population;
}

void Genetic::selection(population_t &population) const
{
    population.erase(std::remove_if(std::begin(population), std::end(population),
                                    [this](auto &&chromosome) {
                                        return Bin(bin_.capacity(), chromosome).value() >
                                               bin_.capacity();
                                    }),
                     std::end(population));
}

Genetic::pairParents_t Genetic::drawTwoPairsOfParents(const population_t &population) const
{
    auto populationForTournament = population_t();
    std::sample(std::cbegin(population), std::cend(population),
                std::back_inserter(populationForTournament), 4, randomEngine());

    return {{populationForTournament.at(0), populationForTournament.at(1)},
            {populationForTournament.at(2), populationForTournament.at(3)}};
}

Genetic::parrents_t Genetic::evaluateParentPair(const Genetic::pairParents_t &pairParents) const
{
    const auto capacity = bin_.capacity();
    const auto firstChromosomeValue = Bin(capacity, pairParents.first.first).value();
    const auto secondChromosomeValue = Bin(capacity, pairParents.first.second).value();

    const auto thirdChromosomeValue = Bin(capacity, pairParents.second.first).value();
    const auto fourthChromosomeValue = Bin(capacity, pairParents.second.second).value();

    return {{firstChromosomeValue > secondChromosomeValue ? pairParents.first.first
                                                          : pairParents.first.second},
            {thirdChromosomeValue > fourthChromosomeValue ? pairParents.second.first
                                                          : pairParents.second.second}};
}

Genetic::parrents_t Genetic::tournamentSelection(const population_t &population) const
{
    if (4 > population.size())
    {
        return {population.at(0), population.at(1)};
    }
    return evaluateParentPair(drawTwoPairsOfParents(population));
}

void Genetic::solve()
{
    auto initialGeneration = generateInitialPopulations(items_);
    for (auto i{parameters_.iteration}; i not_eq 0; --i)
    {
        initialGeneration = generatePopulations(initialGeneration);
    }
}
} // namespace knapsack::algorithm