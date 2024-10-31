#ifndef UTILS_HPP
#define UTILS_HPP

#include <random>

inline void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}


inline int** generateRandomMatrix(int size) {
    int** matrix = new int*[size];
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100); // Adjust range as needed

    for (int i = 0; i < size; ++i) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = (i == j) ? 0 : dist(gen); // Diagonal is 0
        }
    }
    return matrix;
}

inline void deleteMatrix(int** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

#endif // UTILS_HPP