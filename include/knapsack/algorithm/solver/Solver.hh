#ifndef KNAPSACK_SOLVER_HH
#define KNAPSACK_SOLVER_HH
#include <cstddef>

namespace knapsack
{
class Bin;
}
namespace knapsack::algorithm
{
class Solver
{
  public:
    virtual void solve() = 0;
    virtual ~Solver() = default;
};
} // namespace knapsack::algorithm
#endif // KNAPSACK_SOLVER_HH
