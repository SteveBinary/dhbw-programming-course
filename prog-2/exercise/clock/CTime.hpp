#pragma once

#include <string>

#define SECS_OF_MIN 60
#define SECS_OF_HOUR (60 * SECS_OF_MIN)
#define SECS_OF_DAY (24 * SECS_OF_HOUR)

template <class T>
class CTime {
public:

    CTime(T h, T m, T s, T timeZone) {
        SetTime(h * SECS_OF_HOUR + m * SECS_OF_MIN + s + timeZone * SECS_OF_HOUR);
    }
    
    CTime(long initialSeconds) : seconds(initialSeconds) {
    }

    bool operator>=(const CTime& t) const {
        return seconds >= t.seconds;
    }

    bool operator>(const CTime& t) const {
        return seconds > t.seconds;
    }

    bool operator<=(const CTime& t) const {
        return seconds <= t.seconds;
    }

    bool operator<(const CTime& t) const {
        return seconds < t.seconds;
    }

    bool operator==(const CTime& t) const {
        return seconds == t.seconds;
    }

    bool operator!=(const CTime& t) const {
        return seconds != t.seconds;
    }

    CTime& operator++() {
        ++seconds;
        return *this;
    }

    void SetTime(long seconds_) {
        seconds = seconds_;
    }

    T GetHourOfDay() const {
        return (int) (seconds / SECS_OF_HOUR) % 24;
    }

    T GetMinuteOfHour() const {
        return (int) (seconds / SECS_OF_MIN) % 60;
    }

    T GetSecondOfMinute() const {
        return seconds % SECS_OF_MIN;
    }

    std::string ToString() const {
        std::string result = "";

        if (GetHourOfDay() <= 9) result += "0";
        result += std::to_string(GetHourOfDay()) + ":";

        if (GetMinuteOfHour() <= 9) result += "0";
        result += std::to_string(GetMinuteOfHour()) + ":";

        if (GetSecondOfMinute() <= 9) result += "0";
        result += std::to_string(GetSecondOfMinute());

        return result;
    }

    long InSeconds() const {
        return seconds;
    }

private:
    long seconds;
};