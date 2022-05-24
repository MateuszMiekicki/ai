#include <gtest/gtest.h>

#include "shakashaka/Shakashaka.hh"

TEST(setCellTest, settingACellToADot)
{
    // Arrange
    const auto boardSize{5ULL};
    shakashaka::Board board(boardSize);
    const auto cellToSet{shakashaka::Cell::Type::dot};
    const auto coordinate{shakashaka::Coordinate{2, 2}};
    // Act
    const auto insertResult = board.setCell(cellToSet, coordinate);
    // Assert
    ASSERT_TRUE(insertResult);
    const auto setUpBoardCell{board.getCell(coordinate).getType()};
    ASSERT_EQ(setUpBoardCell, shakashaka::Cell::Type::dot);
}

TEST(setCellTest, checkingIfWeCanInsertAnythingIntoABoardOfSizeZero)
{
    // Arrange
    const auto boardSize{0ULL};
    shakashaka::Board board(boardSize);
    const auto cellToSet{shakashaka::Cell::Type::dot};
    const auto coordinate{shakashaka::Coordinate{2, 2}};
    // Act
    const auto setCellResult = board.setCell(cellToSet, coordinate);
    // Assert
    ASSERT_FALSE(setCellResult);
}

TEST(setCellTest, checkingIfICanInsertACellOutsideTheBoardRange)
{
    // Arrange
    const auto boardSize{3ULL};
    shakashaka::Board board(boardSize);
    const auto cellToSet{shakashaka::Cell::Type::upperLeftCornerHalfShaded};
    const auto coordinate{shakashaka::Coordinate{3, 2}};
    // Act
    const auto setCellResult = board.setCell(cellToSet, coordinate);
    // Assert
    ASSERT_FALSE(setCellResult);
}

TEST(setCellTest, checkingIfICanInsertNumberCell)
{
    // Arrange
    const auto boardSize{3ULL};
    shakashaka::Board board(boardSize);
    const auto cellToSet = shakashaka::Cell(2);
    const auto coordinate{shakashaka::Coordinate{2, 2}};
    // Act
    const auto setCellResult = board.setCell(cellToSet, coordinate);
    // Assert
    ASSERT_FALSE(setCellResult);
}

struct BoardAndResultSetCell
{
    shakashaka::Board::board_t board;
    shakashaka::Cell cell;
    shakashaka::Coordinate coordinate;
    bool setCellResult;
};

class Board_Parametrized
    : public ::testing::TestWithParam<BoardAndResultSetCell>
{
};

TEST_P(Board_Parametrized, testOfInsertingNewCellsIntoTheBoard)
{
    // Arrange
    using namespace shakashaka;
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
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty, 0},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(shakashaka::Cell::Type::dot),
            shakashaka::Coordinate{0, 2},
            false},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty, 2},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(shakashaka::Cell::Type::dot),
            shakashaka::Coordinate{0, 2},
            false},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty, 0},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(shakashaka::Cell::Type::dot),
            shakashaka::Coordinate{0, 1},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty, 0},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(shakashaka::Cell::Type::dot),
            shakashaka::Coordinate{1, 2},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::upperLeftCornerHalfShaded},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(shakashaka::Cell::Type::dot),
            shakashaka::Coordinate{0, 2},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::upperRightCornerHalfShaded},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(shakashaka::Cell::Type::dot),
            shakashaka::Coordinate{0, 2},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::bottomLeftCornerHalfShaded},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(shakashaka::Cell::Type::dot),
            shakashaka::Coordinate{0, 2},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::bottomRightCornerHalfShaded},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(shakashaka::Cell::Type::dot),
            shakashaka::Coordinate{0, 2},
            true}));

INSTANTIATE_TEST_SUITE_P(
    settingTheShadedCell, Board_Parametrized,
    ::testing::Values(
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(shakashaka::Cell::Type::upperLeftCornerHalfShaded),
            shakashaka::Coordinate{0, 0},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(
                shakashaka::Cell::Type::upperRightCornerHalfShaded),
            shakashaka::Coordinate{0, 0},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(
                shakashaka::Cell::Type::bottomRightCornerHalfShaded),
            shakashaka::Coordinate{0, 0},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(
                shakashaka::Cell::Type::bottomLeftCornerHalfShaded),
            shakashaka::Coordinate{0, 0},
            true}));

INSTANTIATE_TEST_SUITE_P(
    settingCellsUpperAZeroCell, Board_Parametrized,
    ::testing::Values(
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, 0, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(
                shakashaka::Cell::Type::bottomLeftCornerHalfShaded),
            shakashaka::Coordinate{0, 1},
            false},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, 0, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(
                shakashaka::Cell::Type::bottomRightCornerHalfShaded),
            shakashaka::Coordinate{0, 1},
            false},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, 0, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(shakashaka::Cell::Type::upperLeftCornerHalfShaded),
            shakashaka::Coordinate{0, 1},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, 0, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(
                shakashaka::Cell::Type::upperRightCornerHalfShaded),
            shakashaka::Coordinate{0, 1},
            true}));

INSTANTIATE_TEST_SUITE_P(
    settingCellsBottomAZeroCell, Board_Parametrized,
    ::testing::Values(
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, 0, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(
                shakashaka::Cell::Type::bottomLeftCornerHalfShaded),
            shakashaka::Coordinate{2, 1},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, 0, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(
                shakashaka::Cell::Type::bottomRightCornerHalfShaded),
            shakashaka::Coordinate{2, 1},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, 0, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(shakashaka::Cell::Type::upperLeftCornerHalfShaded),
            shakashaka::Coordinate{2, 1},
            false},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, 0, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(
                shakashaka::Cell::Type::upperRightCornerHalfShaded),
            shakashaka::Coordinate{2, 1},
            false}));

INSTANTIATE_TEST_SUITE_P(
    settingCellsLeftAZeroCell, Board_Parametrized,
    ::testing::Values(
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, 0, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(
                shakashaka::Cell::Type::bottomRightCornerHalfShaded),
            shakashaka::Coordinate{1, 0},
            false},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, 0, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(
                shakashaka::Cell::Type::upperRightCornerHalfShaded),
            shakashaka::Coordinate{1, 0},
            false},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, 0, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(shakashaka::Cell::Type::upperLeftCornerHalfShaded),
            shakashaka::Coordinate{1, 0},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, 0, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(
                shakashaka::Cell::Type::bottomLeftCornerHalfShaded),
            shakashaka::Coordinate{1, 0},
            true}));

INSTANTIATE_TEST_SUITE_P(
    settingCellsRightAZeroCell, Board_Parametrized,
    ::testing::Values(
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, 0, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(
                shakashaka::Cell::Type::bottomRightCornerHalfShaded),
            shakashaka::Coordinate{1, 2},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, 0, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(
                shakashaka::Cell::Type::upperRightCornerHalfShaded),
            shakashaka::Coordinate{1, 2},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, 0, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(shakashaka::Cell::Type::upperLeftCornerHalfShaded),
            shakashaka::Coordinate{1, 2},
            false},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, 0, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(
                shakashaka::Cell::Type::bottomLeftCornerHalfShaded),
            shakashaka::Coordinate{1, 2},
            false}));

INSTANTIATE_TEST_SUITE_P(
    settingDotAroundZeroCell, Board_Parametrized,
    ::testing::Values(
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, 0, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(shakashaka::Cell::Type::dot),
            shakashaka::Coordinate{0, 1},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, 0, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(shakashaka::Cell::Type::dot),
            shakashaka::Coordinate{1, 0},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, 0, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(shakashaka::Cell::Type::dot),
            shakashaka::Coordinate{1, 2},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, 0, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(shakashaka::Cell::Type::dot),
            shakashaka::Coordinate{2, 1},
            true}));

INSTANTIATE_TEST_SUITE_P(
    settingDotAroundNumberCell, Board_Parametrized,
    ::testing::Values(
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::upperRightCornerHalfShaded, 2},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(
                shakashaka::Cell::Type::upperRightCornerHalfShaded),
            shakashaka::Coordinate{1, 2},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::upperRightCornerHalfShaded, 2},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::upperLeftCornerHalfShaded},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(shakashaka::Cell::Type::upperLeftCornerHalfShaded),
            shakashaka::Coordinate{1, 2},
            false},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::bottomLeftCornerHalfShaded,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::upperRightCornerHalfShaded, 3,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::upperRightCornerHalfShaded,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(shakashaka::Cell::Type::upperLeftCornerHalfShaded),
            shakashaka::Coordinate{2, 1},
            false},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::bottomLeftCornerHalfShaded,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::upperRightCornerHalfShaded, 4,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(shakashaka::Cell::Type::upperLeftCornerHalfShaded),
            shakashaka::Coordinate{2, 1},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::upperRightCornerHalfShaded,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::upperLeftCornerHalfShaded, 4,
              shakashaka::Cell::Type::upperRightCornerHalfShaded},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(
                shakashaka::Cell::Type::bottomLeftCornerHalfShaded),
            shakashaka::Coordinate{2, 1},
            true},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::bottomLeftCornerHalfShaded,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::bottomRightCornerHalfShaded, 3,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(
                shakashaka::Cell::Type::upperRightCornerHalfShaded),
            shakashaka::Coordinate{2, 1},
            true}));

INSTANTIATE_TEST_SUITE_P(
    settingCellOnFullShadedCell, Board_Parametrized,
    ::testing::Values(
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::fullyShaded,
              shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(
                shakashaka::Cell::Type::upperRightCornerHalfShaded),
            shakashaka::Coordinate{0, 0},
            false},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::fullyShaded, 2,
              shakashaka::Cell::Type::upperLeftCornerHalfShaded},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::fullyShaded},
             {shakashaka::Cell::Type::empty, shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(shakashaka::Cell::Type::upperLeftCornerHalfShaded),
            shakashaka::Coordinate{1, 2},
            false},
        BoardAndResultSetCell{
            {{shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::bottomLeftCornerHalfShaded,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::upperRightCornerHalfShaded, 3,
              shakashaka::Cell::Type::empty},
             {shakashaka::Cell::Type::empty,
              shakashaka::Cell::Type::upperRightCornerHalfShaded,
              shakashaka::Cell::Type::empty}},
            shakashaka::Cell(shakashaka::Cell::Type::fullyShaded),
            shakashaka::Coordinate{2, 1},
            false}));