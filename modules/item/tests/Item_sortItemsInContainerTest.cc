#include <gtest/gtest.h>

#include "Item.hh"

struct Parameters
{
    knapsack::Item lhs;
    knapsack::Item rhs;
    bool lhsIsMoreCostEffective;
};

class Items : public ::testing::TestWithParam<Parameters>
{
};

TEST_P(Items, comparingTwoItemsAndDeterminingWhichIsMoreCostEffective)
{
    // Arrange
    const auto &[lhs_p, rhs_p, lhsIsMoreCostEffective_p] = GetParam();
    // Act
    const auto lhsIsMoreCostEffective = lhs_p > rhs_p;
    // Assert
    ASSERT_EQ(lhsIsMoreCostEffective, lhsIsMoreCostEffective_p);
}

INSTANTIATE_TEST_SUITE_P(theDiagonalNeighbourOfTheCellInTheCornerIsAllShaded, Items,
                         ::testing::Values(Parameters{{12.6, 1.0}, {3.2, 100.0}, true},
                                           Parameters{{3.0, 1.0}, {5.0, 1.0}, false},
                                           Parameters{{5.001, 1.0}, {5.0, 1.0}, true},
                                           Parameters{{3.0, .5}, {5.0, 1.0}, true},
                                           Parameters{{123.0, 100.0}, {1230.0, 998.999}, false}));
