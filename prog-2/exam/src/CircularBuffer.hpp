#pragma once

#include "Exceptions.hpp"
#include "SequenceIterator.hpp"

template<typename T>
class CircularBuffer {
    T* array;
    int _capacity;
    int head = 0;
    int tail = 0;
    bool full = false;

    /**
     * Update internal states for inserting a new element.
     */
    void next() {
        if (full && ++tail == _capacity) {
            tail = 0;
        }

        if (++head == _capacity) {
            head = 0;
        }

        full = head == tail;
    }

    /**
     * Update internal states for removing an element.
     */
    void prev() {
        if (++tail == _capacity) {
            tail = 0;
        }

        full = false;
    }

public:

    using iterator = SequenceIterator<T>;

    /**
     * Constructor for a circular buffer of a fixed size. Allocated on the heap.
     * 
     * @param capacity - The capacity of the circular buffer. It is fixed. Must be greater than 0.
     */
    CircularBuffer(int capacity) {
        if (capacity < 1) {
            throw InitializeException("The Buffer's capacity must be greater than 0!");
        }

        _capacity = capacity;
        array = new T[capacity]{};
    }

    /**
     * Destructor. Deletes all elements.
     */
    ~CircularBuffer() {
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
        return iterator(array + _capacity);
    }

    /**
     * @return The capacity of the circular buffer. 
     * It is the maximum number of elements the buffer can hold.
     */
    int capacity() {
        return _capacity;
    }

    /**
     * @return Whether the the circular buffer is full.
     */
    bool isFull() {
        return full;
    }

    /**
     * @return Whether the the circular buffer is empty.
     */
    bool isEmpty() {
        return !full && head == tail;
    }

    /**
     * @return The number of elements in the circular buffer.
     */
    int size() {
        if (full) {
            return _capacity;
        } else if (head >= tail) {
            return head - tail;
        } else {
            return _capacity + head - tail;
        }
    }

    /**
     * Pushes a value to the circular buffer.
     * Overwrites the oldest value if the buffer is full.
     * The default use case for a circular buffer.
     * 
     * @param val - The value to insert in the circular buffer.
     */
    void pushOrOverwite(const T &val) {
        array[head] = val;
        next();
    }

    /**
     * Pushes a value to the circular buffer.
     * Rejects the insertion if the buffer is full.
     * 
     * @param val - The value to insert in the circular buffer.
     * @return Whether is value could be inserted.
     */
    bool pushOrReject(const T &val) {
        if (!full) {
            pushOrOverwite(val);
            return true;
        }

        return false;
    }

    /**
     * Pop the next value from the circuular buffer.
     * The value is stored in the receiver.
     * 
     * @param receiver - Receives the data if the circular buffer isn't empty. (MODIFIED)
     * @return Whether the circular buffer is not empty and the receiver is modified.
     */
    bool popInto(T &receiver) {
        if (!isEmpty()) {
            receiver = array[tail];
            prev();
            return true;
        }

        return false;
    }

    /**
     * Clear the circular buffer.
     */
    void clear() {
        head = 0;
        tail = 0;
        full = false;
    }

    /**
     * Copy the elements of a container into this circular buffer.
     * If the container is larger than this circular buffer, the remaining elements wont be inserted.
     * 
     * @param container - The container whose elements will be copied into this circular buffer.
     */
    template<typename Container>
    void fillWith(Container container) {
        for (T t : container) {
            if (!pushOrReject(t)) {
                break;
            }
        }
    }
};
