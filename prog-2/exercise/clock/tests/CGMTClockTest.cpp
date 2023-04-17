#include <stdlib.h>
#include <iostream>
#include "CGMTClock.hpp"
#include "TestUtils.h"

class TestClock : public CGMTClock<TestType> {
public:
    int testInt;

    TestClock() : CGMTClock(0, 0, 0) {
    }

    void DisplayClock() const {
        std::cout << this->GetGMT().ToString() << std::endl;
        std::cout.flush();
    }

    bool IsRunning() {
        return this->isRunning;
    }
};

void testStart() {
    TestClock cGMTClock;
    cGMTClock.Start();

    Wait(3500);

    CTime<TestType> currentTime = cGMTClock.GetGMT();

    if (currentTime != CTime<TestType>(0, 0, 3, 0)) {
        std::cout << "%TEST_FAILED% time=0 testname=testStart (CGMTClockTest) message=" << std::endl;
    }

    Wait(2700);

    currentTime = cGMTClock.GetGMT();

    if (currentTime != CTime<TestType>(0, 0, 6, 0)) {
        std::cout << "%TEST_FAILED% time=0 testname=testStart (CGMTClockTest) message=" << std::endl;
    }

    cGMTClock.Stop();
}

void testSetGetGMT() {
    CTime<TestType> time1(1, 2, 54, 0);
    TestClock cGMTClock;
    cGMTClock.SetGMT(time1);

    CTime<TestType> currentTime = cGMTClock.GetGMT();

    if (currentTime != CTime<TestType>(1, 2, 54, 0)) {
        std::cout << "%TEST_FAILED% time=0 testname=testSetGMT (CGMTClockTest) message=" << std::endl;
    }

    cGMTClock.Stop();
}

void testResetTime() {
    TestClock cGMTClock;

    cGMTClock.Start();
    Wait(3500);
    CTime<TestType> stopTime = cGMTClock.ResetTime();

    if (stopTime != CTime<TestType>(0, 0, 3, 0) || cGMTClock.IsRunning()) {
        std::cout << "%TEST_FAILED% time=0 testname=testResetTime (CGMTClockTest) message=" << std::endl;
    }
}

void testStop() {
    TestClock cGMTClock;

    cGMTClock.Start();
    Wait(3200);
    cGMTClock.Stop();

    if (cGMTClock.IsRunning()) {
        std::cout << "%TEST_FAILED% time=0 testname=testStop (CGMTClockTest) message=" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% CGMTClockTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testStart (CGMTClockTest)" << std::endl;
    testStart();
    std::cout << "%TEST_FINISHED% time=0 testStart (CGMTClockTest)" << std::endl;

    std::cout << "%TEST_STARTED% testSetGMT (CGMTClockTest)" << std::endl;
    testSetGetGMT();
    std::cout << "%TEST_FINISHED% time=0 testSetGMT (CGMTClockTest)" << std::endl;

    std::cout << "%TEST_STARTED% testResetTime (CGMTClockTest)" << std::endl;
    testResetTime();
    std::cout << "%TEST_FINISHED% time=0 testResetTime (CGMTClockTest)" << std::endl;

    std::cout << "%TEST_STARTED% testStop (CGMTClockTest)" << std::endl;
    testStop();
    std::cout << "%TEST_FINISHED% time=0 testStop (CGMTClockTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

