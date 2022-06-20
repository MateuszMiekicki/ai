#include <gtest/gtest.h>

#include <Board.hh>
#include <Cell.hh>
#include <Solver.hh>

namespace
{
struct PrepareBoardParameter
{
    shakashaka::board::Board::board_t board;
    shakashaka::board::Board::board_t boardAfterPrepare;
};

class PrepareBoard : public ::testing::TestWithParam<PrepareBoardParameter>
{
};
} // namespace

TEST_P(PrepareBoard, testPrepareBoardToSolvingAlgorithm)
{
    // Arrange
    using namespace shakashaka::solver;
    const auto &[basicBoard_p, prepareBoard_p] = GetParam();
    // Act
    auto solver = Solver(basicBoard_p);
    solver.prepareBoardToSolve();
    // Assert
    ASSERT_EQ(solver.board_, prepareBoard_p);
}

INSTANTIATE_TEST_SUITE_P(
    theDiagonalNeighbourOfTheCellInTheCornerIsAllShaded, PrepareBoard,
    ::testing::Values(
        PrepareBoardParameter{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::fullyShaded,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty}},
            {{shakashaka::board::Cell::Type::dot, shakashaka::board::Cell::Type::dot,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::dot, shakashaka::board::Cell::Type::fullyShaded,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty}}},
        PrepareBoardParameter{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::fullyShaded, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty}},
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::dot, shakashaka::board::Cell::Type::dot},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::fullyShaded, shakashaka::board::Cell::Type::dot},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty}}},
        PrepareBoardParameter{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::fullyShaded,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty}},
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::dot, shakashaka::board::Cell::Type::fullyShaded,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::dot, shakashaka::board::Cell::Type::dot,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty}}},
        PrepareBoardParameter{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::fullyShaded, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty}},
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::fullyShaded, shakashaka::board::Cell::Type::dot},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::dot, shakashaka::board::Cell::Type::dot}}}));

INSTANTIATE_TEST_SUITE_P(
    inTheCornerIsACellThatRequiresExactlyTwoAdjacentCells, PrepareBoard,
    ::testing::Values(
        PrepareBoardParameter{
            {{2, shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty}},
            {{2, shakashaka::board::Cell::Type::upperLeftCornerHalfShaded,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::upperLeftCornerHalfShaded,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty}}},
        PrepareBoardParameter{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, 2},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty}},
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::upperRightCornerHalfShaded, 2},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::upperRightCornerHalfShaded},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty}}},
        PrepareBoardParameter{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {2, shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::bottomLeftCornerHalfShaded,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {2, shakashaka::board::Cell::Type::bottomLeftCornerHalfShaded,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty}}},
        PrepareBoardParameter{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, 2}},
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::bottomRightCornerHalfShaded},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::bottomRightCornerHalfShaded, 2}}}));