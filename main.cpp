#include <string>

#include "matrixreader.hpp"

int main (int argc, char *argv[]) {
  MatrixReader fileMatrix;
  std::string filename = "data10.txt";

  fileMatrix.readMatrixFromFile(filename);

  fileMatrix.printMatrix();

  return 0;
}
