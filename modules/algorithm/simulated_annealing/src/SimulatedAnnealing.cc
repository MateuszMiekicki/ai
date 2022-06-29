#include "SimulatedAnnealing.hh"
#include "Bin.hh"
#include "Item.hh"

namespace knapsack::algorithm
{
SimulatedAnnealing::SimulatedAnnealing(Bin &bin, const items_t &items, const Parameters &parameters)
    : bin_{bin}, items_{items}, parameters_{parameters}
{

    prepareItems(items_, bin_.capacity(), random);
}

Ratio SimulatedAnnealing::probabilityOfChoosingWorseSolution(const Bin &betterBin,
                                                             const Bin &worseBin,
                                                             const Temperature temperature) const
{
    return std::exp((worseBin.value() - betterBin.value()) / temperature);
}

Ratio SimulatedAnnealing::drawProbability() const
{
    thread_local std::mt19937 engine;
    std::uniform_real_distribution<long double> uniformRealDistribution(0.0L, 1.0L);
    return {(uniformRealDistribution(engine))};
}

void SimulatedAnnealing::objectiveFunction(Temperature &temperature)
{
    Bin current{bin_.capacity()};
    current.fill(items_);
    if (bin_.value() <= current.value())
    {
        bin_ = current;
    }
    else if (const auto probability = drawProbability();
             probabilityOfChoosingWorseSolution(bin_, current, temperature) > probability)
    {
        bin_ = current;
        temperature = temperature.value * probability.value;
    }
}

// ToDo: change the way items are generated to be shuffle, permutations are average
void SimulatedAnnealing::solve()
{
    auto temperature = parameters_.temperature.value();
    //    do
    //    {
    //        objectiveFunction(temperature);
    //    } while (--parameters_.iteration and
    //             std::next_permutation(std::rbegin(items_), std::rend(items_)));

    std::random_device rd;
    std::mt19937 g(rd());
    do
    {
        std::shuffle(items_.begin(), items_.end(), g);
        objectiveFunction(temperature);
    } while (--parameters_.iteration);
}
} // namespace knapsack::algorithm