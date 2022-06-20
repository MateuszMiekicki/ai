#ifndef AI_SOLVER_HH
#define AI_SOLVER_HH
namespace shakashaka::board
{
class Board;
class Neighbour;
} // namespace shakashaka::board

namespace shakashaka::solver
{
class Solver
{
  public:
    shakashaka::board::Board board_;

    Solver(const shakashaka::board::Board &board);
    void prepareBoardToSolve();

  private:
    void prepareCorner();
    void setShadedFieldAroundCornerWithNumber(const shakashaka::board::Neighbour &neighbour);
    bool isSolved() const;
};
} // namespace shakashaka::solver
#endif // AI_SOLVER_HH
