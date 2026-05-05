#include <iostream>

namespace constants {
	const size_t MAX_TIMES = 10;
	const int SECONDS_IN_DAY = 24 * 3600;
}

class Time {
private:

    int hours;
    int minutes;
	int seconds;

    void correctTime() {
        if(this->seconds == 60) {
            this->minutes += 1;
            this->seconds = 0;
        }
        if(this->minutes == 60) {
            this->hours += 1;
            this->minutes = 0;
        }
        if(this->hours == 24) {
            this->hours = 0;
        }
	}

public:

	Time() : hours(0), minutes(0), seconds(0) 
    {}

    Time(int hours, int minutes, int seconds) {
		this->setHours(hours);
		this->setMinutes(minutes);
		this->setSeconds(seconds);
    }

    void setHours(int hours) {
        if(hours >= 0 && hours < 24) {
            this->hours = hours;
		}
        else {
            this->hours = 0;
        }
	}

    void setMinutes(int minutes) {
        if(minutes >= 0 && minutes < 60) {
            this->minutes = minutes;
        }
        else {
            this->minutes = 0;
        }
    }
    void setSeconds(int seconds) {
        if(seconds >= 0 && seconds < 60) {
            this->seconds = seconds;
        }
        else {
            this->seconds = 0;
        }
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

    Time getTimeToMidnight() const {
		int totalSeconds = this->toSeconds();
        if(totalSeconds == 0) {
            return Time(0, 0, 0);
		}

        int remaining = constants::SECONDS_IN_DAY - totalSeconds;
        return { remaining / 3600, (remaining % 3600) / 60, remaining % 60 };
    }

    void updateTimeByOneSecond() {
        
        this->seconds += 1;
		this->correctTime();
    }

    bool isTimeForDinner() const {
		return this->hours == 21 || (this->hours == 20 && this->minutes >= 30);
    }

    bool isTimeForParty() const {
        return this->hours == 23 || this->hours <= 5;
    }

    int toSeconds() const {
        return this->hours * 3600 + this->minutes * 60 + this->seconds;
	}

    Time getDiffBetweenTimes(const Time& otherTime) const {
        int totalSeconds1 = this->toSeconds();
		int totalSeconds2 = otherTime.toSeconds();

		int diff = std::abs(totalSeconds1 - totalSeconds2);

		return { diff / 3600, (diff % 3600) / 60, diff % 60 };
    }

    bool isThisTimeEarlierThan(const Time& otherTime) const{
        return this->toSeconds() < otherTime.toSeconds();
    }

    void printTime() const {
        std::cout << (this->hours < 10 ? "0" : "") << this->hours << ":"
                  << (this->minutes < 10 ? "0" : "") << this->minutes << ":"
			      << (this->seconds < 10 ? "0" : "") << this->seconds << std::endl;
    }
};

void swapTimes(Time& time1, Time& time2) {
	Time temp = time1;
	time1 = time2;
	time2 = temp;
}

void sortTimes(Time* times, size_t size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (times[j + 1].isThisTimeEarlierThan(times[j])) {
				swapTimes(times[j], times[j + 1]);
            }
        }
	}
}

void printTimes(const Time* times, size_t size) {
    for (int i = 0; i < size; ++i) {
        times[i].printTime();
    }
}

int main()
{
    Time times[constants::MAX_TIMES] = {
        Time(14, 20, 15),   
        Time(02, 15, 00),  
        Time(21, 45, 10),   
        Time(07, 05, 59),   
        Time(23, 59, 00),   
        Time(12, 00, 00),   
        Time(20, 35, 00),  
        Time(05, 50, 45),  
        Time(18, 10, 20), 
        Time(10, 30, 00)
    };


	sortTimes(times, constants::MAX_TIMES);
	printTimes(times, constants::MAX_TIMES);

    return 0;
}