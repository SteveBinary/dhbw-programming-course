#include <stdlib.h>
#include <iostream>
#include "CTime.hpp"
#include "TestUtils.h"

void testSetTime() {
    CTime<TestType> time(0, 0, 0, 1);

    if (time.InSeconds() != SECS_OF_HOUR) {
        std::cout << "%TEST_FAILED% time=0 testname=testSetTime (CTimeTest) message=" << std::endl;
    }

    time.SetTime(182);

    if (time.InSeconds() != 182) {
        std::cout << "%TEST_FAILED% time=0 testname=testSetTime (CTimeTest) message=" << std::endl;
    }
}

void testGetHourOfDay() {
    CTime<TestType> time1(1, 2, 3, 0);
    CTime<TestType> time2(1, 2, 54, 1);

    bool cond1 = time1.GetHourOfDay() == 1;
    bool cond2 = time2.GetHourOfDay() == 2;

    if (!cond1 || !cond2) {
        std::cout << "%TEST_FAILED% time=0 testname=testGetHourOfDay (CTimeTest) message=" << std::endl;
    }
}

void testGetMinuteOfHour() {
    CTime<TestType> time1(1, 2, 3, 0);
    CTime<TestType> time2(2, 3, 54, 1);

    bool cond1 = time1.GetMinuteOfHour() == 2;
    bool cond2 = time2.GetMinuteOfHour() == 3;

    if (!cond1 || !cond2) {
        std::cout << "%TEST_FAILED% time=0 testname=testGetMinuteOfHour (CTimeTest) message=" << std::endl;
    }
}

void testGetSecondOfMinute() {
    CTime<TestType> time1(1, 2, 3, 0);
    CTime<TestType> time2(1, 2, 54, 1);

    bool cond1 = time1.GetSecondOfMinute() == 3;
    bool cond2 = time2.GetSecondOfMinute() == 54;

    if (!cond1 || !cond2) {
        std::cout << "%TEST_FAILED% time=0 testname=testGetSecondOfMinute (CTimeTest) message=" << std::endl;
    }
}

void testInSeconds() {
    CTime<TestType> time1(1, 2, 3, 0);
    CTime<TestType> time2(5, 2, 54, 1);
    CTime<TestType> time3(16, 52, 54, -1);
    CTime<TestType> time4(23, 59, 59, 0);
    CTime<TestType> time5(24, 0, 0, 0);
    CTime<TestType> time6(0, 0, 0, 0);

    bool cond1 = time1.InSeconds() == 1 * 60 * 60 + 2 * 60 + 3;
    bool cond2 = time2.InSeconds() == 5 * 60 * 60 + 2 * 60 + 54 + 1 * 60 * 60;
    bool cond3 = time3.InSeconds() == 16 * 60 * 60 + 52 * 60 + 54 - 1 * 60 * 60;
    bool cond4 = time4.InSeconds() == 23 * 60 * 60 + 59 * 60 + 59;
    bool cond5 = time5.InSeconds() == 24 * 60 * 60;
    bool cond6 = time6.InSeconds() == 0;

    if (!cond1 || !cond2 || !cond3 || !cond4 || !cond5 || !cond6) {
        std::cout << "%TEST_FAILED% time=0 testname=testInSeconds (CTimeTest) message=" << std::endl;
    }
}

void testComparison() {
    CTime<TestType> time1(1, 2, 3, 0);
    CTime<TestType> time2(1, 2, 3, 0);
    CTime<TestType> time3(5, 2, 54, 1);
    CTime<TestType> time4(16, 52, 54, -1);
    CTime<TestType> time5(23, 59, 59, 0);

    bool cond1 = false == (time1 >= time3);
    bool cond2 = true == (time3 >= time2);
    bool cond3 = false == (time1 > time2);
    bool cond4 = true == (time3 > time2);
    bool cond5 = false == (time3 <= time2);
    bool cond6 = true == (time1 <= time2);
    bool cond7 = false == (time1 < time2);
    bool cond8 = true == (time4 < time5);
    bool cond9 = false == (time1 == time3);
    bool cond10 = true == (time1 == time2);
    bool cond11 = false == (time1 != time2);
    bool cond12 = true == (time1 != time3);

    if (!cond1 || !cond2 || !cond3 || !cond4 || !cond5 || !cond6 || !cond7 || !cond8 || !cond9 || !cond10 || !cond11 || !cond12) {
        std::cout << "%TEST_FAILED% time=0 testname=testComparison (CTimeTest) message=" << std::endl;
    }
}

void testIncrement() {
    CTime<TestType> time(1, 2, 3, 0);

    long secsBefore = time.InSeconds();
    ++time;
    long secsAfter = time.InSeconds();

    if (secsAfter != secsBefore + 1) {
        std::cout << "%TEST_FAILED% time=0 testname=testIncrement (CTimeTest) message=" << std::endl;
    }
}

void testToString() {
    CTime<TestType> time1(0, 0, 0, 0);
    CTime<TestType> time2(10, 13, 4, 0);
    CTime<TestType> time3(2, 9, 9, 1);
    CTime<TestType> time4(2, 9, 59, -1);

    bool expected1 = "00:00:00" == time1.ToString();
    bool expected2 = "10:13:04" == time2.ToString();
    bool expected3 = "03:09:09" == time3.ToString();
    bool expected4 = "01:09:59" == time4.ToString();

    if (!expected1 || !expected2 || !expected3 || !expected4) {
        std::cout << "%TEST_FAILED% time=0 testname=testToString (CTimeTest) message=" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% CTimeTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testSetTime (CTimeTest)" << std::endl;
    testSetTime();
    std::cout << "%TEST_FINISHED% time=0 testSetTime (CTimeTest)" << std::endl;

    std::cout << "%TEST_STARTED% testGetHourOfDay (CTimeTest)" << std::endl;
    testGetHourOfDay();
    std::cout << "%TEST_FINISHED% time=0 testGetHourOfDay (CTimeTest)" << std::endl;

    std::cout << "%TEST_STARTED% testGetMinuteOfHour (CTimeTest)" << std::endl;
    testGetMinuteOfHour();
    std::cout << "%TEST_FINISHED% time=0 testGetMinuteOfHour (CTimeTest)" << std::endl;

    std::cout << "%TEST_STARTED% testGetSecondOfMinute (CTimeTest)" << std::endl;
    testGetSecondOfMinute();
    std::cout << "%TEST_FINISHED% time=0 testGetSecondOfMinute (CTimeTest)" << std::endl;

    std::cout << "%TEST_STARTED% testInSeconds (CTimeTest)" << std::endl;
    testInSeconds();
    std::cout << "%TEST_FINISHED% time=0 testInSeconds (CTimeTest)" << std::endl;

    std::cout << "%TEST_STARTED% testComparison (CTimeTest)" << std::endl;
    testComparison();
    std::cout << "%TEST_FINISHED% time=0 testComparison (CTimeTest)" << std::endl;

    std::cout << "%TEST_STARTED% testIncrement (CTimeTest)" << std::endl;
    testIncrement();
    std::cout << "%TEST_FINISHED% time=0 testIncrement (CTimeTest)" << std::endl;

    std::cout << "%TEST_STARTED% testToString (CTimeTest)" << std::endl;
    testToString();
    std::cout << "%TEST_FINISHED% time=0 testToString (CTimeTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

