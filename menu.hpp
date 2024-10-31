#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <string>
#include "matrixreader.hpp"
#include "algorithms/bf_atsp.hpp"
#include "algorithms/bb_atsp.hpp"
// Add dynamic programming ATSP solver include when available

class Menu {
public:
    Menu() = default;
    void displayMenu();

private:
    void manualMode();
    void automaticMode();
    void solveATSP(int** matrix, int size);
    void printResult(int cost, int* path, int pathSize);

    MatrixReader matrixReader;
    ATSPSolver* solver = nullptr;
};

#endif
