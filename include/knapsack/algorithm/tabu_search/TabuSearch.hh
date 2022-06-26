#ifndef KNAPSACK_TABUSEARCH_HH
#define KNAPSACK_TABUSEARCH_HH
#include "Bin.hh"
#include "Item.hh"
#include "Solver.hh"

namespace knapsack::algorithm
{
class TabuSearch : public Solver
{
  private:
    std::size_t iteration_;
    Bin &bin_;
    items_t items_;
    void objectiveFunction();
    void quickRemoveItemFromList(items_t &items, const std::size_t idx);

  public:
    TabuSearch() = delete;
    TabuSearch(const std::size_t iteration, Bin &bin, const items_t &items);
    void solve() override;
};
} // namespace knapsack::algorithm
#endif // KNAPSACK_TABUSEARCH_HH
