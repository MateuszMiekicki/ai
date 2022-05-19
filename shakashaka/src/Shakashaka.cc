#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "shakashaka/Shakashaka.hh"
#include <string_view>
#include <vector>

shakashaka::Board::Cell::Cell(const Type t) : type{t}
{
}

shakashaka::Board::Cell::Cell(const unsigned n) : type{Type::number}, number{n}
{
}

std::string shakashaka::Board::Cell::toString() const
{
    std::string result;
    switch (type)
    {
    case Cell::Type::number: {
        result = "number: " + std::to_string(number.value_or(-1));
    }
    break;
    case Cell::Type::bottomLeftCornerHalfShaded: {
        result = "bottomLeftCornerHalfShaded";
    }
    break;
    case Cell::Type::bottomRightCornerHalfShaded: {
        result = "bottomRightCornerHalfShaded";
    }
    break;
    case Cell::Type::upperRightCornerHalfShaded: {
        result = "upperRightCornerHalfShaded";
    }
    break;
    case Cell::Type::upperLeftCornerHalfShaded: {
        result = "upperLeftCornerHalfShaded";
    }
    break;
    case Cell::Type::dot: {
        result = "dot";
    }
    break;
    case Cell::Type::empty: {
        result = "empty";
    }
    break;
    }
    return result;
}

shakashaka::Board::Board(const std::size_t size)
    : Board({size, row_t(size, Cell::Type::empty)})
{
}

shakashaka::Board::Board(const board_t &board) : board_(std::move(board))
{
    try
    {
        logger_ = spdlog::basic_logger_mt(
            logger::shakashaka.loggerName,
            logger::shakashaka.loggerOutputFile.value());
        logger_->set_level(spdlog::level::trace);
        logger_->set_pattern(logger::defaultLoggerFormat);
    }
    catch (const spdlog::spdlog_ex &ex)
    {
        // ToDo: handle it
    }
}

bool shakashaka::Board::isInRangeOfBoard(const Coordinate coordinate) const
{
    if (const auto inRange = board_.size() > coordinate.row and
                             board_.front().size() > coordinate.col;
        inRange)
    {
        return true;
    }
    SPDLOG_LOGGER_TRACE(
        logger_,
        "The coordinates specified(row: {}, col: {}) are out of "
        "range of the board.",
        coordinate.row, coordinate.col);
    return false;
}

shakashaka::Board::coordinateNeighborhoodCell_t shakashaka::Board::
    getNeighbours(const Coordinate coordinate) const
{
    auto setOfCoordinateToCheck = coordinateNeighborhoodCell_t{
        {Position::down, {coordinate.row + 1, coordinate.col}},
        {Position::up, {coordinate.row - 1, coordinate.col}},
        {Position::right, {coordinate.row, coordinate.col + 1}},
        {Position::left, {coordinate.row, coordinate.col - 1}}};
    for (const auto &[position, neighbourCoordinate] : setOfCoordinateToCheck)
    {
        if (not isInRangeOfBoard(neighbourCoordinate))
        {
            setOfCoordinateToCheck.erase(position);
        }
    }
    return setOfCoordinateToCheck;
}

bool shakashaka::Board::Cell::isNumberCell() const
{
    return (type == Cell::Type::number);
}

bool shakashaka::Board::Cell::isZeroCell() const
{
    return (type == Type::number and number == 0);
}

bool shakashaka::Board::Cell::isAdjacentCell(const Position p) const
{
    switch (p)
    {
    case Position::up: {
        return (type == Cell::Type::upperRightCornerHalfShaded or
                type == Cell::Type::upperLeftCornerHalfShaded);
    }
    case Position::down: {
        return (type == Cell::Type::bottomLeftCornerHalfShaded or
                type == Cell::Type::bottomRightCornerHalfShaded);
    }
    case Position::left: {
        return (type == Cell::Type::bottomLeftCornerHalfShaded or
                type == Cell::Type::upperLeftCornerHalfShaded);
    }
    case Position::right: {
        return (type == Cell::Type::bottomRightCornerHalfShaded or
                type == Cell::Type::upperRightCornerHalfShaded);
    }
    default: {
        return false;
    }
    }
}


std::size_t shakashaka::Board::numberOfAdjacentNeighbours(
    const Coordinate coordinate) const
{
    if (not isInRangeOfBoard(coordinate))
    {
        return 0;
    }
    std::size_t counter{0};
    const auto primaryCell = getCell(coordinate);
    for (const auto &[neighbourPosition, neighbourCoordinate] :
         getNeighbours(coordinate))
    {
        SPDLOG_LOGGER_DEBUG(logger_, "{}, {}", neighbourCoordinate.row,
                            neighbourCoordinate.col);
        if (primaryCell.isAdjacentCell(neighbourPosition))
        {
            counter++;
            SPDLOG_LOGGER_DEBUG(logger_, "{}", primaryCell.toString());
        }
    }
    SPDLOG_LOGGER_TRACE(logger_, "counter: {}", counter);
    return counter;
}

bool shakashaka::Board::isSettable(const Cell &cell,
                                   const Coordinate coordinate) const
{
    SPDLOG_LOGGER_TRACE(
        logger_,
        "Function begin. Type cell: {}. Coordinate: row: {}, cell: {}.",
        cell.toString(), coordinate.row, coordinate.col);
    if (not isInRangeOfBoard(coordinate) or cell.isNumberCell())
    {
        SPDLOG_LOGGER_TRACE(logger_,
                            "Function end: return false. The cell is out of "
                            "range of the board or the insertion is a number.");
        return false;
    }
    for (const auto &[neighbourPosition, neighbourCoordinate] :
         getNeighbours(coordinate))
    {
        {
            auto positionToString = [](const Position pos) {
                std::string result;
                switch (pos)
                {
                case Position::right: {
                    result = "right";
                }
                break;
                case Position::left: {
                    result = "left";
                }
                break;
                case Position::down: {
                    result = "down";
                }
                break;
                case Position::up: {
                    result = "up";
                }
                break;
                }
                return result;
            };
            const auto output =
                fmt::format("The neighbour in position {} "
                            "is in coordinates x:{}, y:{}",
                            positionToString(neighbourPosition),
                            neighbourCoordinate.row, neighbourCoordinate.col);
            SPDLOG_LOGGER_TRACE(logger_, output);
        }
        if (const auto neighbouringCell = getCell(neighbourCoordinate);
            neighbouringCell.isZeroCell() and
            cell.isAdjacentCell(neighbourPosition))
        {
            SPDLOG_LOGGER_TRACE(
                logger_,
                "The neighbouring cell is {} and the cell: {} is "
                "adjacent to it.",
                neighbouringCell.toString(), cell.toString());
            return false;
        }
        else if (neighbouringCell.isNumberCell() and
                 cell.isAdjacentCell(neighbourPosition))
        {
            const auto numberOfNeighbours =
                numberOfAdjacentNeighbours(neighbourCoordinate);
            SPDLOG_LOGGER_TRACE(
                logger_,
                "The neighbouring cell is {} and the cell: {} is "
                "adjacent to it.{}",
                neighbouringCell.toString(), cell.toString(),
                numberOfNeighbours);
            if (numberOfNeighbours == neighbouringCell.number)
            {
                SPDLOG_LOGGER_TRACE(logger_,
                                    "Function end: return false, maximum "
                                    "number of neighbours: {} ",
                                    numberOfNeighbours);
                return false;
            }
        }
    }
    SPDLOG_LOGGER_TRACE(logger_, "Function end: return true");
    return true;
}

bool shakashaka::Board::setCell(const Cell cell, const Coordinate coordinate)
{
    if (not isSettable(cell, coordinate))
    {
        return false;
    }
    board_.at(coordinate.row).at(coordinate.col) = cell;
    return true;
}

shakashaka::Board::Cell shakashaka::Board::getCell(
    const Coordinate coordinate) const
{
    if (not isInRangeOfBoard(coordinate))
    {
        // todo: make exception for this case
        //        throw
        throw std::exception();
    }
    return board_.at(coordinate.row).at((coordinate.col));
}