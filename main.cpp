#include <string>

#include "matrixreader.hpp"
#include "bf_atsp.hpp"
#include "bb_atsp.hpp"
#include "sa_atsp.hpp"
#include "menu.hpp"
#include "utils/utils.hpp"
#include <chrono>
#include <iomanip>

int main (int argc, char *argv[]) {

  Menu menu;
  menu.displayMenu();

    /*
  MatrixReader fileMatrix;
  std::string filename = "data10.txt";

  fileMatrix.readMatrixFromFile(filename);

  //fileMatrix.printMatrix();
  BFSolver bf_solver(fileMatrix.getMatrix(),fileMatrix.getMatrixSize());
  bf_solver.solve();
  bf_solver.printResults();

  BnBSolver bb_solver(fileMatrix.getMatrix(),fileMatrix.getMatrixSize());
  bb_solver.solve();
  bb_solver.printResults();
  //SASolver sa_solver

 //testing correctness of bb against bf 

    int counter = 0;                     // Count the number of tests with different results
    int numTests = 10000;               // Number of tests to run for comparing BF and SA solvers
    int numCities = 10;                  // Size of each matrix to test with (can vary this)
    float totalDifference = 0.0;         // Accumulator for differences in cost
    Menu menu;

    for (int test = 0; test < numTests; ++test)
    {
        // Generate a random matrix for testing
        int **matrix = generateRandomMatrix(numCities);

        // Initialize and solve with Brute Force Solver (BFSolver)
        BFSolver *bfSolver = new BFSolver(matrix, numCities);
        bfSolver->solve();
        int bfCost = bfSolver->getBestCost();
        bfSolver->printResults();

        // Initialize and solve with Simulated Annealing Solver (SASolver)
        SASolver *saSolver = new SASolver(matrix, numCities);
        saSolver->solve();
        int saCost = saSolver->getBestCost();
        saSolver->printResults();

        // Compare results
        std::cout << "\nTest #" << test + 1 << " Results Comparison:\n";
        if (bfCost == saCost)
        {
            std::cout << "Both solvers returned the same cost: " << bfCost << "\n";
        }
        else
        {
            counter++;
            std::cout << "Different results:\n";
            std::cout << "BF Cost: " << bfCost << ", SA Cost: " << saCost << "\n";
        }

        // Accumulate the absolute difference
        totalDifference += abs(bfCost - saCost);

        // Clean up
        delete bfSolver;
        delete saSolver;
        deleteMatrix(matrix, numCities);
    }

    // Calculate average difference
    float avgDifference = totalDifference / counter;

    // Display final results
    float mismatchRate = (float)counter / numTests;
    std::cout << "\nFinal Results:\n";
    std::cout << "Number of mismatches: " << counter << "\n";
    std::cout << "Mismatch rate: " << mismatchRate * 100 << "%\n";
    std::cout << "Average difference in cost if wrong: " << avgDifference << "\n";
     */

    /*
    // Set floating-point precision for output
    std::cout << std::fixed << std::setprecision(9);

    // List of problem files
    std::vector<std::string> problemFiles = {"ftv47.atsp","ftv64.atsp","ftv70.atsp","kro124p.atsp","ftv170.atsp","rbg323.atsp","rbg443.atsp"}; // Add file names here
    int runs = 40;
    

    for (const auto& file : problemFiles) {  
        MatrixReader matrixReader;
        matrixReader.readMatrixFromFile(file);
        int **matrix = matrixReader.getMatrix();
        int size = matrixReader.getMatrixSize();

        if (matrix != nullptr && size > 0){
        std::vector<double> executionTimes;
        double totalTime = 0.0;

        int bestSolution = std::numeric_limits<int>::max();
        int worstSolution = std::numeric_limits<int>::min();
        double totalSolution = 0.0;

        std::cout << "Testing file: " << file << "\n";
        for (int i = 0; i < runs; ++i) {
            auto start = std::chrono::high_resolution_clock::now();

            // Solve the problem using SASolver
            SASolver solver(matrix, size);
            solver.solve();
            int solutionCost = solver.getBestCost();

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            double timeInMs = elapsed.count(); // Convert to 
            executionTimes.push_back(timeInMs);
            totalTime += timeInMs;

            // Track best, worst, and total solution costs
            if (solutionCost < bestSolution) {
                bestSolution = solutionCost;
            }
            if (solutionCost > worstSolution) {
                worstSolution = solutionCost;
            }
            totalSolution += solutionCost;

            std::cout << "Run " << i + 1 << ": Time = " << timeInMs << " s, Cost = " << solutionCost << "\n";
        }

        double avgTime = totalTime / runs;
        double avgSolution = totalSolution / runs;

        std::cout << "Results for file: " << file << "\n";
        std::cout << "Best Solution: " << bestSolution << "\n";
        std::cout << "Worst Solution: " << worstSolution << "\n";
        std::cout << "Average Solution: " << avgSolution << "\n";
        std::cout << "Average Time: " << avgTime << " s\n";
        std::cout << "-------------------------------------\n";

        // Clean up the matrix
        }
        else
        {
            std::cout << "Error reading matrix.\n";
        }
  
}
*/
  return 0;
}



    

