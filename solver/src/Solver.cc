#include "Solver.hh"
#include "Board.hh"
#include "Cell.hh"
#include "Neighbour.hh"
#include <algorithm>

shakashaka::solver::Solver::Solver(const shakashaka::board::Board &board) : board_{board}
{
}

bool shakashaka::solver::Solver::isSolved() const
{
    return false;
}

void shakashaka::solver::Solver::prepareBoardToSolve()
{
    prepareCorner();
}

void shakashaka::solver::Solver::prepareCorner()
{
    using namespace shakashaka::board;
    for (const auto &[position, coordinate, cell] : board_.getCornersCoordinates())
    {
        if (cell.isNumber())
        {
            if (cell.getNumber() > 2)
            {
                throw std::exception();
            }
            if (const auto neighbours = board_.getNeighbours(coordinate, false);
                cell.isZeroNumber())
            {
                std::for_each(neighbours.cbegin(), neighbours.cend(),
                              [this](const auto &neighbour) {
                                  board_.setCell(Cell::Type::dot, neighbour.coordinate);
                              });
            }
            else if (cell.getNumber() == 2)
            {
                switch (position)
                {
                case Neighbour::Position::bottomLeft: {
                    board_.setCell(Cell::Type::bottomLeftCornerHalfShaded,
                                   {coordinate.row - 1, coordinate.col});
                    board_.setCell(Cell::Type::bottomLeftCornerHalfShaded,
                                   {coordinate.row, coordinate.col + 1});
                }
                    continue;
                case Neighbour::Position::bottomRight: {
                    board_.setCell(Cell::Type::bottomRightCornerHalfShaded,
                                   {coordinate.row - 1, coordinate.col});
                    board_.setCell(Cell::Type::bottomRightCornerHalfShaded,
                                   {coordinate.row, coordinate.col - 1});
                }
                    continue;
                case Neighbour::Position::upperLeft: {
                    board_.setCell(Cell::Type::upperLeftCornerHalfShaded,
                                   {coordinate.row, coordinate.col + 1});
                    board_.setCell(Cell::Type::upperLeftCornerHalfShaded,
                                   {coordinate.row + 1, coordinate.col});
                }
                    continue;
                case Neighbour::Position::upperRight: {
                    board_.setCell(Cell::Type::upperRightCornerHalfShaded,
                                   {coordinate.row, coordinate.col - 1});
                    board_.setCell(Cell::Type::upperRightCornerHalfShaded,
                                   {coordinate.row + 1, coordinate.col});
                }
                    continue;
                default:
                    continue;
                }
            }
        }

        const auto neighbours = board_.getNeighbours(coordinate);
        if (const auto hasAllNeighboursEmpty =
                std::all_of(neighbours.cbegin(), neighbours.cend(),
                            [](const auto neighbour) { return neighbour.cell.isEmpty(); });
            cell.isSetable() and not hasAllNeighboursEmpty)
        {
            if (const auto hasDiagonalNeighbourFullyShaded = std::any_of(
                    neighbours.begin(), neighbours.end(),
                    [](const auto &neighbour) {
                        const auto diagonalPosition = {
                            Neighbour::Position::upperLeft, Neighbour::Position::bottomLeft,
                            Neighbour::Position::upperRight, Neighbour::Position::bottomRight};
                        return neighbour.cell.getType() == Cell::Type::fullyShaded and
                               std::any_of(diagonalPosition.begin(), diagonalPosition.end(),
                                           [&neighbour](const auto pos) {
                                               return pos == neighbour.position;
                                           });
                    });
                hasDiagonalNeighbourFullyShaded)
            {
                std::for_each(neighbours.begin(), neighbours.end(), [this](const auto x) {
                    board_.setCell(Cell::Type::dot, x.coordinate);
                });
            }
            board_.setCell(Cell::Type::dot, coordinate);
        }
    }
}

void shakashaka::solver::Solver::setShadedFieldAroundCornerWithNumber(
    const shakashaka::board::Neighbour &)
{
    // neighbour
}
