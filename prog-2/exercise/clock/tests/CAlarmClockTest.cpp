#include <stdlib.h>
#include <iostream>
#include "CAlarmClock.hpp"
#include "TestUtils.h"

void testSetAlertTime() {
    CAlarmClock<TestType> alarmClock;
    CTime<TestType> time(1, 0, 0, 0);

    alarmClock.SetAlertTime(time);

    if (!alarmClock.GetAlertFlag() || alarmClock.GetAlertTime() != CTime<TestType>(1, 0, 0, 0)) {
        std::cout << "%TEST_FAILED% time=0 testname=testSetAlertTime (CAlarmClockTest) message=" << std::endl;
    }
}

void testSetAlertDelay() {
    CAlarmClock<TestType> alarmClock;
    int delay = 131;

    if (alarmClock.GetAlertTime() != CTime<TestType>(0, 0, 0, 0) || alarmClock.GetAlertFlag()) {
        std::cout << "%TEST_FAILED% time=0 testname=testSetAlertDelay (CAlarmClockTest) message=" << std::endl;
    }

    alarmClock.SetAlertDelay(delay);

    if (alarmClock.GetAlertTime() != CTime<TestType>(0, 2, 11, 0) || !alarmClock.GetAlertFlag()) {
        std::cout << "%TEST_FAILED% time=0 testname=testSetAlertDelay (CAlarmClockTest) message=" << std::endl;
    }
}

void testStartCheck() {
    CAlarmClock<TestType> alarmClock;

    if (alarmClock.GetAlertFlag()) {
        std::cout << "%TEST_FAILED% time=0 testname=testStartCheck (CAlarmClockTest) message=" << std::endl;
    }

    alarmClock.SetAlertTime(CTime<TestType>(0, 0, 2, 0));
    alarmClock.StartCheck();
    Wait(1000);

    if (!alarmClock.GetAlertFlag()) {
        std::cout << "%TEST_FAILED% time=0 testname=testStartCheck (CAlarmClockTest) message=" << std::endl;
    }

    Wait(1100);

    if (alarmClock.GetAlertFlag()) {
        std::cout << "%TEST_FAILED% time=0 testname=testStartCheck (CAlarmClockTest) message=" << std::endl;
    }
}

void testActivateAlert() {
    CAlarmClock<TestType> alarmClock;

    alarmClock.ActivateAlert();

    if (!alarmClock.GetAlertFlag()) {
        std::cout << "%TEST_FAILED% time=0 testname=testActivateAlert (CAlarmClockTest) message=" << std::endl;
    }
}

void testDeactivateAlert() {
    CAlarmClock<TestType> alarmClock(CTime<TestType>(1, 0, 0, 0));

    if (!alarmClock.GetAlertFlag()) {
        std::cout << "%TEST_FAILED% time=0 testname=testActivateAlert (CAlarmClockTest) message=" << std::endl;
    }

    alarmClock.DeactivateAlert();

    if (alarmClock.GetAlertFlag()) {
        std::cout << "%TEST_FAILED% time=0 testname=testActivateAlert (CAlarmClockTest) message=" << std::endl;
    }
}

void testGetAlertTime() {
    CAlarmClock<TestType> alarmClock;
    CTime<TestType> time1 = alarmClock.GetAlertTime();

    alarmClock.SetAlertTime(CTime<TestType>(1, 1, 1, 0));
    CTime<TestType> time2 = alarmClock.GetAlertTime();

    alarmClock.SetAlertDelay(91);
    CTime<TestType> time3 = alarmClock.GetAlertTime();

    if (time1 != CTime<TestType>(0, 0, 0, 0) || time2 != CTime<TestType>(1, 1, 1, 0) || time3 != CTime<TestType>(1, 2, 32, 0)) {
        std::cout << "%TEST_FAILED% time=0 testname=testGetAlertTime (CAlarmClockTest) message=" << std::endl;
    }
}

void testRemainingTime() {
    CAlarmClock<TestType> alarmClock(CTime<TestType>(0, 0, 5, 0));
    alarmClock.SetGMT(CTime<TestType>(0, 0, 3, 0));
    alarmClock.StartCheck();

    CTime<TestType> remainingTime1 = alarmClock.RemainingTime();
    Wait(1100);

    CTime<TestType> remainingTime2 = alarmClock.RemainingTime();
    Wait(1000);

    CTime<TestType> remainingTime3 = alarmClock.RemainingTime();
    Wait(1000);


    if (remainingTime1 != CTime<TestType>(0, 0, 2, 0) || remainingTime2 != CTime<TestType>(0, 0, 1, 0) || remainingTime3 != CTime<TestType>(0, 0, 0, 0)) {
        std::cout << "%TEST_FAILED% time=0 testname=testRemainingTime (CAlarmClockTest) message=" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% CAlarmClockTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testSetAlertTime (CAlarmClockTest)" << std::endl;
    testSetAlertTime();
    std::cout << "%TEST_FINISHED% time=0 testSetAlertTime (CAlarmClockTest)" << std::endl;

    std::cout << "%TEST_STARTED% testSetAlertDelay (CAlarmClockTest)" << std::endl;
    testSetAlertDelay();
    std::cout << "%TEST_FINISHED% time=0 testSetAlertDelay (CAlarmClockTest)" << std::endl;

    std::cout << "%TEST_STARTED% testStartCheck (CAlarmClockTest)" << std::endl;
    testStartCheck();
    std::cout << "%TEST_FINISHED% time=0 testStartCheck (CAlarmClockTest)" << std::endl;

    std::cout << "%TEST_STARTED% testActivateAlert (CAlarmClockTest)" << std::endl;
    testActivateAlert();
    std::cout << "%TEST_FINISHED% time=0 testActivateAlert (CAlarmClockTest)" << std::endl;

    std::cout << "%TEST_STARTED% testDeactivateAlert (CAlarmClockTest)" << std::endl;
    testDeactivateAlert();
    std::cout << "%TEST_FINISHED% time=0 testDeactivateAlert (CAlarmClockTest)" << std::endl;

    std::cout << "%TEST_STARTED% testGetAlertTime (CAlarmClockTest)" << std::endl;
    testGetAlertTime();
    std::cout << "%TEST_FINISHED% time=0 testGetAlertTime (CAlarmClockTest)" << std::endl;

    std::cout << "%TEST_STARTED% testRemainingTime (CAlarmClockTest)" << std::endl;
    testRemainingTime();
    std::cout << "%TEST_FINISHED% time=0 testRemainingTime (CAlarmClockTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

