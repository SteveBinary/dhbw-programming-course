#pragma once

#include <thread>
#include <chrono>
#include <windows.h>
#include "CWorldTimeClock.hpp"

#define CHECKING_INTERVAL_MS 10

template <class T>
class CAlarmClock : public CWorldTimeClock<T> {
private:
    CTime<T> alertTime;
    bool alertFlag;

public:

    CAlarmClock() : alertTime(CTime<T>(0, 0, 0, 0)), alertFlag(false) {
    }

    CAlarmClock(CTime<T> alertTime_) : alertTime(alertTime_), alertFlag(true) {
    }

    void DisplayAlarmInfo() const {
        std::string alertFlagRepresentation = "";
        if (alertFlag) {
            alertFlagRepresentation = "an";
        } else {
            alertFlagRepresentation = "aus";
        }

        std::cout << "Alarmzeit: " << alertTime.ToString() << " " << alertFlagRepresentation
                << " | aktuelle Zeit: " << this->GetGMT().ToString()
                << " | verbleibend: " << RemainingTime().ToString() << std::endl;
    }

    inline void SetAlertTime(CTime<T> time) {
        alertTime = time;
        ActivateAlert();
    }

    inline void SetAlertDelay(int seconds) {
        alertTime.SetTime(alertTime.InSeconds() + seconds);
        ActivateAlert();
    }

    void CheckAlert() {
        if (alertTime < this->GetGMT()) {
            return;
        }

        CTime<T> previousTime = this->GetGMT();
        DisplayAlarmInfo();

        while (alertFlag) {
            // Display only if time changed. Needed because checking intervall could be less than one second.
            if (previousTime != this->GetGMT()) {
                DisplayAlarmInfo();
                previousTime = this->GetGMT();
            }

            if (alertTime <= this->GetGMT()) {
                std::cout << "ALARM" << std::endl;
                DeactivateAlert();
                this->Stop();
                Beep(523, 500);
                Beep(523, 400);
            } else {
                // higher checking intervall results in higher precision
                std::this_thread::sleep_for(std::chrono::milliseconds(CHECKING_INTERVAL_MS));
            }
        }

        return;
    }

    void StartCheck() {
        this->isRunning = true;
        std::thread myThread(&CAlarmClock::CheckAlert, this);
        myThread.detach();
        this->Start();
    }

    inline void ActivateAlert() {
        alertFlag = true;
    }

    inline void DeactivateAlert() {
        alertFlag = false;
    }

    CTime<T> GetAlertTime() const {
        return alertTime;
    }

    CTime<T> RemainingTime() const {
        return CTime<T>(alertTime.InSeconds() - this->GetGMT().InSeconds());
    }

    bool GetAlertFlag() const {
        return alertFlag;
    }
};
