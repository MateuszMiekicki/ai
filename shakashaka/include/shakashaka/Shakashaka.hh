#ifndef AI_SHAKASHAKA_HH
#define AI_SHAKASHAKA_HH
#include "Logger.hh"
#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>

namespace shakashaka
{
class Board
{
  private:
    std::shared_ptr<spdlog::logger> logger_ = nullptr;
    enum class Position
    {
        up = 0,
        down,
        left,
        right
    };

  public:
    struct Coordinate
    {
        std::size_t row;
        std::size_t col;
    };
    struct Cell
    {
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
        std::string toString() const;
        Type type{Type::empty};
        std::optional<unsigned> number{std::nullopt};
        Cell() = default;
        Cell(const Type t);
        Cell(const unsigned n);

        bool isAdjacentCell(const Position p) const;
        bool isNumberCell() const;
        bool isZeroCell() const;
    };
    using row_t = std::vector<Cell>;
    using board_t = std::vector<row_t>;

  private:
    board_t board_ = {};

    using coordinateNeighborhoodCell_t =
        std::unordered_map<Position, Coordinate>;

    bool isInRangeOfBoard(const Coordinate coordinate) const;
    bool isSettable(const Cell &cell, const Coordinate coordinate) const;

    coordinateNeighborhoodCell_t getNeighbours(
        const Coordinate coordinate) const;
    std::size_t numberOfAdjacentNeighbours(const Coordinate coordinate) const;

    coordinateNeighborhoodCell_t coordinateNeighborhoodCell_ = {};
    bool isAdjacentCell(Cell f, Cell s)const;

  public:
    Board(const std::size_t size);
    Board(const board_t &board);
    bool setCell(const Cell cell, const Coordinate coordinate);
    Cell getCell(const Coordinate coordinate) const;
};
} // namespace shakashaka
#endif // AI_SHAKASHAKA_HH
