#ifndef MY_VECTOR_HPP
#define MY_VECTOR_HPP

#include <stdexcept>  // For exceptions
#include <iostream>   // For debugging (optional)

namespace my {

template <typename T>
class vector {
private:
    T* data;         // Pointer to the dynamically allocated array
    std::size_t size;    // Current size of the vector
    std::size_t capacity; // Total capacity of the allocated array

    // Private helper to reallocate memory when capacity is exceeded
    void resizeIfNeeded();

public:
    // Constructors and destructor
    vector();                         // Default constructor
    vector(std::size_t initialSize);   // Constructor with initial size
    ~vector();                        // Destructor to free memory

    // Accessors
    std::size_t getSize() const;
    std::size_t getCapacity() const;
    bool isEmpty() const;
    T& operator[](std::size_t index);         // Subscript operator for element access
    const T& operator[](std::size_t index) const;  // For constant access

    // Modifiers
    void push_back(const T& value);     // Add an element to the end
    void pop_back();                    // Remove the last element
    void clear();                       // Clear all elements
};

}

#endif // MY_VECTOR_HPP
