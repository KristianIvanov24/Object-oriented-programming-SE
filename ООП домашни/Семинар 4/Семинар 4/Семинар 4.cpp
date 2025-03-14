#include <iostream>
#include <cstring>
#pragma warning (disable:4996)

namespace constants
{
    const unsigned MAX_HOURS = 23;
    const unsigned MAX_MINUTES = 59;
    const unsigned MAX_SECONDS = 59;

    const unsigned DINNER_TIME_START_HOUR = 20;
    const unsigned DINNER_TIME_START_MINUTES = 30;
    const unsigned DINNER_TIME_END_HOUR = 22;

    const unsigned PARTY_TIME_START_HOUR = 23;
    const unsigned PARTY_TIME_END_HOUR = 6;

    const unsigned ZERO_TIME_PART = 0;

    const size_t MAX_TIMES_IN_ARRAY = 10;

}

class Time
{
private:
    unsigned hours;
    unsigned minutes;
    unsigned seconds;

public:
    Time()
    {
        hours = 0;
        minutes = 0;
        seconds = 0;
    }

    Time(unsigned hours, unsigned minutes, unsigned seconds)
    {
        setHours(hours);
        setMinutes(minutes);
        setSeconds(seconds);
    }

    void setHours(unsigned hours)
    {
        if (hours > constants::MAX_HOURS)
            this->hours = 0;

        this->hours = hours;
    }

    unsigned getHours() const
    {
        return hours;
    }

    void setMinutes(unsigned minutes)
    {
        if (minutes > constants::MAX_MINUTES)
            this->minutes = 0;

        this->minutes = minutes;
    }

    unsigned getMinutes() const
    {
        return minutes;
    }

    void setSeconds(unsigned seconds)
    {
        if (seconds > constants::MAX_SECONDS)
            this->seconds = 0;

        this->seconds = seconds;
    }

    unsigned getSeconds() const
    {
        return seconds;
    }

    void addOneSecond()
    {
        seconds++;
        if (seconds > constants::MAX_SECONDS)
        {
            minutes++;
            seconds %= (constants::MAX_SECONDS + 1);
        }

        if (minutes > constants::MAX_MINUTES)
        {
            hours++;
            minutes %= (constants::MAX_MINUTES + 1);
        }

        hours %= (constants::MAX_HOURS + 1);
    }

    bool isDinnerTime() const
    {
        Time startDinnerTime(constants::DINNER_TIME_START_HOUR,
            constants::DINNER_TIME_START_MINUTES, constants::ZERO_TIME_PART);

        Time endDinnerTime(constants::DINNER_TIME_END_HOUR,
            constants::ZERO_TIME_PART, constants::ZERO_TIME_PART);

        return !isTimeEarlierThan(startDinnerTime) && isTimeEarlierThan(endDinnerTime);
    }

    bool isPartyTime() const
    {
        Time startPartyTime(constants::PARTY_TIME_START_HOUR,
            constants::ZERO_TIME_PART, constants::ZERO_TIME_PART);

        Time midnight(0, 0, 0);

        Time endPartyTime(constants::PARTY_TIME_END_HOUR,
            constants::ZERO_TIME_PART, constants::ZERO_TIME_PART);

        bool beforeMidnight = isTimeEarlierThan(midnight);

        return !isTimeEarlierThan(startPartyTime) && beforeMidnight ||
            !beforeMidnight && isTimeEarlierThan(endPartyTime);
    }

    Time timeDiff(const Time& timeToCompare) const
    {
        int resultSeconds = timeToCompare.seconds - this->seconds;
        int resultMinutes = timeToCompare.minutes - this->minutes;
        int resultHours = timeToCompare.hours - this->hours;

        if (resultSeconds < 0)
        {
            resultSeconds += (constants::MAX_SECONDS + 1);
            resultMinutes--;
        }

        if (resultMinutes < 0)
        {
            resultMinutes += (constants::MAX_MINUTES + 1);
            resultHours--;
        }

        if (resultHours < 0)
            resultHours += (constants::MAX_HOURS + 1);

        return Time(resultHours, resultMinutes, resultSeconds);
    }

    void printTimeToMidnight()
    {
        Time midnight(0, 0, 0);
        Time difference = timeDiff(midnight);
        
        difference.printTime();
    }

    bool isTimeEarlierThan(const Time& timeToCompare) const
    {
        if (this->hours != timeToCompare.hours)
            return this->hours < timeToCompare.hours;
        else
        {
            if (this->minutes != timeToCompare.minutes)
                return this->minutes < timeToCompare.minutes;
            else
                return this->seconds < timeToCompare.seconds;
        }
    }

    void printTime() const
    {
        if (hours < 10)
            std::cout << "0";

        std::cout << hours << ":";

        if (minutes < 10)
            std::cout << "0";

        std::cout << minutes << ":";

        if (seconds < 10)
            std::cout << "0";

        std::cout << seconds;

    }
};

void swapTimes(Time& firstTime, Time& secondTime)
{
    Time temp = firstTime;
    firstTime = secondTime;
    secondTime = temp;
}

void sortTimes(Time times[])
{
    for (size_t first = 0; first < constants::MAX_TIMES_IN_ARRAY - 1; first++)
    {
        size_t minIndex = first;

        for (size_t second = first; second < constants::MAX_TIMES_IN_ARRAY; second++)
        {
            if (times[second].isTimeEarlierThan(times[minIndex]))
            {
                minIndex = second;
            }
        }

        if (minIndex != first)
        {
            std::swap(times[first], times[minIndex]);
        }
    }
}

int main()
{
}