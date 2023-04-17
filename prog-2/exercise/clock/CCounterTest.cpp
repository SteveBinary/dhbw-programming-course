#include <stdlib.h>
#include <iostream>
#include "CCounter.hpp"


void testReset() {
    CCounter counter = new Counter();
    
    
    
    counter.Reset();
    if (true) {
        std::cout << "%TEST_FAILED% time=0 testname=testReset (CCounterTest) message=error message sample" << std::endl;
    }
}

void testGetCount() {
    CCounter cCounter = new Counter();
    unsigned int result = cCounter.GetCount();
    
    if (true) {
        std::cout << "%TEST_FAILED% time=0 testname=testGetCount (CCounterTest) message=error message sample" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% CCounterTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testGetCount (CCounterTest)" << std::endl;
    testGetCount();
    std::cout << "%TEST_FINISHED% time=0 testGetCount (CCounterTest)" << std::endl;

    std::cout << "%TEST_STARTED% testReset (CCounterTest)" << std::endl;
    testReset();
    std::cout << "%TEST_FINISHED% time=0 testReset (CCounterTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

