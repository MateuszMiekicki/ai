#include "Knapsack.hh"
#include "Item.hh"
#include <algorithm>
#include <numeric>

namespace knapsack
{
Knapsack::Knapsack(const Weight &capacity, const items_t &items)
    : items_{items}, capacity_{capacity}
{
}

Knapsack::Knapsack(const Weight &capacity) : Knapsack(capacity, {})
{
}

void Knapsack::addItem(const Item &item)
{
    items_.push_back(item);
}

void Knapsack::removeItem(const std::size_t index)
{
    auto it = items_.begin();
    std::advance(it, index);
    items_.erase(it);
}

Value Knapsack::value() const
{
    return std::accumulate(items_.cbegin(), items_.cend(), Value{0},
                           [](const auto &lhs, const auto &rhs) { return lhs + rhs.getValue(); });
}

Weight Knapsack::weight() const
{
    return std::accumulate(items_.cbegin(), items_.cend(), Weight{0},
                           [](const auto &lhs, const auto &rhs) { return lhs + rhs.getWeight(); });
}
} // namespace knapsack