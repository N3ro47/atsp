#include "vector.hpp"
#include <iostream>

namespace my {

// Default constructor: Initialize with a size of 0 and capacity of 1
template <typename T>
vector<T>::vector() : size(0), capacity(1) {
    data = new T[capacity];
}

// Constructor with initial size
template <typename T>
vector<T>::vector(std::size_t initialSize) : size(initialSize), capacity(initialSize * 2) {
    data = new T[capacity];
    for (std::size_t i = 0; i < size; ++i) {
        data[i] = T();  // Default-construct the elements
    }
}

// Destructor: Free the dynamically allocated memory
template <typename T>
vector<T>::~vector() {
    delete[] data;
}

// Get the current size of the vector
template <typename T>
std::size_t vector<T>::getSize() const {
    return size;
}

// Get the current capacity of the vector
template <typename T>
std::size_t vector<T>::getCapacity() const {
    return capacity;
}

// Check if the vector is empty
template <typename T>
bool vector<T>::isEmpty() const {
    return size == 0;
}

// Subscript operator for element access
template <typename T>
T& vector<T>::operator[](std::size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// Subscript operator for constant element access
template <typename T>
const T& vector<T>::operator[](std::size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// Add an element to the end of the vector
template <typename T>
void vector<T>::push_back(const T& value) {
    resizeIfNeeded();  // Resize if the capacity is exceeded
    data[size++] = value;
}

// Remove the last element
template <typename T>
void vector<T>::pop_back() {
    if (size > 0) {
        --size;
    } else {
        throw std::underflow_error("Vector is already empty");
    }
}

// Clear all elements in the vector
template <typename T>
void vector<T>::clear() {
    size = 0;
}

// Private helper to reallocate memory when capacity is exceeded
template <typename T>
void vector<T>::resizeIfNeeded() {
    if (size >= capacity) {
        capacity *= 2;
        T* newData = new T[capacity];

        // Copy old data to new array
        for (std::size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }

        delete[] data;  // Free the old array
        data = newData; // Point to the new array
    }
}

}