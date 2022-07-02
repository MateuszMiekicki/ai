#ifndef KNAPSACK_GENERATE_HH
#define KNAPSACK_GENERATE_HH
#include "Item.hh"
#include "Number.hh"
#include <fstream>
#include <iostream>
#include <random>
#include <string>
namespace knapsack
{
class Generate
{
    static auto &randomEngine()
    {
        std::random_device randomDevice;
        thread_local std::mt19937_64 engine(randomDevice());
        return engine;
    }

    static auto draw(long double max)
    {
        std::uniform_real_distribution<long double> uniformRealDistribution(0.0L, max);
        return (uniformRealDistribution(randomEngine()));
    }

  public:
    static items_t generate(const Weight maxWeight, const Value maxValue, std::size_t how)
    {
        auto items = items_t();
        items.reserve(how);
        for (auto i = how; i not_eq 0; --i)
        {
            items.emplace_back(draw(maxValue), draw(maxWeight));
        }
        return items;
    }

    static void write(std::ofstream &&file, const items_t &items)
    {
        for (auto &&item : items)
        {
            file << item.value() << ' ' << item.weight() << '\n';
        }
    }

    static items_t read(std::ifstream &&file)
    {
        items_t items;
        std::string line;
        while (std::getline(file, line))
        {
            if (auto found = line.find_first_of(";"); found not_eq std::string::npos)
            {
                const auto value = std::stold(std::string(std::begin(line), std::begin(line) + static_cast<long long>(found)));
                const auto weight = std::stold(std::string(std::begin(line) + static_cast<long long>(found)+1LL, std::end(line)));
                items.emplace_back(value, weight);
            }
        }
        return items;
    }
};
} // namespace knapsack
#endif // KNAPSACK_GENERATE_HH
