#include <string>

#include "matrixreader.hpp"
#include "bf_atsp.hpp"

int main (int argc, char *argv[]) {
  MatrixReader fileMatrix;
  std::string filename = "data3.txt";

  fileMatrix.readMatrixFromFile(filename);

  fileMatrix.printMatrix();

  BFSolver bf_solver(fileMatrix.getMatrix(),fileMatrix.getMatrixSize());
  bf_solver.solve();
  bf_solver.printResults();


  

  return 0;
}
