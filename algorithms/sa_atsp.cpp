#include <iostream>
#include "sa_atsp.hpp"
#include "../utils/utils.hpp"

// Constructor
SASolver::SASolver(int **inputMatrix, int numCities)
{
    this->numCities = numCities;
    this->distanceMatrix = new int *[numCities];
    for (int i = 0; i < numCities; i++)
    {
        this->distanceMatrix[i] = new int[numCities];
        for (int j = 0; j < numCities; j++)
        {
            this->distanceMatrix[i][j] = inputMatrix[i][j];
        }
    }

    this->bestPath = new int[numCities];
    this->bestCost = __INT_MAX__; // Start with max cost
}

// Destructor
SASolver::~SASolver()
{
    delete[] bestPath;
    for (int i = 0; i < numCities; i++)
    {
        delete[] distanceMatrix[i];
    }
    delete[] distanceMatrix;
}

void generateIntialPath(int **inputMatrix, int numCities, int *path)
{
    bool *visited = new bool[numCities];
    for (int i = 0; i < numCities; i++) {
    visited[i] = false;
    }

    path[0] = 0;
    visited[0] = true;

    for (int i = 1; i < numCities; i++)
    {
        int lastCity = path[i - 1];
        int nextCity = -1;
        int minDist = __INT_MAX__;
        for (int j = 0; j < numCities; ++j)
        {
            if (!visited[j] && inputMatrix[lastCity][j] < minDist)
            {
                nextCity = j;
                minDist = inputMatrix[lastCity][j];
            }
        }
        path[i] = nextCity;
        visited[nextCity] = true;
    }
    delete[] visited;
}

int calculateCost(int *path, int numCities, int **distanceMatrix)
{
    int pathLength = 0;
    for (int i = 0; i < numCities - 1; i++)
    {
        pathLength += distanceMatrix[path[i]][path[i + 1]];
    }
    pathLength += distanceMatrix[path[numCities - 1]][0];
    return pathLength;
}


void generateNeighbor(int *path, int numCities) {
    int i = rand() % (numCities - 1) + 1;
    int j = rand() % (numCities - 1) + 1; 
    while (i == j) {
        j = rand() % (numCities - 1) + 1;
    }
    swap(path[i], path[j]);
}

void SASolver::solve() {
    solveWithParameters(1000.0, 0.99, 1e-3, 0);
}

// Solve the ATSP using Simulated Annealing
void SASolver::solveWithParameters(
    double initialTemperature,
    double coolingRate,
    double minTemperature,
    int iterationsPerTemp
) {
    // Use default for iterationsPerTemp if not explicitly provided
    if (iterationsPerTemp == 0) {
       
        iterationsPerTemp = numCities * numCities;  // Default O(n^2)
    }

    // Start with a greedy initial solution
    generateIntialPath(distanceMatrix, numCities, bestPath);
    bestCost = calculateCost(bestPath, numCities, distanceMatrix);

    // Copy bestPath to currentPath for annealing
    int *currentPath = new int[numCities];
    for (int i = 0; i < numCities; i++) {
        currentPath[i] = bestPath[i];
    }
    int currentCost = bestCost;

    // Simulated Annealing process
    srand(time(0)); 
    double temperature = initialTemperature;  // Initialize with the given or default value
    while (temperature > minTemperature) {
        for (int iter = 0; iter < iterationsPerTemp; ++iter) {
            // Generate a neighboring solution
            int *neighborPath = new int[numCities];
            for (int i = 0; i < numCities; i++) {
                neighborPath[i] = currentPath[i];
            }
            generateNeighbor(neighborPath, numCities);

            int neighborCost = calculateCost(neighborPath, numCities, distanceMatrix);

            // Calculate cost difference
            int delta = neighborCost - currentCost;

            // Accept the new solution with a probability based on delta and temperature
            if (delta < 0 || exp(-delta / temperature) > (double)rand() / RAND_MAX) {
                for (int i = 0; i < numCities; i++) {
                    currentPath[i] = neighborPath[i];
                }
                currentCost = neighborCost;

                // Update the best solution if improved
                if (currentCost < bestCost) {
                    for (int i = 0; i < numCities; i++) {
                        bestPath[i] = currentPath[i];
                    }
                    bestCost = currentCost;
                }
            }

            delete[] neighborPath; 
        }

        // Cool down
        temperature *= coolingRate;
    }

    delete[] currentPath; 
}


// Print the results
void SASolver::printResults()
{
    std::cout << "Minimum cost: " << bestCost << std::endl;
    std::cout << "Best path: ";
    for (int i = 0; i < numCities; i++)
    {
        std::cout << bestPath[i] << " ";
    }
    std::cout << std::endl;
}

// Get the best cost
int SASolver::getBestCost()
{
    return bestCost;
}

// Get the best path
int *SASolver::getBestPath()
{
    return bestPath;
}
