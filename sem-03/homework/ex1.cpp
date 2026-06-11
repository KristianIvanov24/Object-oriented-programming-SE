#include <iostream>

namespace constants
{
    const int MAX_HOURS = 24;
    const int MAX_MINUTES = 60;
    const int MAX_SECONDS = 60;
    const int MIN_TIME = 0;
    const int MIDNIGHT_SECONDS = MAX_HOURS * MAX_MINUTES * MAX_SECONDS;
}

class Time
{
    int hour;
    int minutes;
    int seconds;

    void normalise()
    {
        minutes += seconds / constants::MAX_SECONDS;
        seconds %= constants::MAX_SECONDS;

        hour += minutes / constants::MAX_MINUTES;
        minutes %= constants::MAX_MINUTES;

        hour %= constants::MAX_HOURS;
    }

    bool isValidSeconds(int seconds) const
    {
        if (seconds >= constants::MAX_SECONDS || seconds < constants::MIN_TIME)
        {
            std::cout << "Invalid seconds" << std::endl;
            return false;
        }
        return true;
    }

    bool isValidMinutes(int minutes) const
    {
        if (minutes >= constants::MAX_MINUTES || minutes < constants::MIN_TIME)
        {
            std::cout << "Invalid minutes" << std::endl;
            return false;
        }
        return true;
    }

    bool isValidHour(int hour) const
    {
        if (hour >= constants::MAX_HOURS || hour < constants::MIN_TIME)
        {
            std::cout << "Invalid hour" << std::endl;
            return false;
        }
        return true;
    }

    int toSeconds() const
    {
        return hour * constants::MAX_MINUTES * constants::MAX_SECONDS + minutes * constants::MAX_SECONDS + seconds;
    }

public:
    Time() : hour(0), minutes(0), seconds(0) {}
    Time(int hour, int minutes, int seconds)
    {
        setHour(hour);
        setMinutes(minutes);
        setSeconds(seconds);
    }
    Time(int s)
    {
        hour = s / (constants::MAX_MINUTES * constants::MAX_SECONDS);
        s %= constants::MAX_MINUTES * constants::MAX_SECONDS;
        minutes = s / constants::MAX_SECONDS;
        seconds = s % constants::MAX_SECONDS;
    }

    void setHour(int hour)
    {
        if (isValidHour(hour))
        {
            this->hour = hour;
        }
        else
        {
            this->hour = 0;
        }
    }

    void setMinutes(int minutes)
    {
        if (isValidMinutes(minutes))
        {
            this->minutes = minutes;
        }
        else
        {
            this->minutes = 0;
        }
    }

    void setSeconds(int seconds)
    {
        if (isValidSeconds(seconds))
        {
            this->seconds = seconds;
        }
        else
        {
            this->seconds = 0;
        }
    }

    Time timeUntilMidnight()
    {
        int difference = constants::MIDNIGHT_SECONDS - toSeconds();
        Time t = difference;
        return t;
    }

    void increment()
    {
        seconds += 1;
        normalise();
    }

    bool isDinnerTime() const
    {
        return compare({20, 30, 0}) >= 0 && compare({22, 0, 0}) <= 0;
    }

    bool isPartyTime() const
    {
        return compare({23, 0, 0}) >= 0 || compare({6, 0, 0}) <= 0;
    }

    Time difference(const Time &other) const
    {
        int difference = toSeconds() - other.toSeconds();
        if (difference < 0)
        {
            difference += constants::MAX_HOURS * constants::MAX_MINUTES * constants::MAX_SECONDS;
        }
        return difference;
    }

    void print() const
    {
        if (hour < 10)
        {
            std::cout << "0";
        }
        std::cout << hour << ":";
        if (minutes < 10)
        {
            std::cout << "0";
        }
        std::cout << minutes << ":";
        if (seconds < 10)
        {
            std::cout << "0";
        }
        std::cout << seconds;
    }

    int compare(const Time &other) const
    {
        return toSeconds() - other.toSeconds();
    }
};

void sort(Time *times, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (times[j].compare(times[j + 1]) > 0)
            {
                std::swap(times[j], times[j + 1]);
            }
        }
    }
}