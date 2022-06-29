#include "TabuSearch.hh"
#include "Bin.hh"
#include "Item.hh"
#include <iostream>
#include <queue>
#include <random>
namespace knapsack::algorithm
{
TabuSearch::TabuSearch(const std::size_t iteration, Bin &bin, const items_t &items)
    : iteration_{iteration}, bin_{bin}, items_{items}
{
    prepareItems(items_, bin_.capacity(), random);
}

void TabuSearch::objectiveFunction()
{
}

void quickRemoveItemFromList(items_t &items, const std::size_t idx)
{
    if (idx < items.size())
    {
        items[idx] = std::move(items.back());
        items.pop_back();
    }
}

auto shuffleSndRemoveShuffledItem(items_t &items)
{
    thread_local std::mt19937_64 engine;
    const auto amountOfItems = items.size() - 1;
    std::uniform_int_distribution<std::mt19937_64::result_type> dist(0, amountOfItems);
    const auto startIndex = dist(engine);
    items.at(startIndex);
    return items.erase(std::begin(items) + static_cast<long long int>(startIndex));
}

auto getNeighbourOnLeftAndRight(items_t &items, std::vector<Item>::iterator &it,
                                std::queue<Item> &tabu)
{
    auto leftNeighbourItr = it - 1;
    auto rightNeighbourItr = it + 1;
    if (leftNeighbourItr == std::begin(items))
    {
        items.push_back(tabu.front());
        tabu.pop();
    }
    if (rightNeighbourItr == std::end(items))
    {
        items.push_back(tabu.front());
        tabu.pop();
    }
}

void TabuSearch::solve()
{
    for (std::size_t it{0}; it < iteration_; ++it)
    {
        std::queue<Item> tabuList;
        auto copy = items_;
        auto current = Bin(bin_.weight());
        for (auto itr = shuffleSndRemoveShuffledItem(copy); itr != copy.end();)
        {
        }
        if (current.value() > bin_.value())
        {
            bin_ = current;
        }
    }
}
} // namespace knapsack::algorithm