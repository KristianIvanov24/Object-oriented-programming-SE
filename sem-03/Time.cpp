#include <iostream>
#pragma warning (disable: 4996)

namespace constants
{
	const int COMPONENT_STR_SPACE = 3;
	const int SECONDS_IN_MINUTE = 60;
	const int MINUTES_IN_HOUR = 60;
	const int HOURS_IN_DAY = 24;
	const int MAX_SECONDS = 59;
	const int MAX_MINUTES = 59;
	const int MAX_HOURS = 23;
	const int ONE_DIGIT = 1;
	const int TWO_DIGITS = 10;
	const int DECIMAL_BASE = 10;
	const int SECONDS_IN_DAY = HOURS_IN_DAY * MINUTES_IN_HOUR * SECONDS_IN_MINUTE;
	const int SECONDS_IN_HOUR = MINUTES_IN_HOUR * SECONDS_IN_MINUTE;
	const char TIME_BEGINNING[] = "00";
	const char TIME_DELIMITER = ':';
}

namespace utils
{
	bool containsOnlyDigits(const char* str)
	{
		for (size_t i = 0; str[i] != '\0'; ++i)
		{
			if (!(str[i] >= '0' && str[i] <= '9'))
			{
				return false;
			}
		}
		return true;
	}

	char intToChar(int digit)
	{
		return digit + '0';
	}
}

class Time
{
	char hours[constants::COMPONENT_STR_SPACE];
	char minutes[constants::COMPONENT_STR_SPACE];
	char seconds[constants::COMPONENT_STR_SPACE];

	bool isValidTimeComponent(const char* component, int maxValue) const
	{
		if (!utils::containsOnlyDigits(component) || strlen(component) > constants::COMPONENT_STR_SPACE - 1)
		{
			return false;
		}

		int value = atoi(component);
		return value >= 0 && value <= maxValue;
	}

	void setHours(const char* hours)
	{
		if (!isValidTimeComponent(hours, constants::MAX_HOURS))
		{
			strcpy(this->hours, constants::TIME_BEGINNING);
			return;
		}

		if (strlen(hours) == constants::ONE_DIGIT)
		{
			char formattedHours[constants::COMPONENT_STR_SPACE] {};
			formattedHours[0] = '0';
			formattedHours[1] = hours[0];
			formattedHours[2] = '\0';
			strcpy(this->hours, formattedHours);
			return;
		}

		strcpy(this->hours, hours);
	}

	void setMinutes(const char* minutes)
	{
		if (!isValidTimeComponent(minutes, constants::MAX_MINUTES))
		{
			strcpy(this->minutes, constants::TIME_BEGINNING);
			return;
		}
		
		if (strlen(minutes) == constants::ONE_DIGIT)
		{
			char formattedMinutes[constants::COMPONENT_STR_SPACE] {};
			formattedMinutes[0] = '0';
			formattedMinutes[1] = minutes[0];
			formattedMinutes[2] = '\0';
			strcpy(this->minutes, formattedMinutes);
			return;
		}

		strcpy(this->minutes, minutes);
	}

	void setSeconds(const char* seconds)
	{
		if (!isValidTimeComponent(seconds, constants::MAX_SECONDS))
		{
			strcpy(this->seconds, constants::TIME_BEGINNING);
			return;
		}

		if (strlen(seconds) == constants::ONE_DIGIT)
		{
			char formattedSeconds[constants::COMPONENT_STR_SPACE] {};
			formattedSeconds[0] = '0';
			formattedSeconds[1] = seconds[0];
			formattedSeconds[2] = '\0';
			strcpy(this->seconds, formattedSeconds);
			return;
		}

		strcpy(this->seconds, seconds);
	}

	void formatTimeComponent(char* const formattedComponent, int component) const
	{
		if (component < constants::TWO_DIGITS)
		{
			formattedComponent[0] = '0';
			formattedComponent[1] = utils::intToChar(component);
			formattedComponent[2] = '\0';
		}
		else
		{
			itoa(component, formattedComponent, constants::DECIMAL_BASE);
		}
	}

public:
	
	Time() : hours("00"), minutes("00"), seconds("00") {}
	
	Time(const char* hours, const char* minutes, const char* seconds)
	{
		setHours(hours);
		setMinutes(minutes);
		setSeconds(seconds);
	}

	const char* getHours() const
	{
		return hours;
	}

	const char* getMinutes() const
	{
		return minutes;
	}
	
	const char* getSeconds() const
	{
		return seconds;
	}
	
	void restToMidnight() const
	{
		int secInt = atoi(seconds);
		int minInt = atoi(minutes);
		int hrInt = atoi(hours);
		int totalSeconds = hrInt * constants::MINUTES_IN_HOUR * constants::SECONDS_IN_MINUTE + minInt * constants::SECONDS_IN_MINUTE + secInt;
		int secondsToMidnight = constants::SECONDS_IN_DAY - totalSeconds;
		int remainingHours = secondsToMidnight / constants::SECONDS_IN_HOUR;
		int remainingMinutes = (secondsToMidnight % constants::SECONDS_IN_HOUR) / constants::SECONDS_IN_MINUTE;
		int remainingSeconds = secondsToMidnight % constants::SECONDS_IN_MINUTE;

		char formattedHours[constants::COMPONENT_STR_SPACE];
		formatTimeComponent(formattedHours, remainingHours);

		char formattedMinutes[constants::COMPONENT_STR_SPACE];
		formatTimeComponent(formattedMinutes, remainingMinutes);

		char formattedSeconds[constants::COMPONENT_STR_SPACE];
		formatTimeComponent(formattedSeconds, remainingSeconds);

		std::cout << "Time remaining to midnight: " << formattedHours << constants::TIME_DELIMITER << formattedMinutes << constants::TIME_DELIMITER << formattedSeconds << std::endl;
	}

	void addOneSecond()
	{
		if (seconds[1] == 9)
		{
			seconds[1] = 0;

			if (seconds[0] == 5)
			{
				seconds[0] = 0;

				if (minutes[1] == 9)
				{
					minutes[1] = 0;

					if (minutes[0] == 5)
					{
						minutes[0] = 0;

						if (hours[1] == 3)
						{
							hours[0] = 0;

							if (hours[0] == 2)
							{
								hours[0] = 0;
								return;
							}
							else
							{
								hours[0]++;
								return;
							}
						}
						else
						{
							hours[1]++;
							return;
						}
					}
					else
					{
						minutes[0]++;
						return;
					}
				}
				else
				{
					minutes[1]++;
					return;
				}
			}
			else
			{
				seconds[0]++;
				return;
			}
		}
		else
		{
			seconds[1]++;
			return;
		}
	}

	bool isDinnerTime() const
	{
		int hoursInt = atoi(hours);
		int minutesInt = atoi(minutes);
		int secondsInt = atoi(seconds);
		
		return hoursInt == 20 && minutesInt >= 30 || hoursInt == 21 || hoursInt == 22 && minutesInt == 0 && secondsInt == 0;
	}

	bool isPartyTime() const
	{
		int hoursInt = atoi(hours);
		int minutesInt = atoi(minutes);
		int secondsInt = atoi(seconds);

		return hoursInt >= 23 && hoursInt < 6 || hoursInt == 6 && minutesInt == 0 && secondsInt == 0;
	}

	Time differenceBetweenTimes(const Time &other) const
	{
		int thisTotalSeconds = atoi(hours) * constants::SECONDS_IN_HOUR + atoi(minutes) * constants::SECONDS_IN_MINUTE + atoi(seconds);
		int otherTotalSeconds = atoi(other.hours) * constants::SECONDS_IN_HOUR + atoi(other.minutes) * constants::SECONDS_IN_MINUTE + atoi(other.seconds);
		int diffSeconds = abs(thisTotalSeconds - otherTotalSeconds);

		int diffHours = diffSeconds / constants::SECONDS_IN_HOUR;
		int diffMinutes = (diffSeconds % constants::SECONDS_IN_HOUR) / constants::SECONDS_IN_MINUTE;
		int diffRemainingSeconds = diffSeconds % constants::SECONDS_IN_MINUTE;

		char formattedHours[constants::COMPONENT_STR_SPACE] {};
		formatTimeComponent(formattedHours, diffHours);
		
		char formattedMinutes[constants::COMPONENT_STR_SPACE] {};
		formatTimeComponent(formattedMinutes, diffMinutes);

		char formattedSeconds[constants::COMPONENT_STR_SPACE] {};
		formatTimeComponent(formattedSeconds, diffRemainingSeconds);
		
		Time diffTime(formattedHours, formattedMinutes, formattedSeconds);
		std::cout << "After init.: " << diffTime.hours << constants::TIME_DELIMITER << diffTime.minutes << constants::TIME_DELIMITER << diffTime.seconds << std::endl;
		return diffTime;
	}

	int compareTimes(const Time &other) const
	{
		int thisTotalSeconds = atoi(hours) * constants::SECONDS_IN_HOUR + atoi(minutes) * constants::SECONDS_IN_MINUTE + atoi(seconds);
		int otherTotalSeconds = atoi(other.hours) * constants::SECONDS_IN_HOUR + atoi(other.minutes) * constants::SECONDS_IN_MINUTE + atoi(other.seconds);

		if (thisTotalSeconds > otherTotalSeconds) return 1;
		if (thisTotalSeconds == otherTotalSeconds) return 0;
		else return -1;
	}

	void printTime() const
	{
		std::cout << hours << constants::TIME_DELIMITER << minutes << constants::TIME_DELIMITER << seconds << std::endl;
	}
};

void sortTimes(Time* const times, size_t size)
{
	for (size_t i = 0; i < size - 1; ++i)
	{
		for (size_t j = 0; j < size - i - 1; ++j)
		{			
			if (times[j].compareTimes(times[j + 1]) == 1)
			{
				Time temp = times[j];
				times[j] = times[j + 1];
				times[j + 1] = temp;
			}
		}
	}
}

int main()
{
	Time time1("5", "21", "15");
	Time time2("3", "12", "8");
	time1.printTime();
	time2.printTime();
	Time diff = time1.differenceBetweenTimes(time2);
	std::cout << "Difference between times: ";
	diff.printTime();

	Time times[] = {
		Time("20", "30", "00"),
		Time("21", "20", "00"),
		Time("22", "00", "43"),
		Time("23", "00", "07"),
		Time("00", "04", "00"),
		Time("01", "00", "00"),
		Time("02", "00", "00"),
		Time("03", "00", "00"),
		Time("04", "00", "00"),
		Time("05", "59", "59")
	};

	size_t timesSize = sizeof(times) / sizeof(Time);
	sortTimes(times, timesSize);

	for (size_t i = 0; i < timesSize; ++i)
	{
		times[i].printTime();
	}
}
