#ifndef KNAPSACK_PARAMETERS_HH
#define KNAPSACK_PARAMETERS_HH
#include <optional>

namespace knapsack::algorithm
{
struct Parameters
{
    Iteration iteration;
    Parameters() = delete;
    explicit Parameters(const Iteration it) : iteration{it}
    {
    }
    std::optional<Temperature> temperature = std::nullopt;
    std::optional<AmountOfChromosomes> amountOfChromosomes = std::nullopt;
    std::optional<ProbabilityOfMutation> probabilityOfMutation = std::nullopt;
};
} // namespace knapsack::algorithm
#endif // KNAPSACK_PARAMETERS_HH
