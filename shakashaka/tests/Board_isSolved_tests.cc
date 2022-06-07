#include <gtest/gtest.h>

#include "shakashaka/Shakashaka.hh"
namespace
{
struct PrepareBoard
{
    shakashaka::Board::board_t board;
    shakashaka::Board::board_t boardAfterPrepare;
};

class PrepareBoard_Parametrized : public ::testing::TestWithParam<PrepareBoard>
{
};
} // namespace

TEST_P(PrepareBoard_Parametrized, testOfInsertingNewCellsIntoTheBoard)
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
    prepareBoard, PrepareBoard_Parametrized,
    ::testing::Values(PrepareBoard{
        {
        {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::fullyShaded, shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
         {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
         {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,shakashaka::Cell::Type::fullyShaded, shakashaka::Cell::Type::empty},
         {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty}
        },
        {
            {shakashaka::Cell::Type::dot, shakashaka::Cell::Type::fullyShaded, shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
            {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
            {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,shakashaka::Cell::Type::fullyShaded, shakashaka::Cell::Type::dot},
            {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,shakashaka::Cell::Type::dot, shakashaka::Cell::Type::dot}
        }}));