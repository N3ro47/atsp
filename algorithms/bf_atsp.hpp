#ifndef BF_ATSP_HPP
#define BF_ATSP_HPP

#include "atspsolver.hpp"

class BFSolver : public ATSPSolver{
    private:
        int bestCost;
        int* bestPath;

        int numCities;
        int** distanceMatrix;

    public:
        BFSolver(int** inputMatrix, const int numCities);
        void solve() override;
        void printResults() override;
        ~BFSolver();
};

#endif // BF_ATSP_HPP