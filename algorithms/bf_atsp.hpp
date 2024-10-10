#ifndef BF_ATSP_HPP
#define BF_ATSP_HPP

#include "atspsolver.hpp"
#include "vector.hpp"

class BFSolver : public ATSPSolver{
    private:
        int bestCost;
        int* bestPath;
        int** distanceMatrix;

    public:
        BFSolver(const int** matrix, const int num_cities);
        void solve() override;
        void printResults() override;
};

#endif // BF_ATSP_HPP