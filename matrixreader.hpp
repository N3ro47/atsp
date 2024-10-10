#ifndef MATRIX_READER_HPP
#define MATRIX_READER_HPP

#include <vector>
#include <string>

class MatrixReader {
private:
    int** matrix;  // 2D array using pointers
    int size;  // Size of the matrix
    
public:
    MatrixReader();
    // Method to read the matrix from a file
    void readMatrixFromFile(const std::string& filename);

    // Method to print the matrix
    void printMatrix() const;

    // Getter to retrieve the matrix
    int** getMatrix() const;

    int getMatrixSize() const;

     ~MatrixReader();  // Destructor
};

#endif // MATRIX_READER_HPP