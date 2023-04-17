#include <iostream>
#include "CWorldTimeClock.hpp"
#include "TestUtils.h"

void testSetTimeZone() {
    CWorldTimeClock<TestType> clock;
    clock.SetGMT(CTime<TestType>(10, 0, 0, 0));

    clock.Start();

    if (clock.GetGMT() != CTime<TestType>(10, 0, 0, 0)) {
        std::cout << "%TEST_FAILED% time=0 testname=testSetTimeZone (CWorldTimeClockTest) message=" << std::endl;
    }

    clock.SetTimeZone(1);

    if (clock.GetGMT() != CTime<TestType>(10, 0, 0, 1)) {
        std::cout << "%TEST_FAILED% time=0 testname=testSetTimeZone (CWorldTimeClockTest) message=" << std::endl;
    }

    Wait(2300);
    clock.SetTimeZone(-1);
    Wait(2300);

    if (clock.GetGMT() != CTime<TestType>(10, 0, 4, -1)) {
        std::cout << "%TEST_FAILED% time=0 testname=testSetTimeZone (CWorldTimeClockTest) message=" << std::endl;
    }

    clock.Stop();
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% CWorldTimeClockTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testSetTimeZone (CWorldTimeClockTest)" << std::endl;
    testSetTimeZone();
    std::cout << "%TEST_FINISHED% time=0 testSetTimeZone (CWorldTimeClockTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

