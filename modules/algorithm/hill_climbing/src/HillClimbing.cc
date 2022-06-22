#include "HillClimbing.hh"
#include "Bin.hh"
#include "Item.hh"

namespace knapsack::algorithm
{
HillClimbing::HillClimbing(const std::size_t iteration, Bin &bin, const items_t &items)
    : iteration_{iteration}, bin_{bin}, items_{items}
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
    } while (--iteration_ and std::next_permutation(std::rbegin(items_), std::rend(items_)));
}
} // namespace knapsack::algorithm