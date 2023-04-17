#pragma once

#include <initializer_list>
#include "SequenceIterator.hpp"
#include "Exceptions.hpp"

template<typename T>
class Array {
    int _size;
    T* array;

public:

    using iterator = SequenceIterator<T>;

    /**
     * Constructor for an array of a fixed size. Allocated on the heap.
     * 
     * @param size - The size of the array. It is fixed. Must be greater than 0.
     */
    Array(int size) {
        if (size < 1) {
            throw InitializeException("The Array's size must be greater than 0!");
        }

        _size = size;
        array = new T[size]{};
    }

    /**
     * Constructor for an array of a fixed size. Allocated on the heap.
     * The size will be the number of arguments given.
     * Allows initialization with initializer list.
     * 
     * usage: Array<int> a = {1, 2, 3, 4, 5};
     * 
     * @param args - All objects to initialize the array with.
     */
    Array(std::initializer_list<T> args) {
        if (args.size() < 1) {
            throw InitializeException("The Array's size must be greater than 0!");
        }

        _size = args.size();
        array = new T[args.size()];

        fillWith(args);
    }

    /**
     * Destructor. Deletes all elements.
     */
    ~Array() {
        delete[] array;
    }

    /**
     * @return The iterator representing the beginning.
     */
    iterator begin() {
        return iterator(array);
    }

    /**
     * @return The iterator representing the end.
     */
    iterator end() {
        return iterator(array + _size);
    }

    /**
     * @return The size of the array.
     */
    int size() {
        return _size;
    }

    /**
     * Clear the array. Delete all elements and allocate 
     * new heap memory to be able to re-use the object.
     */
    void clear() {
        delete[] array;
        array = new T[size()]{};
    }

    /**
     * Copy the elements of a container into this array.
     * 
     * @param container - The container whose elements will be copied into this array.
     * 
     * @throws InitializeException - If the size of the container is greater than the arrays size.
     */
    template<typename Container>
    void fillWith(Container container) {
        if (container.size() > size()) {
            throw InitializeException("The container to fill the array is larger than the array!");
        }

        unsigned int index = 0;

        for (T t : container) {
            array[index++] = t;
        }
    }

    /**
     * @param index - The index of the requested element.
     * @return - A reference to the element at the index's position.
     * 
     * @throws IndexOutOfBoundsException - If the index is smaller than 0 or greater than the arrays size.
     */
    T& operator[](const int &index) {
        if (index < 0 || index >= size()) {
            throw IndexOutOfBoundsException(index, size() - 1);
        }

        return array[index];
    }
};
