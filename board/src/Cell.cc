#include "Cell.hh"
#include "Neighbour.hh"
#include <algorithm>

shakashaka::board::Cell::Cell(const std::size_t number) : type_{Type::number}, number_{number}
{
}

shakashaka::board::Cell::Cell(const Type type) : type_{type}
{
}

shakashaka::board::Cell::Type shakashaka::board::Cell::getType() const
{
    return type_;
}

bool shakashaka::board::Cell::isNumber() const
{
    return type_ == Type::number;
}

bool shakashaka::board::Cell::isZeroNumber() const
{
    return type_ == Type::number and number_ == 0;
}

bool shakashaka::board::Cell::isDot() const
{
    return type_ == Type::dot;
}

bool shakashaka::board::Cell::isBottomType() const
{
    return type_ == Type::bottomRightCornerHalfShaded or type_ == Type::bottomLeftCornerHalfShaded;
}

bool shakashaka::board::Cell::isUpperType() const
{
    return type_ == Type::upperRightCornerHalfShaded or type_ == Type::upperLeftCornerHalfShaded;
}

bool shakashaka::board::Cell::isLeftType() const
{
    return type_ == Type::bottomLeftCornerHalfShaded or type_ == Type::upperLeftCornerHalfShaded;
}

bool shakashaka::board::Cell::isRightType() const
{
    return type_ == Type::bottomRightCornerHalfShaded or type_ == Type::upperRightCornerHalfShaded;
}

std::size_t shakashaka::board::Cell::getNumber() const
{
    return number_.value_or(-1);
}

bool shakashaka::board::Cell::isSetable() const
{
    return (type_ not_eq Type::number) and (type_ not_eq Type::fullyShaded);
}

std::size_t shakashaka::board::Cell::countAdjacentNeighbours(
    const Board::neighbours_t &neighbours) const
{
    const auto counter =
        std::count_if(neighbours.cbegin(), neighbours.cend(),
                      [this](const auto &neighbour) { return isAdjacent(neighbour); });
    return static_cast<std::size_t>(counter);
}

bool shakashaka::board::Cell::isAdjacent(const Neighbour &neighbour) const
{
    switch (const auto &neighbourCell = neighbour.cell; neighbour.position)
    {
    case Neighbour::Position::upper:
        return (neighbourCell.isBottomType() or neighbourCell.isNumber()) and
               (isNumber() or isUpperType());
    case Neighbour::Position::bottom:
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
bool shakashaka::board::Cell::isAdjacentToZero(const Neighbour &neighbour) const
{
    return isAdjacent(neighbour) and neighbour.cell.isZeroNumber();
}

bool shakashaka::board::Cell::isAdjacentToNumber(const Neighbour &neighbour) const
{
    return isAdjacent(neighbour) and neighbour.cell.isNumber();
}
bool shakashaka::board::Cell::isEmpty() const
{
    return type_ == Type::empty;
}
