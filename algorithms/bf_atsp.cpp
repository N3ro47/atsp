#include "bf_atsp.hpp"
#include <iostream>
#include "../utils/utils.hpp"


bool nextPermutation(int *path, int size)
{
    int index = -1;
    int n = size - 2;

    // Step 1: Find the first decreasing element from the right
    for (int i = n; i >= 0; i--)
    {
        if (path[i] < path[i + 1])
        {
            index = i;
            break;
        }
    }

    // Step 2: If no such element exists, reverse the entire array
    if (index == -1)
    {
        // Reverse the array (path)
        int start = 0;
        int end = size - 1;
        while (start < end)
        {
            swap(path[start], path[end]);
            start++;
            end--;
        }
        return false; // Indicates we've generated all permutations
    }
    else
    {
        // Step 3: Find the smallest element larger than path[index] and swap
        for (int i = size - 1; i > index; i--)
        {
            if (path[i] > path[index])
            {
                swap(path[i], path[index]);
                break;
            }
        }

        // Step 4: Reverse the elements after the index
        int start = index + 1;
        int end = size - 1;
        while (start < end)
        {
            swap(path[start], path[end]);
            start++;
            end--;
        }
        return true; // Indicates a new permutation is generated
    }
}

BFSolver::BFSolver(int **inputMatrix, const int numCities)
{
    this->numCities = numCities;

    // Set the bestCost to the maximum possible integer value
    bestCost = __INT_MAX__;

    // Allocate memory for bestPath
    bestPath = new int[numCities];

    // Allocate memory for and copy the distance matrix
    this->distanceMatrix = new int *[numCities];
    for (int i = 0; i < numCities; i++)
    {
        this->distanceMatrix[i] = new int[numCities];
        for (int j = 0; j < numCities; j++)
        {
            this->distanceMatrix[i][j] = inputMatrix[i][j]; // Copy values from inputMatrix
        }
    }
}

void BFSolver::solve()
{
    bool hasNext;
    auto path = new int[numCities];

    // Set the starting city to 0 and initialize the remaining cities
    path[0] = 0;
    for (int i = 1; i < numCities; i++)
    {
        path[i] = i;
    }

    // Generate permutations for cities 1 to numCities - 1
    do
    {
        int pathLength = 0;

        // Calculate the length of the path from city 0 to the last city in the path and back to city 0
        for (int i = 0; i < numCities - 1; i++)
        {
            pathLength += distanceMatrix[path[i]][path[i + 1]];
        }
        pathLength += distanceMatrix[path[numCities - 1]][path[0]]; // Closing the cycle

        // If the path length is shorter, update the best path and best cost
        if (pathLength < bestCost)
        {
            bestCost = pathLength;
            for (int i = 0; i < numCities; i++)
            {
                bestPath[i] = path[i];
            }
        }

        // Get the next permutation for cities 1 to numCities - 1
        hasNext = nextPermutation(path + 1, numCities - 1);

    } while (hasNext);

    delete[] path;
}


void BFSolver::printResults()
{
    std::cout << "min cost: " << bestCost << std::endl;
    std::cout << "best path: ";
    for (int i = 0; i < numCities; i++)
    {
        std::cout << bestPath[i] << " ";
    }
    std::cout << std::endl;
}

BFSolver::~BFSolver()
{
    delete[] bestPath;
    for (int i = 0; i < numCities; ++i)
    {
        delete[] distanceMatrix[i];
    }
    delete[] distanceMatrix;
}