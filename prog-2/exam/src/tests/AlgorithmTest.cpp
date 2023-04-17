#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Person.h"
#include "Algorithm.hpp"
#include "SequenceIterator.hpp"

using namespace std;

void testSwap() {
    int a1 = 3, a2 = 6;
    double b1 = 1.33, b2 = 3.55;

    Algorithm::swap(a1, a2);
    Algorithm::swap(b1, b2);

    if (a1 != 6 || a2 != 3 || b1 != 3.55 || b2 != 1.33) {
        cout << "%TEST_FAILED% time=0 testname=testSwap (AlgorithmTest) message=" << endl;
    }
}

void testSwapIterator() {
    int a1 = 3, a2 = 6;
    double b1 = 1.33, b2 = 3.55;
    int temp1 = 19, temp2 = 11;
    SequenceIterator<int> c1 = SequenceIterator<int>(&temp1);
    SequenceIterator<int> c2 = SequenceIterator<int>(&temp2);

    Algorithm::swapIterator(&a1, &a2);
    Algorithm::swapIterator(&b1, &b2);
    Algorithm::swapIterator(c1, c2);

    if (a1 != 6 || a2 != 3 || b1 != 3.55 || b2 != 1.33 || *c1 != 11 || *c2 != 19) {
        cout << "%TEST_FAILED% time=0 testname=testSwapIterator (AlgorithmTest) message=" << endl;
    }
}

void testQuickSort() {
    vector<int> v1{3, 2, 1};
    vector<double> v2{3.0, 2.0, 1.0};
    vector<Person> v3{Person("", "", 50, 3000.0), Person("", "", 80, 899.99), Person("", "", 61, 2456.76)};
    int array[] = {3, 2, 1};

    Algorithm::quickSort(v1.begin(), v1.end(), [](int const &a, int const &b) {
        return a < b;
    });

    Algorithm::quickSort(v2.begin(), v2.end(), [](double const &a, double const &b) {
        return a < b;
    });

    Algorithm::quickSort(v3.begin(), v3.end(), [](Person const &a, Person const &b) {
        return a.age < b.age;
    });

    Algorithm::quickSort(array, array + 3, [](int const &a, int const &b) {
        return a < b;
    });

    for (int i = 1; i < v1.size(); ++i) {
        if (v1[i - 1] > v1[i]) {
            cout << "%TEST_FAILED% time=0 testname=testQuickSort (AlgorithmTest) message=vector<int> wrong" << endl;
        }
    }

    for (int i = 1; i < v2.size(); ++i) {
        if (v2[i - 1] > v2[i]) {
            cout << "%TEST_FAILED% time=0 testname=testQuickSort (AlgorithmTest) message=vector<double> wrong" << endl;
        }
    }

    for (int i = 1; i < v3.size(); ++i) {
        if (v3[i - 1].age > v3[i].age) {
            cout << "%TEST_FAILED% time=0 testname=testQuickSort (AlgorithmTest) message=vector<Person> wrong" << endl;
        }
    }

    for (int i = 1; i < 3; ++i) {
        if (array[i - 1] > array[i]) {
            cout << "%TEST_FAILED% time=0 testname=testQuickSort (AlgorithmTest) message=array wrong" << endl;
        }
    }
}

int main(int argc, char** argv) {
    cout << "%SUITE_STARTING% AlgorithmTest" << endl;
    cout << "%SUITE_STARTED%" << endl;

    cout << "%TEST_STARTED% testSwap (AlgorithmTest)" << endl;
    testSwap();
    cout << "%TEST_FINISHED% time=0 testSwap (AlgorithmTest)" << endl;

    cout << "%TEST_STARTED% testSwapIterator (AlgorithmTest)" << endl;
    testSwapIterator();
    cout << "%TEST_FINISHED% time=0 testSwapIterator (AlgorithmTest)" << endl;

    cout << "%TEST_STARTED% testQuickSort (AlgorithmTest)" << endl;
    testQuickSort();
    cout << "%TEST_FINISHED% time=0 testQuickSort (AlgorithmTest)" << endl;

    cout << "%SUITE_FINISHED% time=0" << endl;

    return (EXIT_SUCCESS);
}
