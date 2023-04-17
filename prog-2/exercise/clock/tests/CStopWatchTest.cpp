#include <stdlib.h>
#include <iostream>
#include "CStopWatch.hpp"
#include "TestUtils.h"

void testWatch() {
    CStopWatch<TestType> stopWatch;
    stopWatch.StartWatch();

    Wait(1100);

    stopWatch.StartWatch();

    Wait(2100);

    long elapsedTime = stopWatch.StopWatch();

    if (elapsedTime != 2) {
        std::cout << "%TEST_FAILED% time=0 testname=testWatch (CStopWatchTest) message=" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% CStopWatchTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testWatch (CStopWatchTest)" << std::endl;
    testWatch();
    std::cout << "%TEST_FINISHED% time=0 testWatch (CStopWatchTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

