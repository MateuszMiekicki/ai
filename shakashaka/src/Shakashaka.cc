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
    return board_.size() > coordinate.row and
           board_.front().size() > coordinate.col;
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

bool shakashaka::Board::isSettable(const Cell cell,
                                   const Coordinate coordinate) const
{
    SPDLOG_LOGGER_TRACE(logger_, "Function begin");
    if (board_.size() not_eq 0 and cell.type not_eq Cell::Type::number and
        isInRangeOfBoard(coordinate))
    {
        auto traceLog = [this](std::string_view pn, const Coordinate c) {
            const auto output = fmt::format(
                "The neighbour in position {} is in coordinates x:{}, y:{}", pn,
                c.row, c.col);
            SPDLOG_LOGGER_TRACE(logger_, output);
        };

        auto isZeroCell = [](const Cell c) {
            return (c.type == Cell::Type::number and c.number == 0);
        };

        auto isAdjacentCell = [](const Cell c, const Position p) {
            switch (p)
            {
            case Position::up: {
                return (c.type == Cell::Type::upperRightCornerHalfShaded or
                        c.type == Cell::Type::upperLeftCornerHalfShaded);
            }
            case Position::down: {
                return (c.type == Cell::Type::bottomLeftCornerHalfShaded or
                        c.type == Cell::Type::bottomRightCornerHalfShaded);
            }
            case Position::left: {
                return (c.type == Cell::Type::bottomLeftCornerHalfShaded or
                        c.type == Cell::Type::upperLeftCornerHalfShaded);
            }
            case Position::right: {
                return (c.type == Cell::Type::bottomRightCornerHalfShaded or
                        c.type == Cell::Type::upperRightCornerHalfShaded);
            }
            }
            return false;
        };

        for (const auto &[position, neighbourCoordinate] :
             getNeighbours(coordinate))
        {
            traceLog("up", neighbourCoordinate);
            if (const auto neighbouringCell = getCell(neighbourCoordinate);
                isZeroCell(neighbouringCell) and isAdjacentCell(cell, position))
            {
                SPDLOG_LOGGER_TRACE(
                    logger_,
                    "The neighbouring cell is number 0 and the cell is "
                    "adjacent to it. Function end: return false");
                return false;
            }
        }

        SPDLOG_LOGGER_TRACE(logger_, "Function end: return true");
        return true;
    }
    SPDLOG_LOGGER_TRACE(logger_, "Function end: return false");
    return false;
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
