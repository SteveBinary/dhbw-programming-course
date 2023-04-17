#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Array.hpp"
#include "Person.h"

using namespace std;

void testConstructor() {
    try {
        Array<int> a(0);
        cout << "%TEST_FAILED% time=0 testname=testConstructor (ArrayTest) message=Array-initialization should fail!" << endl;
    } catch (InitializeException const &e) {
        // everything is OK, the exception should be thrown
    }

    try {
        Array<int> a(-1);
        cout << "%TEST_FAILED% time=0 testname=testConstructor (ArrayTest) message=Array-initialization should fail!" << endl;
    } catch (InitializeException const &e) {
        // everything is OK, the exception should be thrown
    }

    try {
        Array<int> a = {};
        cout << "%TEST_FAILED% time=0 testname=testConstructor (ArrayTest) message=Array-initialization should fail!" << endl;
    } catch (InitializeException const &e) {
        // everything is OK, the exception should be thrown
    }

    try {
        Array<int> a(10);
    } catch (InitializeException const &e) {
        cout << "%TEST_FAILED% time=0 testname=testConstructor (ArrayTest) message=Array-initialization should not fail!" << endl;
    }

    // initializer list
    Array<int> array = {1, 2, 3, 4, 5};
    if (array.size() != 5 || array[0] != 1 || array[1] != 2 || array[2] != 3 || array[3] != 4 || array[4] != 5) {
        cout << "%TEST_FAILED% time=0 testname=testConstructor (ArrayTest) message=Array-initialization with initializer list failed!" << endl;
    }
}

void testIterators() {
    Array<int> a(5);
    Array<int> b = {1, 2, 3, 4, 5};

    for (int const & i : a) {
        if (i != 0) {
            cout << "%TEST_FAILED% time=0 testname=testIterators (ArrayTest) message=loop 1" << endl;
        }
    }
    for (int & i : a) {
        if (i != 0) {
            cout << "%TEST_FAILED% time=0 testname=testIterators (ArrayTest) message=loop 2" << endl;
        }
    }
    for (int const i : a) {
        if (i != 0) {
            cout << "%TEST_FAILED% time=0 testname=testIterators (ArrayTest) message=loop 3" << endl;
        }
    }
    for (int i : a) {
        if (i != 0) {
            cout << "%TEST_FAILED% time=0 testname=testIterators (ArrayTest) message=loop 4" << endl;
        }
    }

    ////////////

    for (auto i = b.begin() + 1; i < b.end(); ++i) {
        if (*(i - 1) >= *i) {
            cout << "%TEST_FAILED% time=0 testname=testIterators (ArrayTest) message=loop 5" << endl;
        }
    }
}

void testSize() {
    Array<int> a1(1);
    Array<double> a2(10);
    Array<Person> a3(100);

    if (a1.size() != 1 || a2.size() != 10 || a3.size() != 100) {
        cout << "%TEST_FAILED% time=0 testname=testSize (ArrayTest) message=" << endl;
    }
}

void testClear() {
    Array<int> a1 = {1};
    Array<double> a2(10);
    Array<Person> a3(100);

    // int array
    if (a1[0] != 1) {
        cout << "%TEST_FAILED% time=0 testname=testClear (ArrayTest) message=int array 1" << endl;
    }
    a1[0] = 9;
    if (a1[0] != 9) {
        cout << "%TEST_FAILED% time=0 testname=testClear (ArrayTest) message=int array 2" << endl;
    }
    int i1 = a1[0];
    if (i1 != 9) {
        cout << "%TEST_FAILED% time=0 testname=testClear (ArrayTest) message=int array 3" << endl;
    }
    a1.clear();
    if (a1[0] != 0) {
        cout << "%TEST_FAILED% time=0 testname=testClear (ArrayTest) message=int array 4" << endl;
    }

    // double array
    if (a2[0] != 0.0 || a2[9] != 0.0) {
        cout << "%TEST_FAILED% time=0 testname=testClear (ArrayTest) message=double array 1" << endl;
    }
    a2[1] = 8.0;
    a2[7] = -16.0;
    if (a2[1] != 8.0 || a2[7] != -16.0) {
        cout << "%TEST_FAILED% time=0 testname=testClear (ArrayTest) message=double array 2" << endl;
    }
    a2.clear();
    if (a2[1] != 0.0 || a2[7] != 0.0) {
        cout << "%TEST_FAILED% time=0 testname=testClear (ArrayTest) message=double array 3" << endl;
    }
    a2[0] = 128.128;
    a2[9] = 64.64;
    if (a2[0] != 128.128 || a2[9] != 64.64) {
        cout << "%TEST_FAILED% time=0 testname=testClear (ArrayTest) message=double array 4" << endl;
    }
    a2.clear();
    if (a2[0] != 0.0 || a2[9] != 0.0) {
        cout << "%TEST_FAILED% time=0 testname=testClear (ArrayTest) message=double array 5" << endl;
    }

    // person array
    Person emptyPerson;
    if (a3[0] != emptyPerson || a3[99] != emptyPerson) {
        cout << "%TEST_FAILED% time=0 testname=testClear (ArrayTest) message=person array 1" << endl;
    }
    Person p1("a", "b", 1, 2.0);
    Person p2("b", "c", 2, 3.0);
    a3[1] = p1;
    a3[80] = p2;
    if (a3[1] != p1 || a3[80] != p2) {
        cout << "%TEST_FAILED% time=0 testname=testClear (ArrayTest) message=person array 2" << endl;
    }
    a3.clear();
    if (a3[1] != emptyPerson || a3[80] != emptyPerson) {
        cout << "%TEST_FAILED% time=0 testname=testClear (ArrayTest) message=person array 3" << endl;
    }
    Person p3("d", "e", 3, 4.0);
    Person p4("f", "g", 4, 5.0);
    a3[0] = p3;
    a3[99] = p4;
    if (a3[0] != p3 || a3[99] != p4) {
        cout << "%TEST_FAILED% time=0 testname=testClear (ArrayTest) message=person array 4" << endl;
    }
}

void testFillWith() {
    Array<int> a1(3);
    Array<int> a2(10);
    Array<double> a3(10);
    Array<Person> a4(3);

    vector<int> v1 = {1, 2, 3, 4};
    vector<int> v2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<double> v3 = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};

    Person p1, p2("a", "b", 1, 2.0), p3("c", "d", 3, 4.0);
    vector<Person> v4 = {p1, p2, p3};

    // fillling
    try {
        a1.fillWith(v1);
        cout << "%TEST_FAILED% time=0 testname=testFillWith (ArrayTest) message=Filling a1 should fail because v1 is larger than a1!" << endl;
    } catch (InitializeException const &e) {
        // everything is OK, the exception should be thrown
    }
    a2.fillWith(v2);
    a3.fillWith(v3);
    a4.fillWith(v4);

    // testing a1
    for (auto const &e : a1) { // test for iterators at the same time
        if (e != 0) {
            cout << "%TEST_FAILED% time=0 testname=testFillWith (ArrayTest) message=a1 should have all default values!" << endl;
        }
    }

    // testing a2
    int i2 = 0;
    for (auto const &e : a2) { // test for iterators at the same time
        if (e != i2) {
            cout << "%TEST_FAILED% time=0 testname=testFillWith (ArrayTest) message=a2 isn't filled correctly!" << endl;
        }
        ++i2;
    }

    // testing a3
    double d3 = 0.0;
    for (auto const &e : a2) { // test for iterators at the same time
        if (e - d3 > 0.0001 || e - d3 < -0.0001) { // floating-point comparison
            cout << "%TEST_FAILED% time=0 testname=testFillWith (ArrayTest) message=a3 isn't filled correctly!" << endl;
        }
        d3 += 1.0;
    }

    // testing a4
    if (a4[0] != p1) {
        cout << "%TEST_FAILED% time=0 testname=testFillWith (ArrayTest) message=a4 isn't filled correctly! (1)" << endl;
    }
    if (a4[1] != p2) {
        cout << "%TEST_FAILED% time=0 testname=testFillWith (ArrayTest) message=a4 isn't filled correctly! (2)" << endl;
    }
    if (a4[2] != p3) {
        cout << "%TEST_FAILED% time=0 testname=testFillWith (ArrayTest) message=a4 isn't filled correctly! (3)" << endl;
    }
}

int main(int argc, char** argv) {
    cout << "%SUITE_STARTING% ArrayTest" << endl;
    cout << "%SUITE_STARTED%" << endl;

    cout << "%TEST_STARTED% testConstructor (ArrayTest)" << endl;
    testConstructor();
    cout << "%TEST_FINISHED% time=0 testConstructor (ArrayTest)" << endl;

    cout << "%TEST_STARTED% testIterators (ArrayTest)" << endl;
    testIterators();
    cout << "%TEST_FINISHED% time=0 testIterators (ArrayTest)" << endl;

    cout << "%TEST_STARTED% testSize (ArrayTest)" << endl;
    testSize();
    cout << "%TEST_FINISHED% time=0 testSize (ArrayTest)" << endl;

    cout << "%TEST_STARTED% testClear (ArrayTest)" << endl;
    testClear();
    cout << "%TEST_FINISHED% time=0 testClear (ArrayTest)" << endl;

    cout << "%TEST_STARTED% testFillWith (ArrayTest)" << endl;
    testFillWith();
    cout << "%TEST_FINISHED% time=0 testFillWith (ArrayTest)" << endl;

    cout << "%SUITE_FINISHED% time=0" << endl;

    return (EXIT_SUCCESS);
}
