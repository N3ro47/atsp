#include "ga_atsp.hpp"
#include <cstdlib>
#include <ctime>
#include <limits.h>
#include <iostream>

GASolver::GASolver(int **inputMatrix, int numCities) {
    this->distanceMatrix = inputMatrix;
    this->numCities = numCities;
    this->bestPath = new int[numCities];
    this->bestCost = INT_MAX;
    std::srand(std::time(0));
}

GASolver::~GASolver() {
    delete[] bestPath;
}

void GASolver::solve() {
    solveWithParameters(500, 10000, 0.02, 0.85);  // Default values
}

void GASolver::solveWithParameters(int populationSize, int numGenerations, double mutationRate, double crossoverRate) {
    int **population = new int*[populationSize];
    for (int i = 0; i < populationSize; ++i) {
        population[i] = new int[numCities];
    }

    int *fitness = new int[populationSize];
    initializePopulation(population, populationSize);

    for (int generation = 0; generation < numGenerations; ++generation) {
        evaluateFitness(population, populationSize, fitness);

        for (int i = 0; i < populationSize; ++i) {
            if (fitness[i] < bestCost) {
                bestCost = fitness[i];
                for (int j = 0; j < numCities; ++j) {
                    bestPath[j] = population[i][j];
                }
            }
        }

        int **newPopulation = new int*[populationSize];
        for (int i = 0; i < populationSize; ++i) {
            newPopulation[i] = new int[numCities];
        }

        for (int i = 0; i < populationSize; i += 2) {
            int *parent1 = new int[numCities];
            int *parent2 = new int[numCities];
            selectParents(population, populationSize, &parent1);
            selectParents(population, populationSize, &parent2);

            if (((double)std::rand() / RAND_MAX) < crossoverRate) {
                crossover(parent1, parent2, newPopulation[i]);
                crossover(parent2, parent1, newPopulation[i + 1]);
            } else {
                for (int j = 0; j < numCities; ++j) {
                    newPopulation[i][j] = parent1[j];
                    newPopulation[i + 1][j] = parent2[j];
                }
            }

            mutate(newPopulation[i], mutationRate);
            mutate(newPopulation[i + 1], mutationRate);

            delete[] parent1;
            delete[] parent2;
        }

        for (int i = 0; i < populationSize; ++i) {
            delete[] population[i];
        }
        delete[] population;
        population = newPopulation;
    }

    for (int i = 0; i < populationSize; ++i) {
        delete[] population[i];
    }
    delete[] population;
    delete[] fitness;
}

void GASolver::initializePopulation(int **population, int populationSize) {
    for (int i = 0; i < populationSize; ++i) {
        for (int j = 0; j < numCities; ++j) {
            population[i][j] = j;
        }
        for (int j = 0; j < numCities; ++j) {
            int swapIndex = std::rand() % numCities;
            int temp = population[i][j];
            population[i][j] = population[i][swapIndex];
            population[i][swapIndex] = temp;
        }
    }
}

void GASolver::evaluateFitness(int **population, int populationSize, int *fitness) {
    for (int i = 0; i < populationSize; ++i) {
        fitness[i] = calculateCost(population[i]);
    }
}

void GASolver::selectParents(int **population, int populationSize, int **parent) {
    int bestIndex = std::rand() % populationSize;
    int bestCost = calculateCost(population[bestIndex]);

    for (int i = 0; i < 5; ++i) {
        int index = std::rand() % populationSize;
        int cost = calculateCost(population[index]);
        if (cost < bestCost) {
            bestCost = cost;
            bestIndex = index;
        }
    }

    for (int j = 0; j < numCities; ++j) {
        (*parent)[j] = population[bestIndex][j];
    }
}

void GASolver::crossover(int *parent1, int *parent2, int *child) {
    bool *visited = new bool[numCities]();
    int crossoverPoint = std::rand() % numCities;

    for (int i = 0; i <= crossoverPoint; ++i) {
        child[i] = parent1[i];
        visited[parent1[i]] = true;
    }

    int index = crossoverPoint + 1;
    for (int i = 0; i < numCities; ++i) {
        if (!visited[parent2[i]]) {
            child[index++] = parent2[i];
        }
    }

    delete[] visited;
}

void GASolver::mutate(int *path, double mutationRate) {
    if (((double)std::rand() / RAND_MAX) < mutationRate) {
        int index1 = std::rand() % numCities;
        int index2 = std::rand() % numCities;
        int temp = path[index1];
        path[index1] = path[index2];
        path[index2] = temp;
    }
}

int GASolver::calculateCost(int *path) {
    int cost = 0;
    for (int i = 0; i < numCities - 1; ++i) {
        cost += distanceMatrix[path[i]][path[i + 1]];
    }
    cost += distanceMatrix[path[numCities - 1]][path[0]];
    return cost;
}

void GASolver::printResults() {
    for (int i = 0; i < numCities; ++i) {
        std::cout << bestPath[i] << " ";
    }
    std::cout << "\nCost: " << bestCost << std::endl;
}

int GASolver::getBestCost() {
    return bestCost;
}

int *GASolver::getBestPath() {
    return bestPath;
}
