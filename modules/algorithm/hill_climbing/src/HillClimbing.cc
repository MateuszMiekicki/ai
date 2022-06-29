#include "HillClimbing.hh"
#include "Bin.hh"
#include "Item.hh"

namespace knapsack::algorithm
{
HillClimbing::HillClimbing(Bin &bin, const items_t &items, const Parameters &parameters)
    : bin_{bin}, items_{items}, parameters_{parameters}
{
}

void HillClimbing::objectiveFunction()
{
    Bin current{bin_.capacity()};
    current.fill(items_);
    if (bin_.value() < current.value())
    {
        bin_ = current;
    }
}

void HillClimbing::solve()
{
    do
    {
        objectiveFunction();
    } while (--parameters_.iteration and
             std::next_permutation(std::rbegin(items_), std::rend(items_)));
}
} // namespace knapsack::algorithm