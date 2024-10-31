#include <string>

#include "matrixreader.hpp"
#include "bf_atsp.hpp"
#include "bb_atsp.hpp"
#include "menu.hpp"

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
  */

  

  return 0;
}
