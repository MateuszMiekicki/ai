#include <gtest/gtest.h>

#include "shakashaka/Shakashaka.hh"

TEST(setCellTest, settingACellToADot)
{
    // Arrange
    const auto BOARD_SIZE{5ull};
    shakashaka::Board board(BOARD_SIZE);
    const auto CELL_TO_SET{shakashaka::Board::Cell::Type::dot};
    const auto COORDINATE{shakashaka::Board::Coordinate{2, 2}};
    // Act
    const auto INSERT_RESULT = board.setCell(CELL_TO_SET, COORDINATE);
    // Assert
    ASSERT_TRUE(INSERT_RESULT);
    const auto SET_BOARD_CELL{board.getCell(COORDINATE).type};
    ASSERT_EQ(SET_BOARD_CELL, shakashaka::Board::Cell::Type::dot);
}

TEST(setCellTest, checkingIfWeCanInsertAnythingIntoABoardOfSizeZero)
{
    // Arrange
    const auto BOARD_SIZE{0ull};
    shakashaka::Board board(BOARD_SIZE);
    const auto CELL_TO_SET{shakashaka::Board::Cell::Type::dot};
    const auto COORDINATE{shakashaka::Board::Coordinate{2, 2}};
    // Act
    const auto SET_CELL_RESULT = board.setCell(CELL_TO_SET, COORDINATE);
    // Assert
    ASSERT_FALSE(SET_CELL_RESULT);
}

// TEST(setCellTest, setACellWhenThereIsACellWithZeroNextToIt)
//{
//     // Arrange
//     using namespace shakashaka;
//     const auto EMPTY_CELL = Board::Cell();
//     const auto ZERO_CELL = Board::Cell(0);
//     auto boardWithACellWithTheNumberZero =
//         Board::board_t{{EMPTY_CELL, EMPTY_CELL, ZERO_CELL},
//                        {EMPTY_CELL, EMPTY_CELL, EMPTY_CELL},
//                        {EMPTY_CELL, EMPTY_CELL, EMPTY_CELL}};
//     // Act
//     auto board = Board(boardWithACellWithTheNumberZero);
//     const auto SET_CELL_RESULT = board.setCell();
//     // Assert
//     ASSERT_FALSE(SET_CELL_RESULT)
// }

struct BoardAndResultSetCell
{
    shakashaka::Board::board_t board;
    shakashaka::Board::Cell cell;
    shakashaka::Board::Coordinate coordinate;
    bool setCellResult;
};

class Board_Parametrized
    : public ::testing::TestWithParam<BoardAndResultSetCell>
{
};

TEST_P(Board_Parametrized, test_clearing_whitespaces)
{
    // Arrange
    using namespace shakashaka;
    const auto &[board_p, cell_p, coordinate_p, result_p] = GetParam();
    // Act
    auto board = Board(board_p);
    const auto setCellResult = board.setCell(cell_p, coordinate_p);
    // Assert
    ASSERT_EQ(setCellResult, result_p);
}

INSTANTIATE_TEST_CASE_P(
    setCellTest, Board_Parametrized,
    ::testing::Values(
        BoardAndResultSetCell{{{shakashaka::Board::Cell::Type::empty,
                                shakashaka::Board::Cell::Type::empty, 0},
                               {shakashaka::Board::Cell::Type::empty,
                                shakashaka::Board::Cell::Type::empty,
                                shakashaka::Board::Cell::Type::empty},
                               {shakashaka::Board::Cell::Type::empty,
                                shakashaka::Board::Cell::Type::empty,
                                shakashaka::Board::Cell::Type::empty}},
                              shakashaka::Board::Cell(0),
                              shakashaka::Board::Coordinate{0, 1},
                              false},
        BoardAndResultSetCell{{{shakashaka::Board::Cell::Type::empty,
                                shakashaka::Board::Cell::Type::empty,
                                shakashaka::Board::Cell::Type::empty},
                               {shakashaka::Board::Cell::Type::empty,
                                shakashaka::Board::Cell::Type::empty,
                                shakashaka::Board::Cell::Type::empty},
                               {shakashaka::Board::Cell::Type::empty,
                                shakashaka::Board::Cell::Type::empty,
                                shakashaka::Board::Cell::Type::empty}},
                              shakashaka::Board::Cell(0),
                              shakashaka::Board::Coordinate{0, 0},
                              false},
        BoardAndResultSetCell{
            {{shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty, 0},
             {shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty},
             {shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty}},
            shakashaka::Board::Cell(shakashaka::Board::Cell::Type::dot),
            shakashaka::Board::Coordinate{0, 0},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty, 0},
             {shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty},
             {shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty}},
            shakashaka::Board::Cell(shakashaka::Board::Cell::Type::dot),
            shakashaka::Board::Coordinate{0, 1},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::bottomRightCornerHalfShaded},
             {shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty},
             {shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty}},
            shakashaka::Board::Cell(shakashaka::Board::Cell::Type::dot),
            shakashaka::Board::Coordinate{0, 1},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty, 0},
             {shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty},
             {shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty}},
            shakashaka::Board::Cell(shakashaka::Board::Cell::Type::dot),
            shakashaka::Board::Coordinate{0, 1},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::dot, 0},
             {shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty},
             {shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty}},
            shakashaka::Board::Cell(shakashaka::Board::Cell::Type::dot),
            shakashaka::Board::Coordinate{1, 2},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::dot, 0},
             {shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty},
             {shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty}},
            shakashaka::Board::Cell(
                shakashaka::Board::Cell::Type::upperLeftCornerHalfShaded),
            shakashaka::Board::Coordinate{1, 2},
            false},
        BoardAndResultSetCell{
            {{shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::dot, 0},
             {shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty},
             {shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty}},
            shakashaka::Board::Cell(
                shakashaka::Board::Cell::Type::upperRightCornerHalfShaded),
            shakashaka::Board::Coordinate{1, 2},
            false},
        //----
        BoardAndResultSetCell{
            {{shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty},
             {shakashaka::Board::Cell::Type::empty, 0,
              shakashaka::Board::Cell::Type::empty},
             {shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty}},
            shakashaka::Board::Cell(
                shakashaka::Board::Cell::Type::bottomLeftCornerHalfShaded),
            shakashaka::Board::Coordinate{0, 1},
            false},
        BoardAndResultSetCell{
            {{shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty},
             {shakashaka::Board::Cell::Type::empty, 0,
              shakashaka::Board::Cell::Type::empty},
             {shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty}},
            shakashaka::Board::Cell(
                shakashaka::Board::Cell::Type::bottomRightCornerHalfShaded),
            shakashaka::Board::Coordinate{0, 1},
            false},
        BoardAndResultSetCell{
            {{shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty},
             {shakashaka::Board::Cell::Type::empty, 0,
              shakashaka::Board::Cell::Type::empty},
             {shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty}},
            shakashaka::Board::Cell(
                shakashaka::Board::Cell::Type::upperLeftCornerHalfShaded),
            shakashaka::Board::Coordinate{2, 1},
            false},
        BoardAndResultSetCell{
            {{shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty},
             {shakashaka::Board::Cell::Type::empty, 0,
              shakashaka::Board::Cell::Type::empty},
             {shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty}},
            shakashaka::Board::Cell(
                shakashaka::Board::Cell::Type::upperRightCornerHalfShaded),
            shakashaka::Board::Coordinate{2, 1},
            false},
        BoardAndResultSetCell{
            {{shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty},
             {shakashaka::Board::Cell::Type::empty, 0,
              shakashaka::Board::Cell::Type::empty},
             {shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty}},
            shakashaka::Board::Cell(
                shakashaka::Board::Cell::Type::bottomRightCornerHalfShaded),
            shakashaka::Board::Coordinate{1, 0},
            false},
        BoardAndResultSetCell{
            {{shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty},
             {shakashaka::Board::Cell::Type::empty, 0,
              shakashaka::Board::Cell::Type::empty},
             {shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty}},
            shakashaka::Board::Cell(
                shakashaka::Board::Cell::Type::upperRightCornerHalfShaded),
            shakashaka::Board::Coordinate{1, 0},
            false},
        BoardAndResultSetCell{
            {{shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty},
             {shakashaka::Board::Cell::Type::empty, 0,
              shakashaka::Board::Cell::Type::empty},
             {shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty}},
            shakashaka::Board::Cell(
                shakashaka::Board::Cell::Type::upperLeftCornerHalfShaded),
            shakashaka::Board::Coordinate{1, 2},
            false},
        BoardAndResultSetCell{
            {{shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty},
             {shakashaka::Board::Cell::Type::empty, 0,
              shakashaka::Board::Cell::Type::empty},
             {shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty,
              shakashaka::Board::Cell::Type::empty}},
            shakashaka::Board::Cell(
                shakashaka::Board::Cell::Type::bottomLeftCornerHalfShaded),
            shakashaka::Board::Coordinate{1, 2},
            false}));