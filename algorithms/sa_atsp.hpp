#ifndef SA_ATSP_HPP
#define SA_ATSP_HPP
#include "atspsolver.hpp"

class SASolver : public ATSPSolver
{
public:
    SASolver(int **inputMatrix, int numCities);
    ~SASolver();

    void solve();
    void printResults();
    int getBestCost();
    int* getBestPath();

private:
    int **distanceMatrix;
    int numCities;
    int *bestPath;
    int bestCost;

};

#endif // SA_ATSP_HPP