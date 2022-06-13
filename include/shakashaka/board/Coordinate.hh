#ifndef AI_COORDINATE_HH
#define AI_COORDINATE_HH
#include <cstddef>

namespace shakashaka::board
{
struct Coordinate
{
    using row_t = std::size_t;
    using col_t = std::size_t;
    row_t row;
    col_t col;
};
} // namespace shakashaka::board
#endif // AI_COORDINATE_HH
