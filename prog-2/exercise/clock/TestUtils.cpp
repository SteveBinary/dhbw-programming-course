#include <math.h>
#include <chrono>
#include "TestUtils.h"

using namespace std;

timepoint MeasureTime() {
    return std::chrono::high_resolution_clock::now();
}

double TimeInterval(timepoint t1, timepoint t2) {
    return round(((duration) (t2 - t1)).count() * 1000.0) / 1000.0;
}
