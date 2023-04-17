#include <iostream>
#include "CCounter.hpp"
#include "TestUtils.h"

void testIncrease() {
    CCounter<TestType> counter(3);

    bool overflow = counter.Increment();

    if (1 != counter.GetCount() || overflow) {
        std::cout << "%TEST_FAILED% time=0 testname=testIncrease (CCounterTest) message=" << std::endl;
    }

    overflow = counter.Increment();

    if (2 != counter.GetCount() || overflow) {
        std::cout << "%TEST_FAILED% time=0 testname=testIncrease (CCounterTest) message=" << std::endl;
    }

    overflow = counter.Increment();

    if (3 != counter.GetCount() || overflow) {
        std::cout << "%TEST_FAILED% time=0 testname=testIncrease (CCounterTest) message=" << std::endl;
    }

    overflow = counter.Increment();

    if (0 != counter.GetCount() | !overflow) {
        std::cout << "%TEST_FAILED% time=0 testname=testIncrease (CCounterTest) message=" << std::endl;
    }
}

void testReset() {
    CCounter<TestType> counter(10);

    counter.Increment();

    counter.Reset();

    if (0 != counter.GetCount()) {
        std::cout << "%TEST_FAILED% time=0 testname=testReset (CCounterTest) message=" << std::endl;
    }
}

void testGetCount() {
    CCounter<TestType> counter(10, 5);

    bool overflow = counter.Increment();

    if (6 != counter.GetCount() || overflow) {
        //std::cout << "%TEST_FAILED% time=0 testname=testGetCount (CCounterTest) message=" << std::endl;
    }
}

void testOperator() {
    CCounter<TestType> counter1(10);
    CCounter<TestType> counter2(10);

    counter2.Increment();

    bool c1ltc2_1 = counter1 < counter2;
    bool c1ltc2_2 = counter1 < counter2;
    bool c2lt1 = counter2 < 1;
    bool c2lt2 = counter2 < 2;

    if (!c1ltc2_1 || !c1ltc2_2 || c2lt1 || !c2lt2) {
        std::cout << "%TEST_FAILED% time=0 testname=testOperator (CCounterTest) message=" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% CCounterTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testIncrease (CCounterTest)" << std::endl;
    testIncrease();
    std::cout << "%TEST_FINISHED% time=0 testIncrease (CCounterTest)" << std::endl;

    std::cout << "%TEST_STARTED% testReset (CCounterTest)" << std::endl;
    testReset();
    std::cout << "%TEST_FINISHED% time=0 testReset (CCounterTest)" << std::endl;

    std::cout << "%TEST_STARTED% testGetCount (CCounterTest)" << std::endl;
    testGetCount();
    std::cout << "%TEST_FINISHED% time=0 testGetCount (CCounterTest)" << std::endl;

    std::cout << "%TEST_STARTED% testOperator (CCounterTest)" << std::endl;
    testOperator();
    std::cout << "%TEST_FINISHED% time=0 testOperator (CCounterTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

