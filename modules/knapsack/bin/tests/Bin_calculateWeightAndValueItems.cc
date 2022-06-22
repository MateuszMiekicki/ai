#include <gtest/gtest.h>

#include "Bin.hh"
#include "Item.hh"
#include <algorithm>

struct Parameters
{
    std::vector<knapsack::Item> items;
    knapsack::Value expectedValueOfItems;
    knapsack::Weight expectedWeightOfItems;
};

class Calculate : public ::testing::TestWithParam<Parameters>
{
};

TEST_P(Calculate, CalculationOfWeightAndValueOfAllItems)
{
    // Arrange
    const auto &[items, expectedValue, expectedWeight] = GetParam();
    // Act
    const auto knapsack = knapsack::Bin(0, items);
    const auto value = knapsack.value();
    const auto weight = knapsack.weight();
    // Assert
    ASSERT_DOUBLE_EQ(value, expectedValue);
    ASSERT_DOUBLE_EQ(weight, expectedWeight);
}

INSTANTIATE_TEST_SUITE_P(
    calculationOnItemsInKnapsack, Calculate,
    ::testing::Values(Parameters{{{{3.0}, {1.0}}, {{3.0}, {1.0}}, {{3.0}, {1.0}}}, {9}, {3}},
                      Parameters{{{{1.0}, {2.0}}, {{3.0}, {4.0}}, {{5.0}, {6.0}}}, {9}, {12}},
                      Parameters{{{{.5}, {.25}}, {{.5}, {.25}}, {{.5}, {.25}}}, {1.5}, {.75}},
                      Parameters{{{{.33}, {.66}}, {{.33}, {.66}}, {{.33}, {.66}}}, {.99}, {1.98}}));
