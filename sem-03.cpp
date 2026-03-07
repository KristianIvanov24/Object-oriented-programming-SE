#include <iostream>

namespace constants
{
	const int MIN_HOURS = 0;
	const int MAX_HOURS = 24;
	const int MIN_MINUTES = 0;
	const int MAX_MINUTES = 60;
	const int MIN_SECONDS = 0;
	const int MAX_SECONDS = 60;
	const int SECONDS_IN_HOUR = 3600;
	const int SECONDS_IN_MINUTE = 60;
	const int MINUTES_IN_HOUR = 60;
	const int SECONDS_IN_24_HOURS = 24 * SECONDS_IN_HOUR;
}

class Time
{
private:
	int hours;
	int minutes;
	int seconds;

	bool isValid(int hours, int minutes, int seconds)
	{
		return hours >= constants::MIN_HOURS && hours < constants::MAX_HOURS
			&& minutes >= constants::MIN_MINUTES && minutes < constants::MAX_SECONDS
			&& seconds >= constants::MIN_SECONDS && seconds < constants::MAX_SECONDS;
	}

	int toSeconds() const
	{
		return hours * constants::SECONDS_IN_HOUR + minutes * constants::SECONDS_IN_MINUTE + seconds;
	}

public:
	Time() :hours(0), minutes(0), seconds(0) {}

	Time(int h, int m, int s)
	{
		if (isValid(h, m, s))
		{
			hours = h;
			minutes = m;
			seconds = s;
		}
		else
		{
			hours = 0;
			minutes = 0;
			seconds = 0;
		}
	}

	Time timeToMidnight() const
	{
		if (hours == 0 && minutes == 0 && seconds == 0)
			return Time(0, 0, 0);

		int remainSec = constants::SECONDS_IN_24_HOURS - toSeconds();
		int h = remainSec / constants::SECONDS_IN_HOUR;
		int m = (remainSec / constants::SECONDS_IN_MINUTE) % constants::MINUTES_IN_HOUR;
		int s = remainSec % constants::MAX_SECONDS;
		return Time(h, m, s);
	}

	void increaseWithOneSecond()
	{
		seconds++;
		if (seconds == constants::MAX_SECONDS)
		{
			seconds = 0;
			minutes++;
			if (minutes == constants::MAX_MINUTES)
			{
				minutes = 0;
				hours++;
				if (hours == constants::MAX_HOURS)
					hours = 0;
			}
		}
	}

	bool isDinnerTime()const
	{
		int curr = toSeconds();
		int begining = 20 * constants::SECONDS_IN_HOUR + 30 * constants::SECONDS_IN_MINUTE;
		int end = 22 * constants::SECONDS_IN_HOUR;

		return curr >= begining && curr <= end;
	}

	bool isPartyTime()const
	{
		int curr = toSeconds();
		int begining = 23 * constants::SECONDS_IN_HOUR;
		int end = 6 * constants::SECONDS_IN_HOUR;

		return curr >= begining || curr <= end;
	}

	Time difference(const Time& other)const
	{
		int sec1 = toSeconds();
		int sec2 = other.toSeconds();
		int diff = (sec1 > sec2) ? (sec1 - sec2) : (sec2 - sec1);
		return Time(diff / constants::SECONDS_IN_HOUR, (diff / constants::SECONDS_IN_MINUTE) % constants::MINUTES_IN_HOUR, diff % constants::MAX_SECONDS);
	}

	int compare(const Time& other)const
	{
		int sec1 = toSeconds();
		int sec2 = other.toSeconds();
		if (sec1 < sec2)
			return -1;
		if (sec1 > sec2)
			return 1;

		return 0;
	}

	void print()const
	{
		if (hours < 10)
		{
			std::cout << "0";
		}
		std::cout << hours << ":";
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
};

void mySwap(Time& t1, Time& t2)
{
	Time temp = t1;
	t1 = t2;
	t2 = temp;
}

void sortTimes(Time arr[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j].compare(arr[minIndex]) == -1)
			{
				minIndex = j;
			}
		}
		mySwap(arr[i], arr[minIndex]);
	}
}

int main()
{
	Time times[10] = {
		Time(21, 15, 0),
		Time(23, 45, 30),
		Time(8,  30, 0),
		Time(),
		Time(12, 0, 0),
		Time(20, 45, 15),
		Time(4,  15, 0),
		Time(18, 59, 59),
		Time(22, 1, 0),
		Time(9, 10, 20)
	};
	std::cout << "Unsorted times:" << std::endl;
	for (int i = 0; i < 10; i++)
	{
		times[i].print();
		std::cout << "Party " << (times[i].isPartyTime() ? "Yes" : "No");
		std::cout << "Dinner " << (times[i].isDinnerTime() ? "Yes" : "No") << std::endl;
	}

	sortTimes(times, 10);
	std::cout << "Sorted times:" << std::endl;
	for (int i = 0; i < 10; i++)
	{
		times[i].print();
		std::cout << std::endl;
	}
	Time t1(23, 59, 59);
	std::cout << "The time is:" << std::endl;
	t1.print();
	std::cout << std::endl;
	std::cout << "After one second:" << std::endl;
	t1.increaseWithOneSecond();
	t1.print(); std::cout << std::endl;
	Time t2(10, 0, 0);
	Time t3(12, 30, 0);
	std::cout << "The difference between"; t2.print(); std::cout << " and "; t3.print(); std::cout << " is ";
	Time diff = t2.difference(t3);
	diff.print();
}