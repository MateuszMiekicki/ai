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
    using gene_t = Item;
    using chromosome_t = std::vector<gene_t>;
    using population_t = std::vector<chromosome_t>;
    using parrents_t = std::pair<chromosome_t, chromosome_t>;
    using pairParents_t = std::pair<parrents_t, parrents_t>;

    Bin &bin_;
    items_t items_;
    const Parameters parameters_;
    void objectiveFunction();
    population_t generateInitialPopulations(const items_t &items) const;
    population_t generatePopulations(const population_t &population) const;
    void selection(population_t &population) const;
    parrents_t tournamentSelection(const population_t &population) const;
    pairParents_t drawTwoPairsOfParents(const population_t &population) const;
    parrents_t evaluateParentPair(const pairParents_t &pairParents) const;
    chromosome_t crossover(const chromosome_t &first, const chromosome_t &second) const;

  public:
    Genetic() = delete;
    Genetic(Bin &bin, const items_t &items, const Parameters &parameters);
    void solve() override;
};
} // namespace knapsack::algorithm
#endif // KNAPSACK_GENETIC_HH
