#include "Generate.hh"
#include "Genetic.hh"
#include "HillClimbing.hh"
#include "Parameters.hh"
#include "SimulatedAnnealing.hh"
#include "Solver.hh"
#include "Timer.hh"
#include <fstream>
#include <memory>
int main()
{
    using namespace knapsack::algorithm;
    using namespace knapsack;
    auto parameters = Parameters(10000);
    parameters.probabilityOfMutation = .1;
    parameters.amountOfChromosomes = 1000;
    parameters.temperature = 100;
    const auto binCapacity = Weight{150};
    std::ifstream file("test1.csv");
    const auto items = Generate::read(std::move(file));
    {
        std::cerr << "---------------" << std::endl;
        auto bin = Bin(binCapacity);
        auto randomItems = items;
        prepareItems(randomItems, bin.capacity(), random);
        std::unique_ptr<Solver> solver =
            std::make_unique<HillClimbing>(bin, randomItems, parameters);
        std::cerr << "HillClimbing random: " << Timer::measurement(solver).count() << std::endl;
        std::cerr << "Bin value: " << bin.value() << ", weight: " << bin.weight() << std::endl;
    }
    {
        std::cerr << "---------------" << std::endl;
        auto bin = Bin(binCapacity);
        auto randomItems = items;
        prepareItems(randomItems, bin.capacity(), deterministic);
        std::unique_ptr<Solver> solver =
            std::make_unique<HillClimbing>(bin, randomItems, parameters);
        std::cerr << "HillClimbing deterministic: " << Timer::measurement(solver).count()
                  << std::endl;
        std::cerr << "Bin value: " << bin.value() << ", weight: " << bin.weight() << std::endl;
    }
    {
        std::cerr << "---------------" << std::endl;
        auto bin = Bin(binCapacity);
        std::unique_ptr<Solver> solver =
            std::make_unique<SimulatedAnnealing>(bin, items, parameters);
        std::cerr << "SimulatedAnnealing: " << Timer::measurement(solver).count() << std::endl;
        std::cerr << "Bin value: " << bin.value() << ", weight: " << bin.weight() << std::endl;
    }
    {
        std::cerr << "---------------" << std::endl;
        auto bin = Bin(binCapacity);
        std::unique_ptr<Solver> solver = std::make_unique<Genetic>(bin, items, parameters);
        std::cerr << "Genetic: " << Timer::measurement(solver).count() << std::endl;
        std::cerr << "Bin value: " << bin.value() << ", weight: " << bin.weight() << std::endl;
    }
}