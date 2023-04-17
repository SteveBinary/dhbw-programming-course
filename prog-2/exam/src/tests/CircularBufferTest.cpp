#include <stdlib.h>
#include <iostream>
#include "CircularBuffer.hpp"
#include <vector>

using namespace std;

void testConstructor() {
    try {
        CircularBuffer<int> a(0);
        cout << "%TEST_FAILED% time=0 testname=testConstructor (CircularBufferTest) message=CircularBuffer-initialization should fail!" << endl;
    } catch (InitializeException const &e) {
        // everything is OK, the exception should be thrown
    }

    try {
        CircularBuffer<int> b(-1);
        cout << "%TEST_FAILED% time=0 testname=testConstructor (CircularBufferTest) message=CircularBuffer-initialization should fail!" << endl;
    } catch (InitializeException const &e) {
        // everything is OK, the exception should be thrown
    }

    try {
        CircularBuffer<int> c(10);
    } catch (InitializeException const &e) {
        cout << "%TEST_FAILED% time=0 testname=testConstructor (CircularBufferTest) message=CircularBuffer-initialization should not fail!" << endl;
    }
}

void testIterators() {
    CircularBuffer<int> buffer(5);

    for (auto i : buffer) {
        if (i != 0) {
            cout << "%TEST_FAILED% time=0 testname=testIterators (CircularBufferTest) message=loop 1" << endl;
        }
    }

    buffer.pushOrOverwite(1);
    buffer.pushOrOverwite(2);
    buffer.pushOrOverwite(3);
    buffer.pushOrOverwite(4);
    buffer.pushOrOverwite(5);

    for (auto i = buffer.begin() + 1; i < buffer.end(); ++i) {
        if (*(i - 1) >= *i) {
            cout << "%TEST_FAILED% time=0 testname=testIterators (CircularBufferTest) message=loop 2" << endl;
        }
    }
}

void testCapacity() {
    CircularBuffer<int> buffer(5);

    if (buffer.capacity() != 5) {
        cout << "%TEST_FAILED% time=0 testname=testCapacity (CircularBufferTest) message=" << endl;
    }
}

void testIsFull() {
    CircularBuffer<int> buffer(3);

    if (buffer.isFull()) {
        cout << "%TEST_FAILED% time=0 testname=testIsFull (CircularBufferTest) message=buffer should not be full!" << endl;
    }
    buffer.pushOrOverwite(1);
    if (buffer.isFull()) {
        cout << "%TEST_FAILED% time=0 testname=testIsFull (CircularBufferTest) message=buffer should not be full!" << endl;
    }
    buffer.pushOrOverwite(2);
    if (buffer.isFull()) {
        cout << "%TEST_FAILED% time=0 testname=testIsFull (CircularBufferTest) message=buffer should not be full!" << endl;
    }
    buffer.pushOrOverwite(3);
    if (!buffer.isFull()) {
        cout << "%TEST_FAILED% time=0 testname=testIsFull (CircularBufferTest) message=buffer should be full!" << endl;
    }
}

void testIsEmpty() {
    CircularBuffer<int> buffer(3);

    if (!buffer.isEmpty()) {
        cout << "%TEST_FAILED% time=0 testname=testIsEmpty (CircularBufferTest) message=buffer should be empty!" << endl;
    }
    buffer.pushOrOverwite(1);
    if (buffer.isEmpty()) {
        cout << "%TEST_FAILED% time=0 testname=testIsEmpty (CircularBufferTest) message=buffer should not be empty!" << endl;
    }
    buffer.pushOrOverwite(2);
    if (buffer.isEmpty()) {
        cout << "%TEST_FAILED% time=0 testname=testIsEmpty (CircularBufferTest) message=buffer should not be empty!" << endl;
    }
    buffer.pushOrOverwite(3);
    if (buffer.isEmpty()) {
        cout << "%TEST_FAILED% time=0 testname=testIsEmpty (CircularBufferTest) message=buffer should not be empty!" << endl;
    }
}

void testSize() {
    CircularBuffer<int> buffer(3);

    if (buffer.size() != 0) {
        cout << "%TEST_FAILED% time=0 testname=testSize (CircularBufferTest) message=buffer-size should be 0" << endl;
    }
    buffer.pushOrOverwite(1);
    if (buffer.size() != 1) {
        cout << "%TEST_FAILED% time=0 testname=testSize (CircularBufferTest) message=buffer-size should be 1" << endl;
    }
    buffer.pushOrOverwite(2);
    if (buffer.size() != 2) {
        cout << "%TEST_FAILED% time=0 testname=testSize (CircularBufferTest) message=buffer-size should be 2" << endl;
    }
    buffer.pushOrOverwite(3);
    if (buffer.size() != 3) {
        cout << "%TEST_FAILED% time=0 testname=testSize (CircularBufferTest) message=buffer-size should be 3" << endl;
    }
}

void testPushOrOverwite() {
    CircularBuffer<int> buffer(3);

    buffer.pushOrOverwite(5);
    buffer.pushOrOverwite(2);
    buffer.pushOrOverwite(3);
    buffer.pushOrOverwite(0); // should overwrite the 5

    for (auto i = buffer.begin() + 1; i < buffer.end(); ++i) {
        if (*(i - 1) >= *i) {
            cout << "%TEST_FAILED% time=0 testname=testPushOrOverwite (CircularBufferTest) message=" << endl;
        }
    }
}

void testPushOrReject() {
    CircularBuffer<int> buffer(3);

    buffer.pushOrReject(1);
    buffer.pushOrReject(2);
    buffer.pushOrReject(3);
    buffer.pushOrReject(5); // should be rejected

    for (auto i = buffer.begin() + 1; i < buffer.end(); ++i) {
        if (*(i - 1) >= *i) {
            cout << "%TEST_FAILED% time=0 testname=testPushOrReject (CircularBufferTest) message=" << endl;
        }
    }
}

void testPopInto() {
    CircularBuffer<int> buffer(3);

    buffer.pushOrOverwite(1);
    buffer.pushOrReject(2);
    buffer.pushOrOverwite(3);

    int i1;
    bool successful1 = buffer.popInto(i1);
    if (!successful1 || i1 != 1) {
        cout << "%TEST_FAILED% time=0 testname=testPopInto (CircularBufferTest) message=error on i1" << endl;
    }

    int i2;
    bool successful2 = buffer.popInto(i2);
    if (!successful2 || i2 != 2) {
        cout << "%TEST_FAILED% time=0 testname=testPopInto (CircularBufferTest) message=error on i2" << endl;
    }

    int i3;
    bool successful3 = buffer.popInto(i3);
    if (!successful3 || i3 != 3) {
        cout << "%TEST_FAILED% time=0 testname=testPopInto (CircularBufferTest) message=error on i3" << endl;
    }

    int i4;
    bool successful4 = buffer.popInto(i4);
    if (successful4) {
        cout << "%TEST_FAILED% time=0 testname=testPopInto (CircularBufferTest) message=error on i4" << endl;
    }
}

void testClear() {
    CircularBuffer<int> buffer(3);

    if (buffer.size() != 0) {
        cout << "%TEST_FAILED% time=0 testname=testClear (CircularBufferTest) message=1" << endl;
    }

    buffer.pushOrOverwite(1);
    if (buffer.size() != 1) {
        cout << "%TEST_FAILED% time=0 testname=testClear (CircularBufferTest) message=2" << endl;
    }

    buffer.clear();
    if (buffer.size() != 0) {
        cout << "%TEST_FAILED% time=0 testname=testClear (CircularBufferTest) message=3" << endl;
    }

    int i = 0;
    bool successful = buffer.popInto(i);
    if (successful || i == 1) {
        cout << "%TEST_FAILED% time=0 testname=testClear (CircularBufferTest) message=4" << endl;
    }

    buffer.pushOrOverwite(2);
    if (buffer.size() != 1) {
        cout << "%TEST_FAILED% time=0 testname=testClear (CircularBufferTest) message=5" << endl;
    }

    buffer.clear();
    if (buffer.size() != 0) {
        cout << "%TEST_FAILED% time=0 testname=testClear (CircularBufferTest) message=6" << endl;
    }

    int j = 0;
    successful = buffer.popInto(j);
    if (successful || j == 2) {
        cout << "%TEST_FAILED% time=0 testname=testClear (CircularBufferTest) message=7" << endl;
    }
}

void testFillWith() {
    CircularBuffer<int> buffer1(3);
    CircularBuffer<int> buffer2(3);
    vector<int> v1 = {{1, 2, 3}};
    vector<int> v2 = {{1, 2, 3, 4}};

    buffer1.fillWith(v1);
    buffer2.fillWith(v2);

    if (buffer1.size() != 3 || buffer1.capacity() != 3) {
        cout << "%TEST_FAILED% time=0 testname=testFillWith (CircularBufferTest) message=1" << endl;
    }

    if (buffer2.size() != 3 || buffer2.capacity() != 3) {
        cout << "%TEST_FAILED% time=0 testname=testFillWith (CircularBufferTest) message=2" << endl;
    }

    int j = 1;
    for (auto i : buffer1) {
        if (i != j) {
            cout << "%TEST_FAILED% time=0 testname=testFillWith (CircularBufferTest) message=3" << endl;
        }
        ++j;
    }

    j = 1;
    for (auto i : buffer2) {
        if (i != j) {
            cout << "%TEST_FAILED% time=0 testname=testFillWith (CircularBufferTest) message=4" << endl;
        }
        ++j;
    }
}

int main(int argc, char** argv) {
    cout << "%SUITE_STARTING% CircularBufferTest" << endl;
    cout << "%SUITE_STARTED%" << endl;

    cout << "%TEST_STARTED% testConstructor (CircularBufferTest)" << endl;
    testConstructor();
    cout << "%TEST_FINISHED% time=0 testConstructor (CircularBufferTest)" << endl;

    cout << "%TEST_STARTED% testIterators (CircularBufferTest)" << endl;
    testIterators();
    cout << "%TEST_FINISHED% time=0 testIterators (CircularBufferTest)" << endl;

    cout << "%TEST_STARTED% testCapacity (CircularBufferTest)" << endl;
    testCapacity();
    cout << "%TEST_FINISHED% time=0 testCapacity (CircularBufferTest)" << endl;

    cout << "%TEST_STARTED% testIsFull (CircularBufferTest)" << endl;
    testIsFull();
    cout << "%TEST_FINISHED% time=0 testIsFull (CircularBufferTest)" << endl;

    cout << "%TEST_STARTED% testIsEmpty (CircularBufferTest)" << endl;
    testIsEmpty();
    cout << "%TEST_FINISHED% time=0 testIsEmpty (CircularBufferTest)" << endl;

    cout << "%TEST_STARTED% testSize (CircularBufferTest)" << endl;
    testSize();
    cout << "%TEST_FINISHED% time=0 testSize (CircularBufferTest)" << endl;

    cout << "%TEST_STARTED% testPushOrOverwite (CircularBufferTest)" << endl;
    testPushOrOverwite();
    cout << "%TEST_FINISHED% time=0 testPushOrOverwite (CircularBufferTest)" << endl;

    cout << "%TEST_STARTED% testPushOrReject (CircularBufferTest)" << endl;
    testPushOrReject();
    cout << "%TEST_FINISHED% time=0 testPushOrReject (CircularBufferTest)" << endl;

    cout << "%TEST_STARTED% testPopInto (CircularBufferTest)" << endl;
    testPopInto();
    cout << "%TEST_FINISHED% time=0 testPopInto (CircularBufferTest)" << endl;

    cout << "%TEST_STARTED% testClear (CircularBufferTest)" << endl;
    testClear();
    cout << "%TEST_FINISHED% time=0 testClear (CircularBufferTest)" << endl;

    cout << "%TEST_STARTED% testFillWith (CircularBufferTest)" << endl;
    testFillWith();
    cout << "%TEST_FINISHED% time=0 testFillWith (CircularBufferTest)" << endl;

    cout << "%SUITE_FINISHED% time=0" << endl;

    return (EXIT_SUCCESS);
}
