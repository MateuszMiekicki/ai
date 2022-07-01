#include <gtest/gtest.h>

#include "Bin.hh"
#include "Item.hh"
#include "Parameters.hh"
#include "SimulatedAnnealing.hh"
namespace
{
struct Parameters
{
    knapsack::items_t items;
    knapsack::Value expectedValue;
    knapsack::Weight binCapacity;
    knapsack::Iteration iteration;
};

class SimulatedAnnealingSolver : public ::testing::TestWithParam<Parameters>
{
};
} // namespace

TEST_P(SimulatedAnnealingSolver, testingDeterministicOrderItems)
{
    // Arrange
    auto [items, expectedValue, binCapacity, iteration] = GetParam();
    using namespace knapsack;
    using namespace knapsack::algorithm;
    Bin bin{binCapacity};
    prepareItems(items, binCapacity, deterministic);
    knapsack::algorithm::Parameters parameters{iteration};
    parameters.temperature = 1'000.0;
    std::unique_ptr<Solver> solver = std::make_unique<SimulatedAnnealing>(bin, items, parameters);
    // Act
    solver->solve();
    // Assert
    ASSERT_EQ(bin.value(), expectedValue);
}
INSTANTIATE_TEST_SUITE_P(
    removeItemsLargerThanCapacity, SimulatedAnnealingSolver,
    ::testing::Values(
        Parameters{
            {{40, 2}, {160, 2}, {70, 3}, {300, 15}, {70, 1}, {25, 4}, {25, 5}, {180, 6}, {180, 16}},
            520,
            15,
            1000},
        Parameters{{{60, 10}, {100, 20}, {120, 30}}, 220, 50, 1000},
        Parameters{{{60, 10}, {100, 20}, {120, 30}}, 160, 30, 1000}));