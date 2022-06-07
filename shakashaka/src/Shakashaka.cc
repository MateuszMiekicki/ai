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

bool shakashaka::Cell::isSetable() const
{
    return (type_ not_eq Type::number) and (type_ not_eq Type::fullyShaded);
}

shakashaka::Board::Board(const std::size_t size)
    : Board({size, row_t(size, Cell::Type::empty)})
{
}

shakashaka::Board::Board(const board_t &board) : board_{board}
{
    //    try
    //    {
    //        logger_ = spdlog::basic_logger_mt(
    //            logger::shakashaka.loggerName,
    //            logger::shakashaka.loggerOutputFile.value());
    //        logger_->set_level(spdlog::level::trace);
    //        logger_->set_pattern(logger::defaultLoggerFormat);
    //    }
    //    catch (const spdlog::spdlog_ex &ex)
    //    {
    //        std::cerr << "Log init failed: " << ex.what() << '\n';
    //    }
}

bool shakashaka::Board::isInRangeOfBoard(const Coordinate coordinate) const
{
    return board_.size() > coordinate.row and
           board_.front().size() > coordinate.col;
}

bool shakashaka::Board::isSettable(const Cell &cell,
                                   const Coordinate &coordinate) const
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
                    neighbour.cell.countAdjacentNeighbours(
                        getNeighbours(neighbour.coordinate));
                neighbour.cell.getNumber() < (neighboursCounter + 1))
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
bool shakashaka::Cell::isAdjacentToZero(const Neighbour &neighbour) const
{
    return isAdjacent(neighbour) and neighbour.cell.isZeroNumber();
}

bool shakashaka::Cell::isAdjacentToNumber(const Neighbour &neighbour) const
{
    return isAdjacent(neighbour) and neighbour.cell.isNumber();
}
bool shakashaka::Cell::isEmpty() const
{
    return type_ == Type::empty;
}

shakashaka::Board::neighbours_t shakashaka::Board::getNeighbours(
    const Coordinate &coordinate) const
{
    std::vector<std::pair<Neighbour::Position, Coordinate>>
        availableNeighbours = {
            {Neighbour::Position::up, {coordinate.row - 1, coordinate.col}},
            {Neighbour::Position::leftUp,
             {coordinate.row - 1, coordinate.col - 1}},
            {Neighbour::Position::rightUp,
             {coordinate.row - 1, coordinate.col + 1}},
            {Neighbour::Position::down, {coordinate.row + 1, coordinate.col}},
            {Neighbour::Position::leftDown,
             {coordinate.row + 1, coordinate.col - 1}},
            {Neighbour::Position::rightDown,
             {coordinate.row + 1, coordinate.col + 1}},
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

bool shakashaka::Board::isSolved() const
{
    return false;
}

void shakashaka::Board::prepareBoardToSolve()
{
    prepareCorner();
}

void shakashaka::Board::prepareCorner()
{
    if (board_.empty())
    {
        return;
    }
    for (const auto &[position, coordinate, cell] : getCornersCoordinates())
    {
        const auto neighbours = getNeighbours(coordinate);
        if (const auto hasAllNeighboursEmpty = std::all_of(
                neighbours.cbegin(), neighbours.cend(),
                [](const auto neighbour) { return neighbour.cell.isEmpty(); });
            cell.isSetable() and not hasAllNeighboursEmpty)
        {
            if (const auto hasDiagonalNeighbour = std::any_of(
                    neighbours.begin(), neighbours.end(),
                    [](const auto &neighbour) {
                        const auto diagonalPosition = {
                            Neighbour::Position::leftUp,
                            Neighbour::Position::leftDown,
                            Neighbour::Position::rightUp,
                            Neighbour::Position::rightDown};
                        return not neighbour.cell.isEmpty() and
                               std::any_of(diagonalPosition.begin(),
                                           diagonalPosition.end(),
                                           [&neighbour](const auto pos) {
                                               return pos == neighbour.position;
                                           });
                    });
                hasDiagonalNeighbour)
            {
                std::for_each(neighbours.begin(), neighbours.end(),
                              [this](const auto x) {
                                  setCell(Cell::Type::dot, x.coordinate);
                              });
            }
            setCell(Cell::Type::dot, coordinate);
        }
    }
}

shakashaka::Board::corners_t shakashaka::Board::getCornersCoordinates() const
{
    const auto lastRowIndex = board_.size() - 1;
    const auto lastColIndex = board_.at(0).size() - 1;
    const std::vector<std::pair<Neighbour::Position, Coordinate>>
        cornersCoordinate = {
            {Neighbour::Position::leftUp, Coordinate{0, 0}},
            {Neighbour::Position::rightUp, Coordinate{0, lastColIndex}},
            {Neighbour::Position::leftDown, Coordinate{lastRowIndex, 0}},
            {Neighbour::Position::leftUp,
             Coordinate{lastRowIndex, lastColIndex}},
        };
    corners_t result;
    std::for_each(cornersCoordinate.cbegin(), cornersCoordinate.cend(),
                  [this, &result](const auto cc) {
                      if (isInRangeOfBoard(cc.second))
                      {
                          result.push_back(Neighbour{cc.first, cc.second,
                                                     getCell(cc.second)});
                      }
                  });
    return result;
}
