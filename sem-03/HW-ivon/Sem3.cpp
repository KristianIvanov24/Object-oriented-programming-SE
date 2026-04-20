

#include <iostream>




namespace timeConstants 
{
    const int MIN_VAL = 0;
    const int MAX_HOURS = 23;
    const int MAX_MINS_SECS = 59;

    const int SECS_IN_MIN = 60;
    const int MINS_IN_HOUR = 60;
    const int HOURS_IN_DAY = 24;

    const int SECS_IN_HOUR = 3600;
    const int SECS_IN_DAY = 86400;

    const int DINNER_START_H = 20;
    const int DINNER_START_M = 30;
    const int DINNER_END_H = 22;

    const int PARTY_START_H = 23;
    const int PARTY_END_H = 6;
}

namespace timeHelper 
{
    bool isValidHour(int h) 
    {
        return h >= timeConstants::MIN_VAL && h <= timeConstants::MAX_HOURS;
    }

    bool isValidMinOrSec(int val) 
    {
        return val >= timeConstants::MIN_VAL && val <= timeConstants::MAX_MINS_SECS;
    }

    int calculateTotalSeconds(int h, int m, int s) 
    {
        return h * timeConstants::SECS_IN_HOUR + m * timeConstants::SECS_IN_MIN + s;
    }
}

class Time 
{
private:
    int hours;
    int minutes;
    int seconds;

public:

    void setHours(int h) 
    {
        hours = timeHelper::isValidHour(h) ? h : 0;
    }

    void setMinutes(int m) 
    {
        minutes = timeHelper::isValidMinOrSec(m) ? m : 0;
    }

    void setSeconds(int s) 
    {
        seconds = timeHelper::isValidMinOrSec(s) ? s : 0;
    }

    Time() :hours(0), minutes(0), seconds(0) {}
    Time(int hours, int minutes, int seconds)
    {
        long total = timeHelper::calculateTotalSeconds(hours, minutes, seconds);
       
        setHours(total / timeConstants::SECS_IN_HOUR);
        setMinutes((total % timeConstants::SECS_IN_HOUR) / timeConstants::SECS_IN_MIN);
        setSeconds(total % timeConstants::SECS_IN_MIN);
    }

    Time timeToMidnight() const 
    {
        int current = timeHelper::calculateTotalSeconds(hours, minutes, seconds);
        if (current == 0)
            return Time(0, 0, 0);

        int remaining = timeConstants::SECS_IN_DAY - current;
        return Time(0, 0, remaining);
    }

    void addOneSecond()
    {
        int next = timeHelper::calculateTotalSeconds(hours, minutes, seconds) + 1;
        
        setHours(next / timeConstants::SECS_IN_HOUR);
        setMinutes((next % timeConstants::SECS_IN_HOUR) / timeConstants::SECS_IN_MIN);
        setSeconds(next % timeConstants::SECS_IN_MIN);
    }

    bool isDinnerTime() const
    {
        int currentInMins = hours * timeConstants::MINS_IN_HOUR + minutes;
        int startInMins = timeConstants::DINNER_START_H * timeConstants::MINS_IN_HOUR + timeConstants::DINNER_START_M;
        int endInMins = timeConstants::DINNER_END_H * timeConstants::MINS_IN_HOUR;

        return currentInMins >= startInMins && currentInMins <= endInMins;
    }

    bool isPartyTime() const 
    {
        return (hours >= timeConstants::PARTY_START_H || hours < timeConstants::PARTY_END_H);
    }

    Time getDifference(const Time& other) const 
    {
        int t1 = timeHelper::calculateTotalSeconds(hours, minutes, seconds);
        int t2 = timeHelper::calculateTotalSeconds(other.hours, other.minutes, other.seconds);
        return Time(0, 0, std::abs(t1 - t2));
    }

    int compare(const Time& other) const
    {
        int t1 = timeHelper::calculateTotalSeconds(hours, minutes, seconds);
        int t2 = timeHelper::calculateTotalSeconds(other.hours, other.minutes, other.seconds);

        if (t1 > t2) return 1;
        if (t1 < t2) return -1;
        return 0;
    }

    void print() const
    {
        

        if (hours < 10)
            std::cout << '0';
        std::cout << hours << ':';

        if (minutes < 10) 
            std::cout << '0';
        std::cout << minutes << ':';

        if (seconds < 10) 
            std::cout << '0';
        std::cout << seconds << std::endl;
    }

};

int main()
{
    Time t1{ 2,5,50 };
    Time t2{ 19,32,35 };

    t1.timeToMidnight().print();

    t1.compare(t2);
}

