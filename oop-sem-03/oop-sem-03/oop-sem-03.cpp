#include <iostream>

namespace constants
{
    const size_t SYMBOLS_IN_TIME = 9;
    const char* TIME_0 = "00:00:00";
    const char DELIMER_FOR_TIME = ':';
    const size_t SECONDS_IN_MINUTE = 60;
    const size_t SECONDS_IN_HOUR = 3600;
    const int SECONDS_IN_DAY = 86400;
    const size_t MINUTES_IN_HOUR = 60;
    const size_t HOURS_IN_A_DAY = 24;
}

namespace helpFunctions
{
    char unsignedToChar(int sym)
    {
        return sym + '0';
    }

    void setTimeToChar(char* time, int sec, int min, int hours)
    {
        time[0] = helpFunctions::unsignedToChar(hours / 10);
        time[1] = helpFunctions::unsignedToChar(hours % 10);
        time[2] = constants::DELIMER_FOR_TIME;
        time[3] = helpFunctions::unsignedToChar(min / 10);
        time[4] = helpFunctions::unsignedToChar(min % 10);
        time[5] = constants::DELIMER_FOR_TIME;
        time[6] = helpFunctions::unsignedToChar(sec / 10);
        time[7] = helpFunctions::unsignedToChar(sec % 10);
        time[8] = '\0';
    }

    int calculateTotalSeconds(int s, int m, int h)
    {   
        return s + m * constants::SECONDS_IN_MINUTE + h * constants::SECONDS_IN_HOUR;
    }

    int myStdAbs(int diff)
    {
        if (diff < 0)return diff*-1;
        return diff;
    }
}

class Time
{
private:
    char time[constants::SYMBOLS_IN_TIME];
    int seconds;
    int minutes;
    int hours;

    void setTime(int sec, int min, int hours)
    {
        helpFunctions::setTimeToChar(this->time, sec, min, hours);
    }
public:
    Time()
    {
        strcpy_s(this->time, constants::TIME_0);
    }

    Time(int sec, int min, int hours) :seconds(sec), minutes(min), hours(hours)
    {
        setTime(sec, min, hours);
    }

    Time timeLeftToMidNight() const
    {
        int currentTotal = helpFunctions::calculateTotalSeconds(seconds, minutes, hours);
        int left = constants::SECONDS_IN_DAY - currentTotal;

        if (left == constants::SECONDS_IN_DAY) left = 0;

        int h = left / constants::SECONDS_IN_HOUR;
        int m = (left % constants::SECONDS_IN_HOUR) / constants::SECONDS_IN_MINUTE;
        int s = left % constants::SECONDS_IN_MINUTE;

        return Time(s, m, h);
    }

    void addOneSecond()
    {
        if (this->seconds == constants::SECONDS_IN_MINUTE - 1)
        {
            this->seconds = 0;
            if (this->minutes == constants::MINUTES_IN_HOUR - 1)
            {
                this->minutes = 0;
                if (this->hours == constants::HOURS_IN_A_DAY - 1)
                {
                    this->hours = 0;
                }
                else this->hours += 1;
            }
            else this->minutes += 1;
        }
        else this->seconds += 1;
        this->setTime(this->seconds, this->minutes, this->hours);
    }

    bool isItTimeForDinner() const
    {
        if (this->hours < 20 || this->hours>22)
            return false;
        else if (this->hours == 20 && this->minutes < 30)
            return false;
        else if (this->hours == 22 && this->minutes != 0 && this->seconds != 0)
            return false;
        return true;
    }

    bool isItTimeForParty() const
    {
        if (this->hours == 6 && this->minutes == 0 && this->seconds == 0)
            return true;
        return (hours >= 23 || hours < 6);
    }

    Time differenceBetweenTwoTimes(const Time& other)const
    {
        Time toReturn;
        int diff = helpFunctions::myStdAbs(helpFunctions::calculateTotalSeconds(this->seconds, this->minutes, this->hours) - helpFunctions::calculateTotalSeconds(other.seconds, other.minutes, other.hours));
        toReturn.hours = diff / constants::SECONDS_IN_HOUR;
        diff=diff% constants::SECONDS_IN_HOUR;
        toReturn.minutes = diff / constants::SECONDS_IN_MINUTE;
        toReturn.seconds = diff % constants::SECONDS_IN_MINUTE;
        helpFunctions::setTimeToChar(toReturn.time, toReturn.seconds, toReturn.minutes, toReturn.hours);
        return toReturn;

    }

    bool isThisTimeLaterThanOther(const Time& other)const
    {
        return helpFunctions::calculateTotalSeconds(this->seconds, this->minutes, this->hours) >
            helpFunctions::calculateTotalSeconds(other.seconds, other.minutes, other.hours);
    }

    void printTime()const
    {
        std::cout << this->time;
    }
};

int main()
{
    Time t1(0, 45, 20);
    std::cout << "Time: "; t1.printTime();

    std::cout << "Is dinner time? " << (t1.isItTimeForDinner() ? "Yes" : "No") << "\n";

    Time toMidnight = t1.timeLeftToMidNight();
    std::cout << "Time to midnight: "; toMidnight.printTime();

    return 0;
}