#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <string>
#include "matrixreader.hpp"
#include "algorithms/atspsolver.hpp"
// Add dynamic programming ATSP solver include when available

class Menu {
public:
    Menu() = default;
    void displayMenu();

private:
    void loadMatrix();
    void manualMode();
    void automaticMode();
    void solveATSP(int** matrix, int size);
    void printResult(int cost, int* path, int pathSize);

    MatrixReader matrixReader;
    ATSPSolver* solver = nullptr;
};

#endif
