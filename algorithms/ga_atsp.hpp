#ifndef GA_ATSP_HPP
#define GA_ATSP_HPP
#include "atspsolver.hpp"

class GASolver : public ATSPSolver {
public:
    GASolver(int **inputMatrix, int numCities);
    ~GASolver();

    void solve() override;
    void solveWithParameters(  // Parameterized version
        int populationSize,
        int numGenerations,
        double mutationRate,
        double crossoverRate
    );
    void  printResults() override;
    int  getBestCost() override;
    int  *getBestPath() override;

private:
    int **distanceMatrix;
    int numCities;
    int *bestPath;
    int bestCost;

    void initializePopulation(int **population, int populationSize, int **distanceMatrix);
    void evaluateFitness(int **population, int populationSize, int *fitness);
    void selectParents(int **population, int populationSize, int **parents);
    void crossover(int *parent1, int *parent2, int *child);
    void mutate(int *path, double mutationRate);
    void mutateInversion(int * path, double mutationRate);
    int calculateCost(int *path);
};

#endif // GA_ATSP_HPP
