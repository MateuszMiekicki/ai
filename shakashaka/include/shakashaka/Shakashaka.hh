#ifndef AI_SHAKASHAKA_HH
#define AI_SHAKASHAKA_HH
#include "Logger.hh"
#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>

namespace shakashaka
{
struct Coordinate
{
    using row_t = std::size_t;
    using col_t = std::size_t;
    row_t row;
    col_t col;
};

struct Neighbour;
class Cell;
class Board
{
  public:
    using row_t = std::vector<Cell>;
    using board_t = std::vector<row_t>;
    using neighbours_t = std::vector<Neighbour>;

    Board(const std::size_t size);
    Board(const board_t &board);

  private:
    board_t board_ = {};

    bool isInRangeOfBoard(const Coordinate coordinate) const;
    bool isSettable(const Cell &cell, const Coordinate &coordinate) const;
    neighbours_t getNeighbours(const Coordinate &coordinate) const;

  public:
    Cell getCell(const Coordinate &coordinate) const;
    bool setCell(const Cell &cell, const Coordinate &coordinate);
};

class Cell
{
  public:
    enum class Type
    {
        empty = 0,
        number,
        dot,
        upperLeftCornerHalfShaded,
        bottomLeftCornerHalfShaded,
        upperRightCornerHalfShaded,
        bottomRightCornerHalfShaded
    };

  private:
    Type type_ = Type::empty;
    std::optional<std::size_t> number_{std::nullopt};

  public:
    Cell(const Type type);
    Cell(const std::size_t number);
    Type getType() const;
    bool isNumber() const;
    bool isZeroNumber() const;
    bool isAdjacent(const Neighbour &neighbour) const;
    bool isAdjacentToZero(const Neighbour &neighbour) const;
    bool isAdjacentToNumber(const Neighbour &neighbour) const;
    bool isDot() const;
    bool isBottomType() const;
    bool isUpperType() const;
    bool isLeftType() const;
    bool isRightType() const;
    std::size_t countAdjacentNeighbours(
        const Board::neighbours_t &neighbour) const;
    std::size_t getNumber() const;
};

struct Neighbour
{
    enum class Position
    {
        up = 0,
        down,
        left,
        right
    };
    Neighbour() = delete;
    Position position;
    Coordinate coordinate;
    Cell cell;
};
} // namespace shakashaka
#endif // AI_SHAKASHAKA_HH
