#ifndef KNAPSACK_GENETIC_HH
#define KNAPSACK_GENETIC_HH
#include "Bin.hh"
#include "Item.hh"
#include "Parameters.hh"
#include "Solver.hh"
#include <utility>

namespace knapsack::algorithm
{
class Genetic : public Solver
{
  private:
    using gene_t = std::pair<bool, Item>;
    using chromosome_t = std::vector<gene_t>;
    using population_t = std::vector<chromosome_t>;
    using parents_t = std::pair<chromosome_t, chromosome_t>;
    using pairParents_t = std::pair<parents_t, parents_t>;

    Bin &bin_;
    items_t items_;
    const Parameters parameters_;

    chromosome_t generateDefaultListOfChromosomes(const items_t &items) const;
    population_t generatePopulation(const population_t &population) const;
    parents_t selectTwoRandomChromosomes(const population_t &population)const;
    chromosome_t singlePointCrossover(const parents_t& parent) const;
    Value fitness(const chromosome_t& chromosome) const;

    population_t generateInitialPopulation(const items_t &items) const;

  public:
    Genetic() = delete;
    Genetic(Bin &bin, const items_t &items, const Parameters &parameters);
    void solve() override;
};
} // namespace knapsack::algorithm
#endif // KNAPSACK_GENETIC_HH
