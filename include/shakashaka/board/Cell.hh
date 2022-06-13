#ifndef AI_CELL_HH
#define AI_CELL_HH
#include <Board.hh>
#include <cstdint>
#include <optional>

namespace shakashaka::board
{
class Neighbour;
class Cell
{
  public:
    enum class Type
    {
        empty = 0,
        fullyShaded,
        dot,
        number,
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
    bool isSetable() const;
    bool isEmpty() const;
    std::size_t countAdjacentNeighbours(
        const Board::neighbours_t &neighbour) const;
    std::size_t getNumber() const;
    inline bool operator==(const Cell &oth) const
    {
        return type_ == oth.type_;
    }
};
} // namespace shakashaka::board
#endif // AI_CELL_HH
