#include <iostream>
#include "bb_atsp.hpp"
#include "../utils/utils.hpp"

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
    this->bestCost = __INT_MAX__; // Start with max cost
}

BnBSolver::~BnBSolver() {
    delete[] bestPath;
    for (int i = 0; i < numCities; i++) {
        delete[] distanceMatrix[i];
    }
    delete[] distanceMatrix;
}

int BnBSolver::calculateLowerBound(int *partialPath, int depth, bool *visited) {
    int cost = 0;

    // Calculate the cost of the current path
    for (int i = 0; i < depth - 1; i++) {
        cost += distanceMatrix[partialPath[i]][partialPath[i + 1]];
    }

    // Add heuristic lower bound for genuinely unvisited cities
    for (int i = 0; i < numCities; i++) {
        if (visited[i]) continue; // Skip already visited cities
        int minCost = __INT_MAX__;
        for (int j = 0; j < numCities; j++) {
            if (!visited[j] && distanceMatrix[i][j] < minCost) {
                minCost = distanceMatrix[i][j];
            }
        }
        if (minCost != __INT_MAX__) {
            cost += minCost; // Only add if there's a valid minimum cost
        }
    }

    return cost;
}

void BnBSolver::branchAndBound(int *path, int depth, bool *visited) {
    // Base case: if depth equals the number of cities, close the loop
    if (depth == numCities) {
        int totalCost = 0;
        for (int i = 0; i < numCities - 1; i++) {
            totalCost += distanceMatrix[path[i]][path[i + 1]];
        }
        totalCost += distanceMatrix[path[numCities - 1]][path[0]]; // Closing the loop

        if (totalCost < bestCost) {
            bestCost = totalCost;
            for (int i = 0; i < numCities; i++) {
                bestPath[i] = path[i];
            }
        }
        return;
    }

    for (int i = depth; i < numCities; i++) {
        if (depth == 1 && i == 0) continue; // Skip city 0 in the first swap

        // Swap cities in the path to generate new paths
        swap(path[depth], path[i]);
        visited[path[depth]] = true; // Mark the city as visited

        int lowerBound = calculateLowerBound(path, depth + 1, visited);
        if (lowerBound < bestCost) { // Only explore if lowerBound is promising
            branchAndBound(path, depth + 1, visited);
        }

        // Backtrack: unmark the city and swap back
        visited[path[depth]] = false;
        swap(path[depth], path[i]); // Backtrack to previous state
    }
}

void BnBSolver::solve() {
    int *path = new int[numCities];
    for (int i = 0; i < numCities; i++) {
        path[i] = i; // Initialize path
    }

    bool *visited = new bool[numCities](); // Initialize visited array to false
    visited[0] = true; // Start from city 0
    branchAndBound(path, 1, visited); // Start branching from depth 1

    delete[] visited; // Clean up
    delete[] path;
}

void BnBSolver::printResults() {
    std::cout << "Minimum cost: " << bestCost << std::endl;
    std::cout << "Best path: ";
    for (int i = 0; i < numCities; i++) {
        std::cout << bestPath[i] << " ";
    }
    std::cout << std::endl;
}

int BnBSolver::getBestCost()
{
    return bestCost;
}

// Get the best path
int *BnBSolver::getBestPath()
{
    return bestPath;
}