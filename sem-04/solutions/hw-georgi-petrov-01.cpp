#include <iostream>

namespace constants
{
	unsigned TIME_MODIFIER = 60;

	unsigned MAX_SECONDS = 86'400;
}

using namespace constants;

class Time
{
	unsigned seconds;

	Time(unsigned seconds)
	{
		setSeconds(seconds);
	}

	void setSeconds(int seconds)
	{
		this->seconds = seconds % MAX_SECONDS;
	}

	// static
	unsigned minutesToSeconds(unsigned minutes) const
	{
		return minutes * TIME_MODIFIER;
	}

	// static
	unsigned hoursToSeconds(unsigned hours) const
	{
		return minutesToSeconds(hours * TIME_MODIFIER);
	}

	void increaseTimeBy(unsigned seconds)
	{
		setSeconds(this->seconds + seconds);
	}

	bool isBetween(const Time& start, const Time& end) const
	{
		if (start.isLaterThan(end))
		{
			return isLaterThan(start, true) || isEarlierThan(end, true);
		}

		return isLaterThan(start, true) && isEarlierThan(end, true);
	}

public:

	Time()
	{
		setSeconds(0);
	}

	Time(unsigned hours, unsigned minutes, unsigned seconds)
	{
		unsigned timeInSeconds = hoursToSeconds(hours) + minutesToSeconds(minutes) + seconds;
		setSeconds(timeInSeconds);
	}

	unsigned getSeconds() const
	{
		return this->seconds % TIME_MODIFIER;
	}

	unsigned getMinutes() const
	{
		return (this->seconds / TIME_MODIFIER) % TIME_MODIFIER;
	}

	unsigned getHours() const
	{
		return (this->seconds / TIME_MODIFIER) / TIME_MODIFIER;
	}

	Time getTimeUntilMidnight() const
	{
		return MAX_SECONDS - this->seconds;
	}

	void increaseTimeByOneSecond()
	{
		increaseTimeBy(1);
	}

	bool isDinnerTime() const
	{
		return isBetween({ 20, 30, 00 }, { 22, 00, 00 });
	}

	bool isPartyTime() const
	{
		return isBetween({ 23, 00, 00 }, { 06, 00, 00 });
	}

	Time timeLeftUntil(const Time& time) const
	{
		if (isLaterThan(time))
		{
			return getTimeUntilMidnight().seconds + time.seconds;
		}

		return time.seconds - this->seconds;
	}

	bool isLaterThan(const Time& time, bool inclusive = false) const
	{
		return this->seconds > time.seconds || (inclusive && isExactly(time));
	}

	bool isEarlierThan(const Time& time, bool inclusive = false) const
	{
		return !isLaterThan(time, !inclusive);
	}

	bool isExactly(const Time& time) const
	{
		return this->seconds == time.seconds;
	}

	void print() const
	{
		unsigned seconds = getSeconds();
		unsigned minutes = getMinutes();
		unsigned hours = getHours();

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


void selectionSortTimes(Time* times, size_t size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < size; j++)
		{
			if (times[j].isEarlierThan(times[minIndex]))
			{
				minIndex = j;
			}
		}
		std::swap(times[i], times[minIndex]);
	}
}

void printTimes(Time* times, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		times[i].print();
		std::cout << std::endl;
	}
}

int main()
{
	const size_t size = 10;
	Time times[size] = {
		Time(10, 30, 45), // 10:30:45
		Time(6, 15, 20),  // 06:15:20
		Time(14, 50, 55), // 14:50:55
		Time(22, 10, 5),  // 22:10:05
		Time(3, 45, 30),  // 03:45:30
		Time(18, 25, 40), // 18:25:40
		Time(8, 55, 12),  // 08:55:12
		Time(12, 5, 10),  // 12:05:10
		Time(19, 30, 55), // 19:30:55
		Time(9, 0, 0)     // 09:00:00
	};

	selectionSortTimes(times, size);
	printTimes(times, size);

	return 0;
}
