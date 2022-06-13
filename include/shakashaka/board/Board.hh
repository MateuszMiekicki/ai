#ifndef AI_BOARD_HH
#define AI_BOARD_HH
#include <vector>

namespace shakashaka::board
{
class Cell;
class Coordinate;
class Neighbour;

class Board
{
  public:
    using row_t = std::vector<Cell>;
    using board_t = std::vector<row_t>;
    using neighbours_t = std::vector<Neighbour>;
    using corners_t = std::vector<Neighbour>;

    Board(const std::size_t size);
    Board(const board_t &board);

  private:
    board_t board_ = {};

    bool isInRangeOfBoard(const Coordinate coordinate) const;
    bool isSettable(const Cell &cell, const Coordinate &coordinate) const;

  public:
    neighbours_t getNeighbours(const Coordinate &coordinate,
                               const bool withDiagonal = true) const;
    corners_t getCornersCoordinates() const;
    Cell getCell(const Coordinate &coordinate) const;
    bool setCell(const Cell &cell, const Coordinate &coordinate);
    inline bool operator==(const Board &oth) const
    {
        return board_ == oth.board_;
    }
};
} // namespace shakashaka::board
#endif // AI_BOARD_HH
