#ifndef KNAPSACK_BIN_HH
#define KNAPSACK_BIN_HH
#include "Number.hh"
#include <vector>

namespace knapsack
{
class Item;
using items_t = std::vector<Item>;
class Bin
{
  private:
    items_t items_ = {};
    Weight capacity_ = {0};

  public:
    Bin() = delete;
    Bin(const Weight &capacity, const items_t &items);
    explicit Bin(const Weight &capacity);
    void fill(const items_t &items);
    bool isFits(const Item &item) const;
    Value value() const;
    Weight weight() const;
    Weight capacity() const;
    void add(const Item &item);
    items_t items() const;
};
} // namespace knapsack
#endif // KNAPSACK_BIN_HH
