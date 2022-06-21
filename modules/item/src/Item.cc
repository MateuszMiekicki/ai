#include "Item.hh"
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

bool Item::operator==(const Item &item) const
{
    return (costEffectivenessRatio() == item.costEffectivenessRatio());
}


bool Item::operator<(const Item &item) const
{
    return (costEffectivenessRatio() < item.costEffectivenessRatio());
}

bool Item::operator>(const Item &item) const
{
    return (costEffectivenessRatio() > item.costEffectivenessRatio());
}


Value Item::getValue() const
{
    return value_;
}

Weight Item::getWeight() const
{
    return weight_;
}
} // namespace knapsack