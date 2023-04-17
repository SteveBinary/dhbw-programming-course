#pragma once

#include "CTime.hpp"
#include "CWorldTimeClock.hpp"

#define CHECKING_INTERVAL_MS 10

template <class T>
class CStopWatch : private CWorldTimeClock<T> {
private:
    bool isRunning = false;

    void CheckTime() {
        CTime<T> previous = this->GetGMT();
        DisplayTime();

        while (isRunning) {
            if (previous != this->GetGMT()) {
                DisplayTime();
                previous = this->GetGMT();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(CHECKING_INTERVAL_MS));
        }
        return;
    }

    void StartCheck() {
        isRunning = true;
        std::thread myThread(&CStopWatch::CheckTime, this);
        myThread.detach();
        this->Start();
    }

    void DisplayTime() {
        std::cout << "Abgelaufene Zeit: " << this->GetGMT().ToString() << std::endl;
    }

public:

    void StartWatch() {
        if (isRunning) {
            this->SetGMT(CTime<T>(0, 0, 0, 0));
        } else {
            StartCheck();
        }
    }

    long StopWatch() {
        if (!isRunning) return 0;

        isRunning = false;
        return this->GetGMT().InSeconds();
    }
};
