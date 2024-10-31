#ifndef BB_ATSP_HPP
#define BB_ATSP_HPP

#include "atspsolver.hpp"

class BnBSolver : public ATSPSolver
{
    int **distanceMatrix;
    int numCities;
    int *bestPath;
    int bestCost;

    int calculateLowerBound(int *partialPath, int depth);
    void branchAndBound(int *path, int depth);

public:
    BnBSolver(int **inputMatrix, int numCities);
    ~BnBSolver();
    void solve();
    void printResults();
};

#endif // BB_ATSP_HPP