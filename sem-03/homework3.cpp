#include <iostream>

namespace constants
{
    const unsigned MAX_HOURS = 23;
    const unsigned MAX_MINUTES = 59;
    const unsigned MAX_SECONDS = 59;
}

class Time
{
    unsigned hours;
    unsigned minutes;
    unsigned seconds;

    bool isValidHours(unsigned hours) const
    {
        return hours <= constants::MAX_HOURS;
    }

    bool isValidMinutes(unsigned minutes) const
    {
        return minutes <= constants::MAX_MINUTES;
    }

    bool isValidSeconds(unsigned seconds) const
    {
        return seconds <= constants::MAX_SECONDS;
    }

    unsigned toTotalSeconds() const
    {
        return (hours * 60 + minutes) * 60 + seconds;
    }

    Time totalSecondsToTime(unsigned totalSeconds) const
    {
        unsigned seconds = totalSeconds % 60;
        totalSeconds /= 60;
        unsigned minutes = totalSeconds % 60;
        unsigned hours = totalSeconds / 60;
        return Time(hours, minutes, seconds);
    }

public:

    Time() :hours(0), minutes(0), seconds(0)
    {

    }
    
    Time(unsigned hours, unsigned minutes, unsigned seconds)
    {
        setHours(hours);
        setMinutes(minutes);
        setSeconds(seconds);
    }

    unsigned getHours() const
    {
        return hours;
    }

    unsigned getMinutes() const
    {
        return minutes;
    }

    unsigned getSeconds() const
    {
        return seconds;
    }

    void setHours(unsigned hours)
    {
        if (isValidHours(hours))
            this->hours = hours;
        else
            this->hours = 0;
    }

    void setMinutes(unsigned minutes)
    {
        if (isValidMinutes(minutes))
            this->minutes = minutes;
        else
            this->minutes = 0;
    }

    void setSeconds(unsigned seconds)
    {
        if (isValidSeconds(seconds))
            this->seconds = seconds;
        else
            this->seconds = 0;
    }

    Time leftUntilMidnight() const
    {
        return Time(constants::MAX_HOURS - hours, constants::MAX_MINUTES+1 - minutes, constants::MAX_SECONDS+1 - seconds);
    }

    void addSecond()
    {
        if (seconds < constants::MAX_SECONDS)
            seconds++;
        else
        {
            seconds = 0;
            if (minutes < constants::MAX_MINUTES)
                minutes++;
            else
            {
                minutes = 0;
                if (hours < constants::MAX_HOURS)
                    hours++;
                else
                    hours = 0;
            }
        }
    }

    bool isDinner() const
    {
        if (hours < 19 || hours>=22)
            return false;
        if (hours == 20)
            if (minutes < 30)
                return false;
        return true;
    }

    bool isParty() const
    {
        if (hours < 6 || hours == 23)
            return true;
        return false;
    }

    Time difference(Time& toSubtract) const
    {
        unsigned firstTotalSeconds = this->toTotalSeconds();
        unsigned secondTotalSeconds = toSubtract.toTotalSeconds();
        unsigned difference = firstTotalSeconds > secondTotalSeconds ? firstTotalSeconds - secondTotalSeconds : secondTotalSeconds - firstTotalSeconds;
        return totalSecondsToTime(difference);
    }
    
    int compare(Time& secondTime) const
    {
        unsigned firstTotalSeconds = this->toTotalSeconds();
        unsigned secondTotalSeconds = secondTime.toTotalSeconds();
        return firstTotalSeconds - secondTotalSeconds;
    }

    void print() const
    {
        std::cout << hours << ':' << minutes << ':' << seconds << std::endl;
    }
};

void timeInsertionSort(Time arr[], size_t size)
{
    for (int i = 1;i < size;i++)
    {
        Time currEl = arr[i];
        int currIndex = i - 1;
        while (currIndex >= 0 && arr[currIndex].compare(currEl) > 0)
        {
            arr[currIndex + 1] = arr[currIndex];
            currIndex--;
        }
        arr[currIndex + 1] = currEl;
    }
}

int main()
{
    Time times[10];
    for (int i = 0;i < 10;i++)
    {
        unsigned hours;
        unsigned minutes;
        unsigned seconds;
        std::cin >> hours >> minutes >> seconds;
        times[i] = Time(hours, minutes, seconds);
    }
    std::cout << std::endl;
    timeInsertionSort(times, 10);
    for (int i = 0;i < 10;i++)
    {
        times[i].print();
    }
}
/*
20 39 09
14 35 37
08 15 24
07 09 22
23 52 56
03 50 35
15 17 41
12 20 01
18 37 35
20 21 51
*/

