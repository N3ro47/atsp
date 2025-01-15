#ifndef SA_ATSP_HPP
#define SA_ATSP_HPP
#include "atspsolver.hpp"

class SASolver : public ATSPSolver
{
public:
    SASolver(int **inputMatrix, int numCities);
    ~SASolver();

    void solve() override;
    // Updated solve function with default parameters
    void solveWithParameters(  // Parameterized version with a distinct name
        double initialTemperature,
        double coolingRate,
        double minTemperature,
        int iterationsPerTemp
    );
    void printResults() override;
    int getBestCost() override;
    int* getBestPath() override;

private:
    int **distanceMatrix;
    int numCities;
    int *bestPath;
    int bestCost;
};

#endif // SA_ATSP_HPP
