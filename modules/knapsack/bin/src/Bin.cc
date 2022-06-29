#include "Bin.hh"
#include "Item.hh"
#include <numeric>

namespace knapsack
{
Bin::Bin(const Weight &capacity, const items_t &items) : items_{items}, capacity_{capacity}
{
}

Bin::Bin(const Weight &capacity) : Bin(capacity, {})
{
}

bool Bin::isFits(const Item &item) const
{
    return ((weight() + item.weight()) <= capacity());
}
// ToDo: refactoring, adding a function that simply fills the backpack, add fill if it fits
void Bin::fill(const items_t &items)
{
    std::for_each(items.cbegin(), items.cend(), [this](const auto &item) {
        if (isFits(item))
        {
            items_.push_back(item);
        }
    });
}

Value Bin::value() const
{
    return std::accumulate(items_.cbegin(), items_.cend(), Value{0},
                           [](const auto &lhs, const auto &rhs) { return lhs + rhs.value(); });
}

Weight Bin::weight() const
{
    return std::accumulate(items_.cbegin(), items_.cend(), Weight{0},
                           [](const auto &lhs, const auto &rhs) { return lhs + rhs.weight(); });
}
Weight Bin::capacity() const
{
    return capacity_;
}

void Bin::add(const Item &item)
{
    items_.emplace_back(item);
}

items_t Bin::items() const
{
    return items_;
}
} // namespace knapsack