#include <gtest/gtest.h>

#include "Item.hh"

namespace
{
struct Parameters
{
    knapsack::items_t before;
    knapsack::items_t after;
    knapsack::Weight binCapacity;
};

class Preparation : public ::testing::TestWithParam<Parameters>
{
};
} // namespace

TEST_P(Preparation, removalOfItemsHeavierThanTheBinLimit)
{
    // Arrange
    auto [before, after, binCapacity] = GetParam();
    // Act
    knapsack::removeItemsLargerThanCapacity(before, binCapacity);
    // Assert
    ASSERT_EQ(before, after);
}

INSTANTIATE_TEST_SUITE_P(
    removeItemsLargerThanCapacity, Preparation,
    ::testing::Values(Parameters{{{1, 43}, {1, 3}, {1, 6.4}, {1, 15}, {1, 14.999}},
                                 {{1, 3}, {1, 6.4}, {1, 15}, {1, 14.999}},
                                 15},
                      Parameters{{{1, 43}, {1, 3}, {1, 6.4}, {1, 15}, {1, 14.999}, {1, 14.5}},
                                 {{1, 3}, {1, 6.4}, {1, 14.5}},
                                 14.543},
                      Parameters{{{1, 43}, {1, 3}, {1, 6.4}, {1, 15}, {1, 14.999}},
                                 {{1, 43}, {1, 3}, {1, 6.4}, {1, 15}, {1, 14.999}},
                                 43}));
