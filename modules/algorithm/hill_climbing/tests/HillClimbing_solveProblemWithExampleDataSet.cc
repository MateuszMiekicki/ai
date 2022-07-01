#include <gtest/gtest.h>

#include "Bin.hh"
#include "HillClimbing.hh"
#include "Item.hh"

namespace
{
struct Parameters
{
    knapsack::items_t items;
    knapsack::Value expectedValue;
    knapsack::Weight binCapacity;
    knapsack::Iteration iteration;
};

class HillClimbingSolver : public ::testing::TestWithParam<Parameters>
{
};
} // namespace

TEST_P(HillClimbingSolver, testingDeterministicOrderItems)
{
    // Arrange
    auto [items, expectedValue, binCapacity, iteration] = GetParam();
    using namespace knapsack;
    using namespace knapsack::algorithm;
    Bin bin{binCapacity};
    prepareItems(items, binCapacity, deterministic);
    knapsack::algorithm::Parameters parameters{iteration};
    std::unique_ptr<Solver> solver = std::make_unique<HillClimbing>(bin, items, parameters);
    // Act
    solver->solve();
    // Assert
    ASSERT_EQ(bin.value(), expectedValue);
}

INSTANTIATE_TEST_SUITE_P(
    removeItemsLargerThanCapacity, HillClimbingSolver,
    ::testing::Values(
        Parameters{
            {{40, 2}, {160, 2}, {70, 3}, {300, 15}, {70, 1}, {25, 4}, {25, 5}, {180, 6}, {180, 16}},
            520,
            15,
            10},
        Parameters{{{60, 10}, {100, 20}, {120, 30}}, 220, 50, 5},
        Parameters{{{60, 10}, {100, 20}, {120, 30}}, 160, 30, 5}));
