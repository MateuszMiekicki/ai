#include "Item.hh"
#include <random>
#include <stdexcept>

namespace knapsack
{
Item::Item(const Value value, const Weight weight) : value_{value}, weight_{weight}
{
}

Ratio Item::costEffectivenessRatio() const
{
    if (weight_.value == 0.0L)
    {
        throw std::invalid_argument("The weight must not be zero");
    }
    return {value_.value / weight_.value};
}

Value Item::value() const
{
    return value_;
}

Weight Item::weight() const
{
    return weight_;
}

bool operator==(const Item &lhs, const Item &rhs)
{
    return (lhs.weight() == rhs.weight()) and (lhs.value() == rhs.value());
}

bool operator<(const Item &lhs, const Item &rhs)
{
    return (lhs.costEffectivenessRatio() < rhs.costEffectivenessRatio());
}

bool operator>(const Item &lhs, const Item &rhs)
{
    return (lhs.costEffectivenessRatio() > rhs.costEffectivenessRatio());
}

void removeItemsLargerThanCapacity(items_t &items, const Weight &binCapacity)
{
    const auto iteratorForFirstLargerItemThanCapacity =
        std::remove_if(std::begin(items), std::end(items),
                       [&binCapacity](const auto &item) { return item.weight() > binCapacity; });
    items.erase(iteratorForFirstLargerItemThanCapacity, std::end(items));
}

void prepareItems(items_t &items, const Weight &binCapacity,
                  const std::function<void(items_t &)> &function)
{
    knapsack::removeItemsLargerThanCapacity(items, binCapacity);
    function(items);
}

void deterministic(items_t &items)
{
    std::sort(std::begin(items), std::end(items), std::greater<knapsack::Item>());
}

void random(items_t &items)
{
    std::random_device rd;
    thread_local std::mt19937 g(rd());
    std::shuffle(items.begin(), items.end(), g);
}
} // namespace knapsack