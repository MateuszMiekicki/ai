#ifndef KNAPSACK_KNAPSACK_HH
#define KNAPSACK_KNAPSACK_HH
#include "Decimal.hh"
#include <vector>

namespace knapsack
{
class Item;
using items_t = std::vector<Item>;
class Knapsack
{
  private:
    items_t items_ = {};
    Weight capacity_ = {0};

  public:
    Knapsack() = delete;
    Knapsack(const Weight &capacity, const items_t &items);
    Knapsack(const Weight &capacity);
    void addItem(const Item &item);
    void removeItem(const std::size_t index);
    Value value() const;
    Weight weight() const;
};
} // namespace knapsack
#endif // KNAPSACK_KNAPSACK_HH
