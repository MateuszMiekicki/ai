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

    using selectionMethod_t = std::function<parents_t(population_t)>;
    using evolutionMethod_t = std::function<parents_t(parents_t)>;

    Bin &bin_;
    items_t items_;
    const Parameters parameters_;

    chromosome_t generateChromosome(const items_t &items, const std::size_t amountOfGenes) const;
    population_t generatePopulation(const items_t &items) const;
    population_t generatePopulation(population_t population) const;

    void removeOverWeightGene(population_t &population) const;

    parents_t selection(population_t population, const selectionMethod_t &selectionMethod) const;
    static parents_t rankingMethod(population_t population);

    parents_t evolutionOperator(parents_t parents, const evolutionMethod_t &evolutionMethod) const;
    static parents_t onePointCrossover(parents_t parents);
    static parents_t uniformCrossover(parents_t parents);
    chromosome_t fitness(const population_t &population) const;
    void mutation(parents_t &parents) const;
    void mutation(chromosome_t &chromosome) const;
    void removeWeakest(population_t &population) const;


    chromosome_t objectFunction(const parents_t& parents)const;
  public:
    Genetic() = delete;
    Genetic(Bin &bin, const items_t &items, const Parameters &parameters);
    void solve() override;
};
} // namespace knapsack::algorithm
#endif // KNAPSACK_GENETIC_HH
