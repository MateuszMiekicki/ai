#include "HillClimbing.hh"
#include "Bin.hh"
#include "Item.hh"
#include <algorithm>
#include <execution>
#include <iostream>
#include <mutex>
#include <numeric>
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

//auto random(const std::size_t min, const std::size_t max)
//{
//    // todo: max, change range to random
//    std::uniform_int_distribution<std::mt19937_64 ::result_type> dist(min, max);
//    return dist(randomEngine());
//}

//auto random(const std::size_t min, const std::size_t max, const std::size_t count)
//{
//    std::unordered_set<std::size_t> selected;
//    while (selected.size() < count)
//    {
//        selected.insert(random(min, max));
//    }
//    return std::vector(std::begin(selected), std::end(selected));
//}

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
using gene_t = std::pair<bool, knapsack::Item>;
using chromosome_t = std::vector<gene_t>;
auto toChromosome = [](const knapsack::items_t &itemsToConvert) {
    auto tempChromosome = chromosome_t();
    tempChromosome.reserve(itemsToConvert.size());
    for (const auto item : itemsToConvert)
    {
        tempChromosome.emplace_back(false, item);
    }
    return tempChromosome;
};

void mutation(chromosome_t &chromosome)
{
    for (auto &gene : chromosome)
    {
        gene.first = (drawProbability() <= 0.01L) ? (not gene.first) : gene.first;
    }
}

} // namespace
namespace knapsack::algorithm
{
HillClimbing::HillClimbing(Bin &bin, const items_t &items, const Parameters &parameters)
    : bin_{bin}, items_{items}, parameters_{parameters}
{
}

void HillClimbing::objectiveFunction()
{
    Bin current{bin_.capacity()};
    current.fill(items_);
    if (bin_.value() < current.value())
    {
        bin_ = current;
    }
}

void HillClimbing::solve()
{
    auto chromosome = toChromosome(items_);
    auto bestChromosome = chromosome;
    do
    {
        mutation(chromosome);
        if (bin_.capacity() >= weight(chromosome))
        {
            if (value(bestChromosome) < value(chromosome))
            {
                bestChromosome = chromosome;
            }
        }
    } while (static_cast<bool>(--parameters_.iteration));
    std::cerr << "\n value " << value(bestChromosome) << ' ' << weight(bestChromosome) << std::endl;
}
} // namespace knapsack::algorithm