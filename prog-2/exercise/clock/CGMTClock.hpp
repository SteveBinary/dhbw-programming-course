#pragma once

#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include "CCounter.hpp"
#include "CTime.hpp"

template <class T>
class CGMTClock {
protected:
    bool isRunning = false;
    CCounter<T> secondsCounter;
    CCounter<T> minutesCounter;
    CCounter<T> hoursCounter;

    T GetHours() const {
        return hoursCounter.GetCount();
    }

    T GetMinutes() const {
        return minutesCounter.GetCount();
    }

    T GetSeconds() const {
        return secondsCounter.GetCount();
    }

    bool IncrementSeconds() {
        return secondsCounter.Increment();
    }

    bool IncrementMinutes() {
        return minutesCounter.Increment();
    }

    bool IncrementHours() {
        return hoursCounter.Increment();
    }

    void RunTillStop() {
        while (isRunning) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            if (IncrementSeconds()) {
                std::cout << "Minutenwechsel" << std::endl;
                if (IncrementMinutes()) {
                    std::cout << "Stundenwechsel" << std::endl;
                    if (IncrementHours()) {
                        std::cout << "Tageswechsel" << std::endl;
                    }
                }
            }
        }

        return;
    }

public:

    CGMTClock(T initialHours, T initialMinutes, T initialSeconds) :
    secondsCounter((T) 59, initialSeconds),
    minutesCounter((T) 59, initialMinutes),
    hoursCounter((T) 23, initialHours) {
    }

    CGMTClock(const CGMTClock<T> &donor) : CGMTClock(donor.GetHours(), donor.GetMinutes(), donor.GetSeconds()) {
    }

    ~CGMTClock() {
        Stop();
    }

    virtual void Start() {
        isRunning = true;
        std::thread myThread(&CGMTClock::RunTillStop, this);
        myThread.detach();
    }

    void SetGMT(CTime<T> time) {
        hoursCounter.SetCount(time.GetHourOfDay());
        minutesCounter.SetCount(time.GetMinuteOfHour());
        secondsCounter.SetCount(time.GetSecondOfMinute());
    }

    CTime<T> GetGMT() const {
        return CTime<T>(GetHours(), GetMinutes(), GetSeconds(), 0);
    }

    CTime<T> ResetTime() {
        CTime<T> time = GetGMT();

        hoursCounter.Reset();
        minutesCounter.Reset();
        secondsCounter.Reset();
        Stop();

        return time;
    }

    void Stop() {
        isRunning = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    virtual void DisplayClock() const = 0;
};
