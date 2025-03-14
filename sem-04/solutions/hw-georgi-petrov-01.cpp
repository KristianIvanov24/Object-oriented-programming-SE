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

int main()
{

}