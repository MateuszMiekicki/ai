#ifndef AI_NEIGHBOUR_HH
#define AI_NEIGHBOUR_HH
#include <Coordinate.hh>

namespace shakashaka::board
{
class Coordinate;
class Cell;
struct Neighbour
{
    enum class Position
    {
        upper = 0,
        bottom,
        left,
        right,
        upperLeft,
        upperRight,
        bottomRight,
        bottomLeft
    };
    Neighbour() = delete;
    Position position;
    Coordinate coordinate;
    Cell cell;
};
} // namespace shakashaka::board
#endif // AI_NEIGHBOUR_HH
