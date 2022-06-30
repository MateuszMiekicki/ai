#ifndef KNAPSACK_ITEM_HH
#define KNAPSACK_ITEM_HH
#include "Number.hh"
#include <functional>
#include <vector>

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

    Value value() const;
    Weight weight() const;
};

bool operator==(const Item &lhs, const Item &rhs);
bool operator<(const Item &lhs, const Item &rhs);
bool operator>(const Item &lhs, const Item &rhs);

using items_t = std::vector<Item>;
void removeItemsLargerThanCapacity(items_t &items, const Weight &binCapacity);
void prepareItems(items_t &items, const Weight &binCapacity,
                  const std::function<void(items_t &)> &function);
void deterministic(items_t &items);
void random(items_t &items);

} // namespace knapsack
#endif // KNAPSACK_ITEM_HH
