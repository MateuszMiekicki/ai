#include <gtest/gtest.h>

#include "Bin.hh"
#include "Item.hh"
#include "TabuSearch.hh"

namespace
{
struct Parameters
{
    knapsack::items_t items;
    knapsack::Value expectedValue;
    knapsack::Weight binCapacity;
    std::size_t iteration;
};

class TabuSearchSolver : public ::testing::TestWithParam<Parameters>
{
};
} // namespace

TEST_P(TabuSearchSolver, testingDeterministicOrderItems)
{
    // Arrange
    auto [items, expectedValue, binCapacity, iteration] = GetParam();
    using namespace knapsack;
    using namespace knapsack::algorithm;
    Bin bin{binCapacity};
    prepareItems(items, binCapacity, deterministic);
    std::unique_ptr<Solver> solver = std::make_unique<TabuSearch>(iteration, bin, items);
    // Act
    solver->solve();
    // Assert
    ASSERT_EQ(bin.value(), expectedValue);
}

INSTANTIATE_TEST_SUITE_P(
    removeItemsLargerThanCapacity, TabuSearchSolver,
    ::testing::Values(Parameters{
        {{40, 2}, {160, 2}, {70, 3}, {300, 15}, {70, 1}, {25, 4}, {25, 5}, {180, 6}, {180, 16}},
        520,
        15,
        10} //        Parameters{{{60, 10}, {100, 20}, {120, 30}}, 220, 50, 5},
            //        Parameters{{{60, 10}, {100, 20}, {120, 30}}, 160, 30, 5}
                      ));
