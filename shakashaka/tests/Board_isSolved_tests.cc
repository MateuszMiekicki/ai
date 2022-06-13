#include <gtest/gtest.h>

#include "shakashaka/Shakashaka.hh"
namespace
{
struct PrepareBoardParameter
{
    shakashaka::Board::board_t board;
    shakashaka::Board::board_t boardAfterPrepare;
};

class PrepareBoard : public ::testing::TestWithParam<PrepareBoardParameter>
{
};
} // namespace

TEST_P(PrepareBoard, testPrepareBoardToSolvingAlgorithm)
{
    // Arrange
    using namespace shakashaka;
    const auto &[basicBoard_p, prepareBoard_p] = GetParam();
    // Act
    auto board = Board(basicBoard_p);
    board.prepareBoardToSolve();
    // Assert
    ASSERT_EQ(board, prepareBoard_p);
}

INSTANTIATE_TEST_SUITE_P(
    theDiagonalNeighbourOfTheCellInTheCornerIsAllShaded, PrepareBoard,
    ::testing::Values(
        PrepareBoardParameter{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::fullyShaded,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty}},
            {{shakashaka::Cell::Type::dot, shakashaka::Cell::Type::dot,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::dot, shakashaka::Cell::Type::fullyShaded,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty}}},
        PrepareBoardParameter{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::fullyShaded,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty}},
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::dot, shakashaka::Cell::Type::dot},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::fullyShaded, shakashaka::Cell::Type::dot},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty}}},
        PrepareBoardParameter{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::fullyShaded,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty}},
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::dot, shakashaka::Cell::Type::fullyShaded,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::dot, shakashaka::Cell::Type::dot,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty}}},
        PrepareBoardParameter{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::fullyShaded,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty}},
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::fullyShaded, shakashaka::Cell::Type::dot},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::dot, shakashaka::Cell::Type::dot}}}));

INSTANTIATE_TEST_SUITE_P(
    inTheCornerIsACellThatRequiresExactlyTwoAdjacentCells, PrepareBoard,
    ::testing::Values(
        PrepareBoardParameter{
            {{2, shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty}},
            {{2, shakashaka::Cell::Type::upperLeftCornerHalfShaded,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::upperLeftCornerHalfShaded,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty}}},
        PrepareBoardParameter{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, 2},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty}},
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::upperRightCornerHalfShaded, 2},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::upperRightCornerHalfShaded},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty}}},
        PrepareBoardParameter{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {2, shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::bottomLeftCornerHalfShaded,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {2, shakashaka::Cell::Type::bottomLeftCornerHalfShaded,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty}}},
        PrepareBoardParameter{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, 2}},
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::bottomRightCornerHalfShaded},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::bottomRightCornerHalfShaded, 2}}}));