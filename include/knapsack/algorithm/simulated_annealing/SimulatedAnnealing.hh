#ifndef KNAPSACK_SIMULATEDANNEALING_HH
#define KNAPSACK_SIMULATEDANNEALING_HH
#include "Bin.hh"
#include "Item.hh"
#include "Parameters.hh"
#include "Solver.hh"
#include <random>

namespace knapsack::algorithm
{
class SimulatedAnnealing : public Solver
{
  private:
    Bin &bin_;
    items_t items_;
    Parameters parameters_;
    static constexpr long double boltzmannConstant{1.3806503e-23};

    Ratio probabilityOfChoosingWorseSolution(const Bin &betterBin, const Bin &worseBin,
                                             const Temperature temperature) const;
    Ratio drawProbability() const;
    bool objectiveFunction(const Bin& current)const;
    void permutation();

  public:
    SimulatedAnnealing() = delete;
    SimulatedAnnealing(Bin &bin, const items_t &items, const Parameters &parameters);
    void solve() override;
};
} // namespace knapsack::algorithm
#endif // KNAPSACK_SIMULATEDANNEALING_HH
