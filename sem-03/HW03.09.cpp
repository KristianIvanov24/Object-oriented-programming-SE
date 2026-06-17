// HW03.09.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>

namespace configConstants {
    const int HOURS_IN_DAY = 24;
    const int MINUTES_IN_HOUR = 60;
    const int SECONDS_IN_MINUTE = 60;
    const int SECONDS_IN_HOUR = 3600;

    const int DINNER_EARLY_HOUR = 20;
    const int DINNER_EARLY_MINUTE = 30;
    const int DINNER_PEAK_HOUR = 21;
    const int DINNER_LATE_HOUR = 22;

    const int PARTY_START_HOUR = 23;
    const int PARTY_END_HOUR = 6;
}


class Time {

    unsigned int hours;
    unsigned int minutes;
    unsigned int seconds; 

    void correctTime() {
        if (this->seconds == configConstants::SECONDS_IN_MINUTE) {
            this->minutes += 1;
            this->seconds = 0;
        }
        if (this->minutes == configConstants::MINUTES_IN_HOUR) {
            this->hours += 1;
            this->minutes = 0;
        }
        if (this->hours == configConstants::HOURS_IN_DAY) {
            this->hours = 0;
        }
    }

public:
    Time() :hours(0), minutes(0), seconds(0) {

    }
    Time(int hours, int minutes, int seconds) {
        this->setSeconds(seconds);
        this->setMinutes(minutes);
        this->setHours(hours);
    }

    void setHours(int hours) {
        if (hours >= 0 && hours < configConstants::HOURS_IN_DAY)
            this->hours = hours;
        else if(hours>= configConstants::HOURS_IN_DAY) {
            while (hours >= configConstants::HOURS_IN_DAY) {
                hours -= configConstants::HOURS_IN_DAY;
            }
            this->hours = hours;
        }else
        this->hours = 0; 
    }

    void setMinutes(int minutes) {
        if (minutes >= 0 && minutes < configConstants::MINUTES_IN_HOUR)
            this->minutes = minutes;
        else if (minutes >= configConstants::MINUTES_IN_HOUR) {
            while (minutes >= configConstants::MINUTES_IN_HOUR) {
                minutes -= configConstants::MINUTES_IN_HOUR;
            }
            this->minutes = minutes;
        }
        else
            this->minutes = 0; 
    }

    void setSeconds(int seconds) {
        if (seconds >= 0 && seconds < configConstants::SECONDS_IN_MINUTE)
            this->seconds = seconds;
        else if (seconds >= configConstants::SECONDS_IN_MINUTE) {
            while (seconds >= configConstants::SECONDS_IN_MINUTE) {
                seconds -= configConstants::SECONDS_IN_MINUTE;
            }
            this->seconds = seconds;
        }
        else
            this->seconds = 0; 
    }

    int getHours() const {
        return this->hours;
    }

    int getMinutes() const {
        return this->minutes;
    }

    int getSeconds() const {
        return this->seconds;
    }

    void updateTimeByOneSecond() {

        this->seconds += 1;
        this->correctTime();
    }

    bool isTimeForDinner() const {
        return this->hours == configConstants::DINNER_PEAK_HOUR ||
            (this->hours == configConstants::DINNER_EARLY_HOUR && this->minutes >= configConstants::DINNER_EARLY_MINUTE) ||
            this->hours == configConstants::DINNER_LATE_HOUR && this->minutes==0 && this->seconds == 0;
    }

    bool isTimeForParty() const {
        return this->hours == configConstants::PARTY_START_HOUR ||
            this->hours < configConstants::PARTY_END_HOUR ||
            (this->hours == configConstants::PARTY_END_HOUR && this->minutes == 0 && this->seconds == 0);
    }

    int toSeconds() const {
        return this->hours * configConstants::SECONDS_IN_HOUR + this->minutes * configConstants::MINUTES_IN_HOUR + this->seconds;
    }

    Time getTimeToMidnight() const {
        int totalSeconds = this->toSeconds();
        if (totalSeconds == 0) {
            return Time(0, 0, 0);
        }

        int remaining = configConstants::HOURS_IN_DAY* configConstants::SECONDS_IN_HOUR - totalSeconds;
        return { remaining / configConstants::SECONDS_IN_HOUR, (remaining % configConstants::SECONDS_IN_HOUR) / configConstants::MINUTES_IN_HOUR, remaining % configConstants::MINUTES_IN_HOUR };
    }

    Time getDiffBetweenTimes(const Time& inputTime) const {
        int totalSecondsTime = this->toSeconds();
        int totalSecondsOtherTime = inputTime.toSeconds();

        int diff = std::abs(totalSecondsTime - totalSecondsOtherTime);

        return { diff / configConstants::SECONDS_IN_HOUR, (diff % configConstants::SECONDS_IN_HOUR) / configConstants::MINUTES_IN_HOUR, diff % configConstants::MINUTES_IN_HOUR };
    }

    int compare(const Time& other) const {
        int mySeconds = this->toSeconds();
        int otherSeconds = other.toSeconds();

        if (mySeconds > otherSeconds) 
            return 1;
        if (mySeconds < otherSeconds) 
            return -1;

        return 0;
    }

    void printTime() const {
        std::cout << this->hours << ":" <<this->minutes << ":" <<this->seconds << std::endl;
    }
};

void printTimes(const Time* times, size_t size) {
    for (int i = 0; i < size; ++i) {
        times[i].printTime();
    }
}

void sortTimes(Time* times, size_t size) {
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size - 1; j++)
        {
            if (times[j].toSeconds() > times[j + 1].toSeconds()) {
                swapTimes(times[j], times[j + 1]);
            }
        }
    }
}

void swapTimes(Time& timeA, Time& timeB) {
    Time timeTemp = timeA;
    timeA = timeB;
    timeB = timeTemp;
}

int main()
{
    Time times[10] = {
        Time(8, 45, 12),
        Time(22, 15, 30),
        Time(3, 0, 59),
        Time(16, 20, 0),
        Time(0, 1, 1),
        Time(21, 30, 0),
        Time(9, 9, 9),
        Time(11, 59, 59),
        Time(19, 0, 0),
        Time(5, 30, 45)
    };

    printTimes(times, 10);
    sortTimes(times, 10);
    printTimes(times, 10);

    return 0;
}