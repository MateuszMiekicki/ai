#ifndef KNAPSACK_HILLCLIMBING_HH
#define KNAPSACK_HILLCLIMBING_HH
#include "Bin.hh"
#include "Item.hh"
#include "Parameters.hh"
#include "Solver.hh"

namespace knapsack::algorithm
{
class HillClimbing : public Solver
{
  private:
    Bin &bin_;
    items_t items_;
    Parameters parameters_;
    void objectiveFunction();

  public:
    HillClimbing() = delete;
    HillClimbing(Bin &bin, const items_t &items, const Parameters &parameters);
    void solve() override;
};
} // namespace knapsack::algorithm
#endif // KNAPSACK_HILLCLIMBING_HH
