#ifndef KNAPSACK_PARAMETERS_HH
#define KNAPSACK_PARAMETERS_HH
#include <optional>

namespace knapsack::algorithm
{
using Temperature = Decimal<struct TemperatureTag>;

template<typename Tag>
using NaturalNumbers = Number<Tag, unsigned long long>;

using AmountOfChromosomes = NaturalNumbers<struct AmountOfChromosomesTag>;

struct Parameters
{
    std::size_t iteration;
    Parameters() = delete;
    Parameters(const std::size_t it) : iteration{it}
    {
    }
    std::optional<Temperature> temperature = std::nullopt;
    std::optional<AmountOfChromosomes> amountOfChromosomes = std::nullopt;
};
} // namespace knapsack::algorithm
#endif // KNAPSACK_PARAMETERS_HH
