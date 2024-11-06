#include "menu.hpp"
#include "utils.hpp"
#include "algorithms/bb_atsp.hpp"
#include "algorithms/bf_atsp.hpp"
#include "algorithms/sa_atsp.hpp"

#include <chrono>
#include <iomanip>

void Menu::displayMenu()
{
    int choice;
    do
    {
        std::cout << "===== ATSP Solver Menu =====\n";
        std::cout << "1. Manual Mode\n";
        std::cout << "2. Automatic Mode\n";
        std::cout << "3. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            manualMode();
            break;
        case 2:
            automaticMode();
            break;
        case 3:
            std::cout << "Exiting.\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
        }
    } while (choice != 3);
}

void Menu::manualMode()
{
    std::string filename;
    std::cout << "Enter the matrix filename: ";
    std::cin >> filename;

    matrixReader.readMatrixFromFile(filename);
    int **matrix = matrixReader.getMatrix();
    int size = matrixReader.getMatrixSize();

    if (matrix != nullptr && size > 0)
    {
        solveATSP(matrix, size);
    }
    else
    {
        std::cout << "Error reading matrix.\n";
    }
}

void Menu::solveATSP(int **matrix, int size)
{
    loopprint:
    int choice;
    std::cout << "Select solving method:\n";
    std::cout << "1. Brute Force\n";
    std::cout << "2. Branch & Bound\n";
    std::cout << "3. Simulated annealing\n";
    std::cout << "4. Show matrix\n";
    std::cout << "Choose an option: ";
    std::cin >> choice;

    int cost;
    int *path = new int[size];

    switch (choice)
    {
    case 1:
        solver = new BFSolver(matrix, size);
        break;
    case 2:
        solver = new BnBSolver(matrix, size);
        break;
    case 3:
        solver = new SASolver(matrix, size);
        break;
    case 4:
        printMatrix(matrix, size);
        delete[] path; // delete the original path array
        goto loopprint;
    default:
        std::cout << "Invalid choice.\n";
        delete[] path; // delete the original path array
        return;
    }

    solver->solve();
    solver->printResults();
    cost = solver->getBestCost();
    int *bestPath = solver->getBestPath(); // get the best path from the solver
    // use the bestPath variable instead of reassigning path

    delete solver;
}

void Menu::automaticMode()
{
    int minSize, maxSize, step, instances, choice;

    // Ask the user to select the solving method
    std::cout << "Select solving method:\n";
    std::cout << "1. Brute Force\n";
    std::cout << "2. Branch & Bound\n";
    std::cout << "3. Simulated annealing\n";
    std::cout << "Choose an option: ";
    std::cin >> choice;

    // Gather user inputs for N range and number of instances
    std::cout << "Enter minimum N (number of cities): ";
    std::cin >> minSize;
    std::cout << "Enter maximum N (number of cities): ";
    std::cin >> maxSize;
    std::cout << "Enter step size for N: ";
    std::cin >> step;
    std::cout << "Enter number of instances per N: ";
    std::cin >> instances;

    std::cout << std::fixed << std::setprecision(9);

    // Loop through each size N and generate instances
    for (int size = minSize; size <= maxSize; size += step)
    {
        double totalTime = 0.0;

        for (int i = 0; i < instances; ++i)
        {
            int **matrix = generateRandomMatrix(size);

            // Instantiate the solver based on the selected option
            switch (choice)
            {
            case 1:
                solver = new BFSolver(matrix, size);
                break;
            case 2:
                solver = new BnBSolver(matrix, size);
                break;
            case 3:
                solver = new SASolver(matrix, size);
                break;
            default:
                std::cout << "Invalid choice.\n";
                deleteMatrix(matrix, size);
                return;
            }

            // Measure
            auto start = std::chrono::high_resolution_clock::now();
            solver->solve();
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> duration = end - start;
            totalTime += duration.count();

            // Clean up
            delete solver;
            deleteMatrix(matrix, size);
        }

        // Average time for current size
        double averageTime = totalTime / instances;
        std::cout << "N = " << size << ", Average Time = " << averageTime << " s\n";
    }
}
