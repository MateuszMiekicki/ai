#ifndef KNAPSACK_ITEM_HH
#define KNAPSACK_ITEM_HH
#include "Decimal.hh"

namespace knapsack
{
class Item
{
  private:
    Value value_;
    Weight weight_;

  public:
    Item(const Value value, const Weight weight);

    Ratio costEffectivenessRatio() const;

    bool operator==(const Item &item) const;
    bool operator!=(const Item &item) const;

    bool operator<(const Item &item) const;
    bool operator>(const Item &item) const;

    bool operator<=(const Item &item) const;
    bool operator>=(const Item &item) const;

    Value getValue() const;
    Weight getWeight() const;
};
} // namespace knapsack

#endif // KNAPSACK_ITEM_HH
