#ifndef ATSPSOLVER_HPP
#define ATSPSOLVER_HPP

class ATSPSolver {
public:
    virtual void solve() = 0;

    virtual void printResults() = 0;
    virtual ~ATSPSolver() {}

};
#endif // ATSPSOLVER_HPP

