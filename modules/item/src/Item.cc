#include "Item.hh"
#include <stdexcept>

namespace knapsack
{
Item::Item(const price_t price, const weight_t weight) : price_{price}, weight_{weight}
{
}

Item::ratio_t Item::costEffectivenessRatio() const
{
    if (weight_ == 0.0)
    {
        throw std::invalid_argument("");
    }
    return price_ / weight_;
}

bool Item::operator==(const Item &item) const
{
    return (costEffectivenessRatio() == item.costEffectivenessRatio());
}

bool Item::operator!=(const Item &item) const
{
    return not(*this == item);
}

bool Item::operator<(const Item &item) const
{
    return (costEffectivenessRatio() < item.costEffectivenessRatio());
}

bool Item::operator>(const Item &item) const
{
    return (costEffectivenessRatio() > item.costEffectivenessRatio());
}

bool Item::operator<=(const Item &item) const
{
    return (costEffectivenessRatio() <= item.costEffectivenessRatio());
}

bool Item::operator>=(const Item &item) const
{
    return (costEffectivenessRatio() >= item.costEffectivenessRatio());
}

} // namespace knapsack