#ifndef ATSPSOLVER_HPP
#define ATSPSOLVER_HPP

class ATSPSolver {
public:
    virtual void solve() = 0;

    virtual void printResults() = 0;
    virtual ~ATSPSolver() {}
    virtual int getBestCost(){ return -1; }
    virtual int* getBestPath(){ return nullptr; }

};
#endif // ATSPSOLVER_HPP

