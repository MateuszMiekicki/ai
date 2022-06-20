#ifndef KNAPSACK_ITEM_HH
#define KNAPSACK_ITEM_HH

namespace knapsack
{
class Item
{
  public:
    using price_t = long double;
    using weight_t = long double;
    using ratio_t = long double;

  private:
    price_t price_;
    weight_t weight_;

  public:
    Item(const price_t price, const weight_t weight);

    ratio_t costEffectivenessRatio() const;

    bool operator==(const Item &item) const;
    bool operator!=(const Item &item) const;

    bool operator<(const Item &item) const;
    bool operator>(const Item &item) const;

    bool operator<=(const Item &item) const;
    bool operator>=(const Item &item) const;
};
} // namespace knapsack

#endif // KNAPSACK_ITEM_HH
