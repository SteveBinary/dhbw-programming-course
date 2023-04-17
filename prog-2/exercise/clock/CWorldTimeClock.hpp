#pragma once

#include <iostream>
#include <thread>
#include "CGMTClock.hpp"
#include "CTime.hpp"

template <class T>
class CWorldTimeClock : public CGMTClock<T> {
private:
    T timeZone;

public:

    CWorldTimeClock(T timeZone_) : CGMTClock<T>(0, 0, 0) {
        SetTimeZone(timeZone_);
    }

    CWorldTimeClock() : CGMTClock<T>(0, 0, 0) {
        SetTimeZone((T) 0);
    }
    
    void DisplayClock() const {
        std::cout << this->GetGMT().ToString() << " " << std::showpos << timeZone << std::endl;
        std::cout.flush();
    }

    void SetTimeZone(T newTimeZone) {
        this->SetGMT(CTime<T>(this->GetHours(), this->GetMinutes(), this->GetSeconds(), newTimeZone - timeZone));
        timeZone = newTimeZone;
    }
};
