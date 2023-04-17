#pragma once

namespace Algorithm {

    /**
     * Swap value of any two non-const variables with the same type.
     * 
     * @param a - Value gets swapped with b's value.
     * @param b - Value gets swapped with a's value.
     */
    template<typename C>
    inline void swap(C &a, C &b) {
        auto temp = a;
        a = b;
        b = temp;
    }

    /**
     * Swap contents of any two iterators with the same type.
     * 
     * @param a - Content gets swapped with b's content.
     * @param b - Content gets swapped with a's content.
     */
    template<typename Iterator>
    inline void swapIterator(Iterator a, Iterator b) {
        swap(*a, *b);
    }

    /**
     * Sort a sqeuence defined by the begin and end iterator with the 
     * quick sort algorithm. The iterators must be RandomAccessIterators.
     * 
     * @param begin - The begin of the sequence.
     * @param end - The end of the sequence.
     * @param comparator - The comparator that determines the order. 
     * It is a function or a functor that takes two objects of the iterators value_type and returns a bool.
     */
    template<typename Iterator, typename Comparator>
    void quickSort(Iterator begin, Iterator end, Comparator comparator) {
        if (end <= begin) return;

        Iterator pivot = begin;
        Iterator middle = begin + 1;

        for (Iterator i = begin + 1; i < end; ++i) {
            if (comparator(*i, *pivot)) {
                swapIterator(i, middle);
                ++middle;
            }
        }

        swapIterator(begin, middle - 1);

        quickSort(begin, middle - 1, comparator);
        quickSort(middle, end, comparator);
    }

}
