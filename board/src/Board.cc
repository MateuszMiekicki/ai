#include "Board.hh"
#include "Cell.hh"
#include "Coordinate.hh"
#include "Neighbour.hh"
#include <algorithm>

shakashaka::board::Board::Board(const std::size_t size)
    : Board({size, row_t(size, Cell::Type::empty)})
{
}

shakashaka::board::Board::Board(const board_t &board) : board_{board}
{
    // ToDo: change it, to more flexibility solution
    if (board_.empty())
    {
        throw std::exception();
    }
}

bool shakashaka::board::Board::isInRangeOfBoard(const Coordinate coordinate) const
{
    return board_.size() > coordinate.row and board_.front().size() > coordinate.col;
}

bool shakashaka::board::Board::isSettable(const Cell &cell, const Coordinate &coordinate) const
{
    // todo: refactoring this function Change statement to more readable
    if (not isInRangeOfBoard(coordinate) or not cell.isSetable() or
        not getCell(coordinate).isSetable())
    {
        return false;
    }
    if (cell.isDot())
    {
        return true;
    }
    for (const auto &neighbour : getNeighbours(coordinate))
    {
        if (cell.isAdjacentToZero(neighbour))
        {
            return false;
        }
        if (cell.isAdjacentToNumber(neighbour))
        {
            if (const auto neighboursCounter =
                    neighbour.cell.countAdjacentNeighbours(getNeighbours(neighbour.coordinate));
                neighbour.cell.getNumber() < (neighboursCounter + 1))
            {
                return false;
            }
        }
    }
    return true;
}

// todo: to split in two function, one with diagonal, one without
shakashaka::board::Board::neighbours_t shakashaka::board::Board::getNeighbours(
    const Coordinate &coordinate, const bool withDiagonal) const
{
    std::vector<std::pair<Neighbour::Position, Coordinate>> availableNeighbours = {
        {Neighbour::Position::upper, {coordinate.row - 1, coordinate.col}},
        {Neighbour::Position::bottom, {coordinate.row + 1, coordinate.col}},
        {Neighbour::Position::left, {coordinate.row, coordinate.col - 1}},
        {Neighbour::Position::right, {coordinate.row, coordinate.col + 1}}};
    if (withDiagonal)
    {
        availableNeighbours.push_back(
            {Neighbour::Position::bottomLeft, {coordinate.row + 1, coordinate.col - 1}});
        availableNeighbours.push_back(
            {Neighbour::Position::bottomRight, {coordinate.row + 1, coordinate.col + 1}});
        availableNeighbours.push_back(
            {Neighbour::Position::upperLeft, {coordinate.row - 1, coordinate.col - 1}});
        availableNeighbours.push_back(
            {Neighbour::Position::upperRight, {coordinate.row - 1, coordinate.col + 1}});
    }
    neighbours_t neighboursCoordinates;
    for (const auto &[pos, cor] : availableNeighbours)
    {
        if (isInRangeOfBoard(cor))
        {
            /// ToDo: change push_back to enplace_back
            neighboursCoordinates.push_back({pos, cor, getCell(cor)});
        }
    }
    return neighboursCoordinates;
}

shakashaka::board::Cell shakashaka::board::Board::getCell(const Coordinate &coordinate) const
{
    if (not isInRangeOfBoard(coordinate))
    {
        // todo: specify the type of exception
        throw std::exception();
    }
    return board_.at(coordinate.row).at(coordinate.col);
}

bool shakashaka::board::Board::setCell(const Cell &cell, const Coordinate &coordinate)
{
    if (not isSettable(cell, coordinate))
    {
        return false;
    }
    board_.at(coordinate.row).at(coordinate.col) = cell;
    return true;
}

shakashaka::board::Board::corners_t shakashaka::board::Board::getCornersCoordinates() const
{
    const auto lastRowIndex = board_.size() - 1;
    const auto lastColIndex = board_.at(0).size() - 1;
    const std::vector<std::pair<Neighbour::Position, Coordinate>> cornersCoordinate = {
        {Neighbour::Position::upperLeft, Coordinate{0, 0}},
        {Neighbour::Position::upperRight, Coordinate{0, lastColIndex}},
        {Neighbour::Position::bottomLeft, Coordinate{lastRowIndex, 0}},
        {Neighbour::Position::bottomRight, Coordinate{lastRowIndex, lastColIndex}},
    };
    corners_t result;
    std::for_each(cornersCoordinate.cbegin(), cornersCoordinate.cend(),
                  [this, &result](const auto cc) {
                      if (isInRangeOfBoard(cc.second))
                      {
                          result.push_back(Neighbour{cc.first, cc.second, getCell(cc.second)});
                      }
                  });
    return result;
}
