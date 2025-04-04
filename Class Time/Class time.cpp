#include <iostream>

namespace GLOBAL_CONSTANTS
{
	const int DEFAULT_TIME = 0;
	const int HOUR_MULTIPLIER = 3600;
	const int MIN_MULTIPLIER = 60;
	const int MAX_POSSIBLE_SECONDS = 24 * 3600;
	const int MAX_MINUTES_AND_SECONDS = 60;
	const int MAX_HOURS_IN_A_DAY = 24;
	const int PARTY_START = 23;
	const int PARTY_END = 6;
	const int MAX_NUMBER_OF_TIMES = 10;
	const int START_OF_DINNER = 20 * 3600 + 30 * 60;
	const int END_OF_DINNER = 22 * 3600;
}

class Time
{
private:
	int hours;
	int minutes;
	int seconds;
	int timeInSeconds;

	int hoursToSeconds(int hours) const
	{
		return hours * GLOBAL_CONSTANTS::HOUR_MULTIPLIER;
	}

	int minutesToSeconds(int minutes) const
	{
		return minutes * GLOBAL_CONSTANTS::MIN_MULTIPLIER;
	}

	int getAllSeconds() const
	{
		return hoursToSeconds(this->hours) + minutesToSeconds(this->minutes) + this->seconds;
	}

	//getting the total amount of seconds in our time^

	int secToHours(int seconds) const
	{
		return seconds / GLOBAL_CONSTANTS::HOUR_MULTIPLIER;
	}

	int secToMinutes(int seconds) const
	{
		return (seconds % GLOBAL_CONSTANTS::HOUR_MULTIPLIER) / GLOBAL_CONSTANTS::MIN_MULTIPLIER;
	}

	int getSecRem(int seconds) const
	{
		return seconds % GLOBAL_CONSTANTS::MIN_MULTIPLIER;
	}

	//converting all seconds int hours,minutes,seconds format ^

	int getRemainingSeconds() const
	{
		return GLOBAL_CONSTANTS::MAX_POSSIBLE_SECONDS - this->timeInSeconds;
	}

	//getting remaining seconds ^

	void addOneHour()
	{
		this->hours++;
		if (this->hours == GLOBAL_CONSTANTS::MAX_HOURS_IN_A_DAY)
			this->hours %= GLOBAL_CONSTANTS::MAX_HOURS_IN_A_DAY;
	}

	void addOneMinute()
	{
		this->minutes++;
		if (this->minutes == GLOBAL_CONSTANTS::MAX_MINUTES_AND_SECONDS)
		{
			this->minutes %= GLOBAL_CONSTANTS::MAX_MINUTES_AND_SECONDS;
			addOneHour();
		}
	}

	void printHours() const
	{
		if (this->hours < 10) std::cout << "0";
		std::cout << this->hours << ":";
	}

	void printMinutes() const
	{
		if (this->minutes < 10) std::cout << "0";
		std::cout << this->minutes << ":";
	}

	void printSeconds()const
	{
		if (this->seconds < 10) std::cout << "0";
		std::cout << this->seconds;
	}
	//print ^
	bool validateHours(int hours) const
	{
		if (hours < 0 || hours > 23) return false;
		return true;
	}

	bool validateMinutes(int minutes) const
	{
		if (minutes < 0 || minutes > 59) return false;
		return true;
	}

	bool validateSeconds(int seconds) const
	{
		if (seconds < 0 || seconds > 59) return false;
		return true;
	}

	bool validate(int hours, int minutes, int sec) const
	{
		return validateHours(hours) && validateMinutes(minutes) && validateSeconds(sec);
	}

	void bigSetter(int hours, int minutes, int seconds)
	{
		setHours(hours);
		setMinutes(minutes);
		setSeconds(seconds);
		this->timeInSeconds = getAllSeconds();
	}

public:
	Time() : hours(GLOBAL_CONSTANTS::DEFAULT_TIME),
		minutes(GLOBAL_CONSTANTS::DEFAULT_TIME),
		seconds(GLOBAL_CONSTANTS::DEFAULT_TIME),
		timeInSeconds(GLOBAL_CONSTANTS::DEFAULT_TIME) {};

	Time(int hours, int minutes, int seconds)
	{
		if (!validate(hours, minutes, seconds))
		{
			bigSetter(GLOBAL_CONSTANTS::DEFAULT_TIME,
				GLOBAL_CONSTANTS::DEFAULT_TIME,
				GLOBAL_CONSTANTS::DEFAULT_TIME);
			std::cout << "Invalid data";
		}
		else
		{
			bigSetter(hours, minutes, seconds);
		}
	}

	void setHours(int hours)
	{
		this->hours = hours;
		this->timeInSeconds = getAllSeconds();
	}

	void setMinutes(int minutes)
	{
		this->minutes = minutes;
		this->timeInSeconds = getAllSeconds();
	}

	void setSeconds(int seconds)
	{
		this->seconds = seconds;
		this->timeInSeconds = getAllSeconds();
	}
	//setters ^
	int getHours() const
	{
		return this->hours;
	}

	int getMinutes() const
	{
		return this->minutes;
	}

	int getSeconds() const
	{
		return this->seconds;
	}
	//getters ^
	const Time getRemainingTime() const
	{
		int remainingSeconds = getRemainingSeconds();
		int remainingHours = secToHours(remainingSeconds);
		int remainingMinutes = secToMinutes(remainingSeconds);
		int seconds = getSecRem(remainingSeconds); //remaining seconds % 60

		return { remainingHours ,remainingMinutes, seconds };
	}

	void addOneSecond()
	{
		this->seconds++;
		this->timeInSeconds++;

		if (this->seconds == GLOBAL_CONSTANTS::MAX_MINUTES_AND_SECONDS)
		{
			this->seconds %= GLOBAL_CONSTANTS::MAX_MINUTES_AND_SECONDS;
			addOneMinute();
		}
	}

	bool isItDinnerTime() const
	{
		return timeInSeconds >= GLOBAL_CONSTANTS::START_OF_DINNER &&
			timeInSeconds < GLOBAL_CONSTANTS::END_OF_DINNER;
	}

	bool isItPartyTime() const
	{
		return (this->hours >= GLOBAL_CONSTANTS::PARTY_START
			|| this->hours < GLOBAL_CONSTANTS::PARTY_END);
	}

	const Time getDifferenceOfTimes(const Time& other) const
	{
		int diffInSeconds = this->timeInSeconds - other.timeInSeconds;
		diffInSeconds = diffInSeconds < 0 ? -diffInSeconds : diffInSeconds;
		//Няма да използвам abs! никога!!!

		int newSeconds = getSecRem(diffInSeconds);
		int newMinutes = secToMinutes(diffInSeconds);
		int newHours = secToHours(diffInSeconds);

		return { newHours,newMinutes,newSeconds };
	}

	bool compareTimes(const Time& other) const
	{
		return this->timeInSeconds >= other.timeInSeconds;
	}

	void printTime() const
	{
		printHours();
		printMinutes();
		printSeconds();
		std::cout << std::endl;
	}
};

struct Times
{
	Time times[GLOBAL_CONSTANTS::MAX_NUMBER_OF_TIMES];
	int currentTimes = 0;

private:
	void swapTimes(Time& t1, Time& t2)
	{
		Time temp = t1;
		t1 = t2;
		t2 = temp;
	}

public:
	void sort()
	{
		for (int i = 0; i < currentTimes - 1; ++i)
		{
			for (int j = 0; j < currentTimes - i - 1; ++j)
			{
				if (times[j].compareTimes(times[j + 1]))
					swapTimes(times[j], times[j + 1]);
			}
		}
	}
	
	void readTimes()
	{
		std::cout << "Enter how many times do you want: ";
		std::cin >> currentTimes;
		if (currentTimes < 0 || currentTimes > GLOBAL_CONSTANTS::MAX_NUMBER_OF_TIMES)
		{
			std::cout << "The number must be between 0 and 10";
			return;
		}

		std::cout << std::endl;
		for (int i = 0; i < currentTimes; ++i)
		{
			std::cout << "Enter hours: ";
			int hours = 0;
			std::cin >> hours;
			std::cout << "Enter minutes: ";
			int minutes = 0;
			std::cin >> minutes;
			std::cout << "Enter seconds: ";
			int seconds = 0;
			std::cin >> seconds;
			std::cout << std::endl;

			times[i] = Time(hours, minutes, seconds);
		}
	}
	
	void printTimes() const
	{
		for (int i = 0; i < currentTimes; ++i)
		{
			std::cout << "Time " << i + 1 << " is: ";
			times[i].printTime();
		}
	}
};

int main()
{

	return 0;
}
