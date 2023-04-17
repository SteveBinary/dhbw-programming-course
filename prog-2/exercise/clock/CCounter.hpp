#pragma once
#include <iostream>

template <class T>
class CCounter {
private:
    T count;
    T max;


public:

    CCounter(T maximum, T initialCount = 0) : count(initialCount), max(maximum) {
    }

    bool Increment() {
        if (count < max) {
            ++count;
            return false;
        } else {
            Reset();
            return true;
        }
    }

    void Reset() {
        count = 0;
    }

    T GetCount() const {
        return count;
    }

    void SetCount(T newCount) {
        count = newCount;
    }

    bool operator<(unsigned int const other) const {
        return count < other;
    }

    bool operator<(CCounter const &other) const {
        return count < other.count;
    }
};
