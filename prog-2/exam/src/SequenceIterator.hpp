#pragma once

#include <iterator>

template<typename T>
class SequenceIterator : public std::iterator<std::random_access_iterator_tag, T> {
    T *_t;
public:

    /**
     * Constructor
     * 
     * @param t - The pointer to the element this iterator is pointing to.
     */
    SequenceIterator(T *t) {
        _t = t;
    }

    /////////////////////////////////////////////////////////////////////////////
    //   overload necessary operators to have a valid random access iterator   //
    /////////////////////////////////////////////////////////////////////////////

    SequenceIterator<T>& operator++() {
        ++_t;
        return *this;
    }

    SequenceIterator<T> operator++(int) {
        SequenceIterator<T> temp = SequenceIterator<T>(_t);
        operator++();
        return temp;
    }

    SequenceIterator<T> operator+(const int &n) {
        return SequenceIterator<T>(_t + n);
    }

    SequenceIterator<T> operator+(const SequenceIterator<T> &other) {
        return SequenceIterator<T>(_t + other._t);
    }

    SequenceIterator<T>& operator--() {
        --_t;
        return *this;
    }

    SequenceIterator<T> operator--(int) {
        SequenceIterator<T> temp = SequenceIterator<T>(_t);
        operator--();
        return temp;
    }

    SequenceIterator<T> operator-(const int &n) {
        return SequenceIterator<T>(_t - n);
    }

    SequenceIterator<T> operator-(const SequenceIterator<T> &other) {
        return SequenceIterator<T>(_t - other._t);
    }

    SequenceIterator<T>& operator=(const SequenceIterator<T> &other) {
        _t = other._t;
        return *this;
    }

    SequenceIterator<T>& operator+=(const SequenceIterator<T> &other) {
        _t += other._t;
        return *this;
    }

    SequenceIterator<T>& operator-=(const SequenceIterator<T> &other) {
        _t -= other._t;
        return *this;
    }

    bool operator==(const SequenceIterator<T> &other) {
        return _t == other._t;
    }

    bool operator!=(const SequenceIterator<T> &other) {
        return _t != other._t;
    }

    bool operator<(const SequenceIterator<T> &other) {
        return _t < other._t;
    }

    bool operator<=(const SequenceIterator<T> &other) {
        return _t <= other._t;
    }

    bool operator>(const SequenceIterator<T> &other) {
        return _t > other._t;
    }

    bool operator>=(const SequenceIterator<T> &other) {
        return _t >= other._t;
    }

    T& operator*() {
        return *_t;
    }

    T& operator[](const int &n) {
        return *(_t + n);
    }
};
