#include <gtest/gtest.h>

#include "Board.hh"
#include "Cell.hh"
#include "Coordinate.hh"

TEST(setCellTest, settingACellToADot)
{
    // Arrange
    const auto boardSize{5ULL};
    shakashaka::board::Board board(boardSize);
    const auto cellToSet{shakashaka::board::Cell::Type::dot};
    const auto coordinate{shakashaka::board::Coordinate{2, 2}};
    // Act
    const auto insertResult = board.setCell(cellToSet, coordinate);
    // Assert
    ASSERT_TRUE(insertResult);
    const auto setUpBoardCell{board.getCell(coordinate).getType()};
    ASSERT_EQ(setUpBoardCell, shakashaka::board::Cell::Type::dot);
}

TEST(setCellTest, checkingIfWeCanInsertAnythingIntoABoardOfSizeZero)
{
    // Arrange
    const auto boardSize{0ULL};
    // Assert
    ASSERT_THROW(/*Act*/ shakashaka::board::Board board(boardSize), std::exception);
}

TEST(setCellTest, checkingIfICanInsertACellOutsideTheBoardRange)
{
    // Arrange
    const auto boardSize{3ULL};
    shakashaka::board::Board board(boardSize);
    const auto cellToSet{shakashaka::board::Cell::Type::upperLeftCornerHalfShaded};
    const auto coordinate{shakashaka::board::Coordinate{3, 2}};
    // Act
    const auto setCellResult = board.setCell(cellToSet, coordinate);
    // Assert
    ASSERT_FALSE(setCellResult);
}

TEST(setCellTest, checkingIfICanInsertNumberCell)
{
    // Arrange
    const auto boardSize{3ULL};
    shakashaka::board::Board board(boardSize);
    const auto cellToSet = shakashaka::board::Cell(2);
    const auto coordinate{shakashaka::board::Coordinate{2, 2}};
    // Act
    const auto setCellResult = board.setCell(cellToSet, coordinate);
    // Assert
    ASSERT_FALSE(setCellResult);
}

namespace
{
struct BoardAndResultSetCell
{
    shakashaka::board::Board::board_t board;
    shakashaka::board::Cell cell;
    shakashaka::board::Coordinate coordinate;
    bool setCellResult;
};

class Board_Parametrized : public ::testing::TestWithParam<BoardAndResultSetCell>
{
};
} // namespace

TEST_P(Board_Parametrized, testOfInsertingNewCellsIntoTheBoard)
{
    // Arrange
    using namespace shakashaka::board;
    const auto &[board_p, cell_p, coordinate_p, result_p] = GetParam();
    // Act
    auto board = Board(board_p);
    const auto setCellResult = board.setCell(cell_p, coordinate_p);
    // Assert
    ASSERT_EQ(setCellResult, result_p);
    if (result_p)
    {
        ASSERT_EQ(cell_p.getType(), board.getCell(coordinate_p).getType());
    }
}

INSTANTIATE_TEST_SUITE_P(
    settingACellWithADot, Board_Parametrized,
    ::testing::Values(
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty, 0},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::dot),
            shakashaka::board::Coordinate{0, 2},
            false},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty, 2},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::dot),
            shakashaka::board::Coordinate{0, 2},
            false},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty, 0},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::dot),
            shakashaka::board::Coordinate{0, 1},
            true},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty, 0},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::dot),
            shakashaka::board::Coordinate{1, 2},
            true},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::upperLeftCornerHalfShaded},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::dot),
            shakashaka::board::Coordinate{0, 2},
            true},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::upperRightCornerHalfShaded},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::dot),
            shakashaka::board::Coordinate{0, 2},
            true},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::bottomLeftCornerHalfShaded},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::dot),
            shakashaka::board::Coordinate{0, 2},
            true},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::bottomRightCornerHalfShaded},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::dot),
            shakashaka::board::Coordinate{0, 2},
            true}));

INSTANTIATE_TEST_SUITE_P(
    settingTheShadedCell, Board_Parametrized,
    ::testing::Values(
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::upperLeftCornerHalfShaded),
            shakashaka::board::Coordinate{0, 0},
            true},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::upperRightCornerHalfShaded),
            shakashaka::board::Coordinate{0, 0},
            true},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::bottomRightCornerHalfShaded),
            shakashaka::board::Coordinate{0, 0},
            true},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::bottomLeftCornerHalfShaded),
            shakashaka::board::Coordinate{0, 0},
            true}));

INSTANTIATE_TEST_SUITE_P(
    settingCellsUpperAZeroCell, Board_Parametrized,
    ::testing::Values(
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, 0, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::bottomLeftCornerHalfShaded),
            shakashaka::board::Coordinate{0, 1},
            false},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, 0, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::bottomRightCornerHalfShaded),
            shakashaka::board::Coordinate{0, 1},
            false},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, 0, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::upperLeftCornerHalfShaded),
            shakashaka::board::Coordinate{0, 1},
            true},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, 0, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::upperRightCornerHalfShaded),
            shakashaka::board::Coordinate{0, 1},
            true}));

INSTANTIATE_TEST_SUITE_P(
    settingCellsBottomAZeroCell, Board_Parametrized,
    ::testing::Values(
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, 0, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::bottomLeftCornerHalfShaded),
            shakashaka::board::Coordinate{2, 1},
            true},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, 0, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::bottomRightCornerHalfShaded),
            shakashaka::board::Coordinate{2, 1},
            true},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, 0, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::upperLeftCornerHalfShaded),
            shakashaka::board::Coordinate{2, 1},
            false},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, 0, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::upperRightCornerHalfShaded),
            shakashaka::board::Coordinate{2, 1},
            false}));

INSTANTIATE_TEST_SUITE_P(
    settingCellsLeftAZeroCell, Board_Parametrized,
    ::testing::Values(
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, 0, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::bottomRightCornerHalfShaded),
            shakashaka::board::Coordinate{1, 0},
            false},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, 0, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::upperRightCornerHalfShaded),
            shakashaka::board::Coordinate{1, 0},
            false},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, 0, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::upperLeftCornerHalfShaded),
            shakashaka::board::Coordinate{1, 0},
            true},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, 0, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::bottomLeftCornerHalfShaded),
            shakashaka::board::Coordinate{1, 0},
            true}));

INSTANTIATE_TEST_SUITE_P(
    settingCellsRightAZeroCell, Board_Parametrized,
    ::testing::Values(
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, 0, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::bottomRightCornerHalfShaded),
            shakashaka::board::Coordinate{1, 2},
            true},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, 0, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::upperRightCornerHalfShaded),
            shakashaka::board::Coordinate{1, 2},
            true},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, 0, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::upperLeftCornerHalfShaded),
            shakashaka::board::Coordinate{1, 2},
            false},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, 0, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::bottomLeftCornerHalfShaded),
            shakashaka::board::Coordinate{1, 2},
            false}));

INSTANTIATE_TEST_SUITE_P(
    settingDotAroundZeroCell, Board_Parametrized,
    ::testing::Values(
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, 0, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::dot),
            shakashaka::board::Coordinate{0, 1},
            true},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, 0, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::dot),
            shakashaka::board::Coordinate{1, 0},
            true},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, 0, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::dot),
            shakashaka::board::Coordinate{1, 2},
            true},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, 0, shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::dot),
            shakashaka::board::Coordinate{2, 1},
            true}));

INSTANTIATE_TEST_SUITE_P(
    settingDotAroundNumberCell, Board_Parametrized,
    ::testing::Values(
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::upperRightCornerHalfShaded, 2},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::upperRightCornerHalfShaded),
            shakashaka::board::Coordinate{1, 2},
            true},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::upperRightCornerHalfShaded, 2},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::upperLeftCornerHalfShaded},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::upperLeftCornerHalfShaded),
            shakashaka::board::Coordinate{1, 2},
            false},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::bottomLeftCornerHalfShaded,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::upperRightCornerHalfShaded, 3,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::upperRightCornerHalfShaded,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::upperLeftCornerHalfShaded),
            shakashaka::board::Coordinate{2, 1},
            false},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::bottomLeftCornerHalfShaded,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::upperRightCornerHalfShaded, 4,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::upperLeftCornerHalfShaded),
            shakashaka::board::Coordinate{2, 1},
            true},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::upperRightCornerHalfShaded,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::upperLeftCornerHalfShaded, 4,
              shakashaka::board::Cell::Type::upperRightCornerHalfShaded},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::bottomLeftCornerHalfShaded),
            shakashaka::board::Coordinate{2, 1},
            true},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::bottomLeftCornerHalfShaded,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::bottomRightCornerHalfShaded, 3,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::upperRightCornerHalfShaded),
            shakashaka::board::Coordinate{2, 1},
            true}));

INSTANTIATE_TEST_SUITE_P(
    settingCellOnFullShadedCell, Board_Parametrized,
    ::testing::Values(
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::fullyShaded, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::upperRightCornerHalfShaded),
            shakashaka::board::Coordinate{0, 0},
            false},
        BoardAndResultSetCell{
            {{shakashaka::board::Cell::Type::fullyShaded, 2,
              shakashaka::board::Cell::Type::upperLeftCornerHalfShaded},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::fullyShaded},
             {shakashaka::board::Cell::Type::empty, shakashaka::board::Cell::Type::empty,
              shakashaka::board::Cell::Type::empty}},
            shakashaka::board::Cell(shakashaka::board::Cell::Type::upperLeftCornerHalfShaded),
            shakashaka::board::Coordinate{1, 2},
            false},
        BoardAndResultSetCell{{{shakashaka::board::Cell::Type::empty,
                                shakashaka::board::Cell::Type::bottomLeftCornerHalfShaded,
                                shakashaka::board::Cell::Type::empty},
                               {shakashaka::board::Cell::Type::upperRightCornerHalfShaded, 3,
                                shakashaka::board::Cell::Type::empty},
                               {shakashaka::board::Cell::Type::empty,
                                shakashaka::board::Cell::Type::upperRightCornerHalfShaded,
                                shakashaka::board::Cell::Type::empty}},
                              shakashaka::board::Cell(shakashaka::board::Cell::Type::fullyShaded),
                              shakashaka::board::Coordinate{2, 1},
                              false}));