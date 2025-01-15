#include "menu.hpp"
#include "utils.hpp"
#include "algorithms/bb_atsp.hpp"
#include "algorithms/bf_atsp.hpp"
#include "algorithms/sa_atsp.hpp"
#include "algorithms/ga_atsp.hpp"

#include <chrono>
#include <iomanip>

void Menu::displayMenu() {
    int choice;
    do {
        std::cout << "===== ATSP Solver Menu =====\n";
        std::cout << "1. Load Matrix\n";
        std::cout << "2. Solve ATSP\n";
        std::cout << "3. Show Matrix\n";
        std::cout << "4. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            loadMatrix();
            break;
        case 2:
            if (matrixReader.getMatrix() != nullptr) {
                solveATSP(matrixReader.getMatrix(), matrixReader.getMatrixSize());
            } else {
                std::cout << "No matrix loaded. Please load a matrix first.\n";
            }
            break;
        case 3:
            if (matrixReader.getMatrix() != nullptr) {
                printMatrix(matrixReader.getMatrix(), matrixReader.getMatrixSize());
            } else {
                std::cout << "No matrix loaded. Please load a matrix first.\n";
            }
            break;
        case 4:
            std::cout << "Exiting.\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
        }
    } while (choice != 4);
}

void Menu::loadMatrix() {
    std::string filename;
    std::cout << "Enter the matrix filename: ";
    std::cin >> filename;

    matrixReader.readMatrixFromFile(filename);
    int **matrix = matrixReader.getMatrix();
    int size = matrixReader.getMatrixSize();

    if (matrix != nullptr && size > 0) {
        std::cout << "Matrix loaded successfully.\n";
    } else {
        std::cout << "Error reading matrix.\n";
    }
}

void Menu::solveATSP(int **matrix, int size) {
    // Static variables to retain previous SA parameters
    static double initialTemp = 1000.0;
    static double coolingRate = 0.99;
    static double minTemp = 1e-3;
    static int iterationsPerTemp = 0;

    // Static variables for GA parameters
    static int populationSize = 500;
    static int numGenerations = 3000;
    static double mutationRate = 0.01;
    static double crossoverRate = 0.85;

    while (true) {
        int choice;
        std::cout << "\nSelect solving method:\n";
        std::cout << "1. Brute Force\n";
        std::cout << "2. Branch & Bound\n";
        std::cout << "3. Simulated Annealing\n";
        std::cout << "4. Genetic Algorithm\n";  // New option for GA
        std::cout << "5. Go Back\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        if (choice == 5) return; // Exit to the previous menu

        int *path = new int[size];
        switch (choice) {
        case 1:
            solver = new BFSolver(matrix, size);
            break;
        case 2:
            solver = new BnBSolver(matrix, size);
            break;
        case 3: {
            solver = new SASolver(matrix, size);

            // Prompt user to choose parameter type for SA
            int saChoice;
            std::cout << "Simulated Annealing Parameters:\n";
            std::cout << "1. Use previous parameters\n";
            std::cout << "2. Use default parameters\n";
            std::cout << "3. Enter new parameters\n";
            std::cout << "Choose an option: ";
            std::cin >> saChoice;

            if (saChoice == 3) { // Enter new parameters
                std::cout << "Enter initial temperature (default: " << initialTemp << "): ";
                std::cin >> initialTemp;
                std::cout << "Enter cooling rate (default: " << coolingRate << "): ";
                std::cin >> coolingRate;
                std::cout << "Enter minimum temperature (default: " << minTemp << "): ";
                std::cin >> minTemp;
                std::cout << "Enter iterations per temperature (default: "
                          << (iterationsPerTemp == 0 ? "numCities^2" : std::to_string(iterationsPerTemp)) << "): ";
                std::cin >> iterationsPerTemp;
            } else if (saChoice == 2) { // Use default parameters
                initialTemp = 1000.0;
                coolingRate = 0.99;
                minTemp = 1e-3;
                iterationsPerTemp = 0; // Default: numCities^2
            }

            // Call the parameterized solve function
            dynamic_cast<SASolver *>(solver)->solveWithParameters(initialTemp, coolingRate, minTemp, iterationsPerTemp);
            break;
        }
        case 4: {
            solver = new GASolver(matrix, size);

            // Prompt user to choose parameter type for GA
            int gaChoice;
            std::cout << "Genetic Algorithm Parameters:\n";
            std::cout << "1. Use previous parameters\n";
            std::cout << "2. Use default parameters\n";
            std::cout << "3. Enter new parameters\n";
            std::cout << "Choose an option: ";
            std::cin >> gaChoice;

            if (gaChoice == 3) { // Enter new parameters
                std::cout << "Enter population size (default: " << populationSize << "): ";
                std::cin >> populationSize;
                std::cout << "Enter number of generations (default: " << numGenerations << "): ";
                std::cin >> numGenerations;
                std::cout << "Enter mutation rate (default: " << mutationRate << "): ";
                std::cin >> mutationRate;
                std::cout << "Enter crossover rate (default: " << crossoverRate << "): ";
                std::cin >> crossoverRate;
            } else if (gaChoice == 2) { // Use default parameters
                populationSize = 100;
                numGenerations = 1000;
                mutationRate = 0.01;
                crossoverRate = 0.8;
            }

            // Call the parameterized solve function
            dynamic_cast<GASolver *>(solver)->solveWithParameters(populationSize, numGenerations, mutationRate, crossoverRate);
            break;
        }
        default:
            std::cout << "Invalid choice.\n";
            delete[] path;
            continue;
        }

        // Measure execution time
        std::cout << std::fixed << std::setprecision(9);
        auto start = std::chrono::high_resolution_clock::now();
        solver->solve(); // Runs the selected algorithm
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        std::cout << "N = " << size << ", Time = " << duration.count() << " s\n";

        solver->printResults();
        delete solver;
    }
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
