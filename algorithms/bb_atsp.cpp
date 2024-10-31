#include <iostream>
#include "bb_atsp.hpp"
#include "../utils/utils.hpp"

// Constructor
BnBSolver::BnBSolver(int **inputMatrix, int numCities) {
    this->numCities = numCities;
    this->distanceMatrix = new int *[numCities];
    for (int i = 0; i < numCities; i++) {
        this->distanceMatrix[i] = new int[numCities];
        for (int j = 0; j < numCities; j++) {
            this->distanceMatrix[i][j] = inputMatrix[i][j];
        }
    }

    this->bestPath = new int[numCities];
    this->bestCost = __INT_MAX__;
}

// Destructor
BnBSolver::~BnBSolver() {
    delete[] bestPath;
    for (int i = 0; i < numCities; i++) {
        delete[] distanceMatrix[i];
    }
    delete[] distanceMatrix;
}

// Calculate Lower Bound
int BnBSolver::calculateLowerBound(int *partialPath, int depth) {
    int cost = 0;
    for (int i = 0; i < depth - 1; i++) {
        cost += distanceMatrix[partialPath[i]][partialPath[i + 1]];
    }
    // Add a heuristic lower bound for remaining cities
    for (int i = depth; i < numCities; i++) {
        int minCost = __INT_MAX__;
        for (int j = 0; j < numCities; j++) {
            if (i != j && distanceMatrix[i][j] < minCost) {
                minCost = distanceMatrix[i][j];
            }
        }
        cost += minCost;
    }
    return cost;
}

// Branch and Bound with fixed start at city 0
void BnBSolver::branchAndBound(int *path, int depth) {
    if (depth == numCities) {
        int totalCost = 0;
        for (int i = 0; i < numCities - 1; i++) {
            totalCost += distanceMatrix[path[i]][path[i + 1]];
        }
        totalCost += distanceMatrix[path[numCities - 1]][path[0]]; // close the loop

        if (totalCost < bestCost) {
            bestCost = totalCost;
            for (int i = 0; i < numCities; i++) {
                bestPath[i] = path[i];
            }
        }
        return;
    }

    for (int i = depth; i < numCities; i++) {
        if (depth == 1 && i == 0) continue; // Skip swapping with city 0 to fix it as start
        swap(path[depth], path[i]);
        int lowerBound = calculateLowerBound(path, depth + 1);
        if (lowerBound < bestCost) {
            branchAndBound(path, depth + 1);
        }
        swap(path[depth], path[i]); // backtrack
    }
}

// Solve function
void BnBSolver::solve() {
    int *path = new int[numCities];
    for (int i = 0; i < numCities; i++) {
        path[i] = i;
    }

    branchAndBound(path, 1); // Start branching from depth 1 to fix city 0

    delete[] path;
}

// Print Results
void BnBSolver::printResults() {
    std::cout << "Minimum cost: " << bestCost << std::endl;
    std::cout << "Best path: ";
    for (int i = 0; i < numCities; i++) {
        std::cout << bestPath[i] << " ";
    }
    std::cout << std::endl;
}
