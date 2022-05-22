#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "shakashaka/Shakashaka.hh"
#include <vector>

shakashaka::Cell::Cell(const std::size_t number)
    : type_{Type::number}, number_{number}
{
}

shakashaka::Cell::Cell(const Type type) : type_{type}
{
}

shakashaka::Cell::Type shakashaka::Cell::getType() const
{
    return type_;
}

bool shakashaka::Cell::isNumber() const
{
    return type_ == Type::number;
}

bool shakashaka::Cell::isZeroNumber() const
{
    return type_ == Type::number and number_ == 0;
}

bool shakashaka::Cell::isDot() const
{
    return type_ == Type::dot;
}

bool shakashaka::Cell::isBottomType() const
{
    return type_ == Type::bottomRightCornerHalfShaded or
           type_ == Type::bottomLeftCornerHalfShaded;
}

bool shakashaka::Cell::isUpperType() const
{
    return type_ == Type::upperRightCornerHalfShaded or
           type_ == Type::upperLeftCornerHalfShaded;
}

bool shakashaka::Cell::isLeftType() const
{
    return type_ == Type::bottomLeftCornerHalfShaded or
           type_ == Type::upperLeftCornerHalfShaded;
}

bool shakashaka::Cell::isRightType() const
{
    return type_ == Type::bottomRightCornerHalfShaded or
           type_ == Type::upperRightCornerHalfShaded;
}
std::size_t shakashaka::Cell::getNumber() const
{
    return number_.value_or(-1);
}

shakashaka::Board::Board(const std::size_t size)
    : Board({size, row_t(size, Cell::Type::empty)})
{
}

shakashaka::Board::Board(const board_t &board) : board_{board}
{
}

bool shakashaka::Board::isInRangeOfBoard(const Coordinate coordinate) const
{
    return board_.size() > coordinate.row and
           board_.front().size() > coordinate.col;
}

bool shakashaka::Board::isSettable(const Cell &cell,
                                   const Coordinate &coordinate) const
{
    if (not isInRangeOfBoard(coordinate) or cell.isNumber() or
        getCell(coordinate).isNumber())
    {
        return false;
    }
    if (cell.isDot())
    {
        return true;
    }
    for (const auto &neighbour : getNeighbours(coordinate))
    {
        if (const auto isAdjacent = cell.isAdjacent(neighbour);
            isAdjacent and neighbour.cell.isZeroNumber())
        {
            return false;
        }
        else if (isAdjacent and neighbour.cell.isNumber())
        {
            const auto neighboursNeighbour =
                getNeighbours(neighbour.coordinate);
            auto res =
                neighbour.cell.countAdjacentNeighbours(neighboursNeighbour);
            spdlog::info(res);
            if (neighbour.cell.getNumber() < (res + 1))
            {
                return false;
            }
        }
    }
    return true;
}

std::size_t shakashaka::Cell::countAdjacentNeighbours(
    const Board::neighbours_t &neighbours) const
{
    const auto counter = std::count_if(
        neighbours.cbegin(), neighbours.cend(),
        [this](const auto &neighbour) { return isAdjacent(neighbour); });
    return static_cast<std::size_t>(counter);
}

bool shakashaka::Cell::isAdjacent(const Neighbour &neighbour) const
{
    switch (const auto &neighbourCell = neighbour.cell; neighbour.position)
    {
    case Neighbour::Position::up:
        return (neighbourCell.isBottomType() or neighbourCell.isNumber()) and
               (isNumber() or isUpperType());
    case Neighbour::Position::down:
        return (neighbourCell.isUpperType() or neighbourCell.isNumber()) and
               (isNumber() or isBottomType());
    case Neighbour::Position::left:
        return (neighbourCell.isRightType() or neighbourCell.isNumber()) and
               (isNumber() or isLeftType());
    case Neighbour::Position::right:
        return (neighbourCell.isLeftType() or neighbourCell.isNumber()) and
               (isNumber() or isRightType());
    default:
        return false;
    }
}

shakashaka::Board::neighbours_t shakashaka::Board::getNeighbours(
    const Coordinate &coordinate) const
{
    std::vector<std::pair<Neighbour::Position, Coordinate>>
        availableNeighbours = {
            {Neighbour::Position::up, {coordinate.row - 1, coordinate.col}},
            {Neighbour::Position::down, {coordinate.row + 1, coordinate.col}},
            {Neighbour::Position::left, {coordinate.row, coordinate.col - 1}},
            {Neighbour::Position::right, {coordinate.row, coordinate.col + 1}}};
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

shakashaka::Cell shakashaka::Board::getCell(const Coordinate &coordinate) const
{
    if (not isInRangeOfBoard(coordinate))
    {
        // todo: specify the type of exception
        throw std::exception();
    }
    return board_.at(coordinate.row).at(coordinate.col);
}

bool shakashaka::Board::setCell(const Cell &cell, const Coordinate &coordinate)
{
    if (not isSettable(cell, coordinate))
    {
        return false;
    }
    board_.at(coordinate.row).at(coordinate.col) = cell;
    return true;
}