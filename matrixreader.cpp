#include "matrixreader.hpp"
#include <fstream>
#include <iostream>

MatrixReader::MatrixReader() {
    size = 0;
    matrix = nullptr;
}

void MatrixReader::readMatrixFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        // Handle error
        return;
    }

    // Read the size of the matrix
    file >> size;

    // Allocate memory for the matrix
    matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
    }

    // Read the matrix from the file
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            file >> matrix[i][j];
        }
    }

    file.close();
}

void MatrixReader::printMatrix() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int** MatrixReader::getMatrix() const {
    return matrix;
}

int MatrixReader::getMatrixSize() const {
    return size;
}

MatrixReader::~MatrixReader() {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}