#ifndef BB_ATSP_HPP
#define BB_ATSP_HPP
#include "atspsolver.hpp"

class BnBSolver : public ATSPSolver
{
public:
    BnBSolver(int **inputMatrix, int numCities);
    ~BnBSolver();

    void solve();
    void printResults();
    int calculateLowerBound(int *partialPath, int depth, bool *visited);
    int getBestCost();
    int* getBestPath() ;

private:
    int **distanceMatrix;
    int numCities;
    int *bestPath;
    int bestCost;

    void branchAndBound(int *path, int depth, bool *visited);
};

#endif // BB_ATSP_HPP