#pragma once

#include <chrono>
#include <thread>

typedef char TestType;
typedef std::chrono::high_resolution_clock::time_point timepoint;
typedef std::chrono::duration<double> duration;

timepoint MeasureTime();
double TimeInterval(timepoint t1, timepoint t2);

inline void Wait(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
