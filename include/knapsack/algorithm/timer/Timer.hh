#ifndef KNAPSACK_STOPWATCH_HH
#define KNAPSACK_STOPWATCH_HH
#include "Solver.hh"
#include <chrono>
#include <memory>

namespace knapsack::algorithm
{
class Timer
{
  public:
    static auto measurement(const std::unique_ptr<Solver> &solver)
    {
        const auto start = std::chrono::high_resolution_clock::now();
        solver->solve();
        const auto stop = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    }
};
} // namespace knapsack::algorithm
#endif // KNAPSACK_STOPWATCH_HH
