// OOP_D3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

//Реализирайте клас Time, който ще се използва за работа с часове(13:05:45).Вашият клас трябва да има следния интерфейс :
//Подразбиращ се конcтруктор, който създава часа на 00 : 00 : 00.
//Конструктор, който приема три параметъра - час, минути и секунди.
//Член - функция, която връща оставащото време до полунощ.
//Член - функция, която увеличава часа с 1 секунда.
//Член - функция, която връща дали е време за вечеря.В рамките на задачата време за вечеря е между 20 : 30 и 22 : 00.
//Член - функция, която връща дали е време за парти.В рамките на задачата време за парти е между 23 : 00 и 06 : 00.
//Член - функция, която приема друг обект от тип Time и връща обект от тип Time, което е разликата между двете времена.
//Член - функция, която която приема друг обект от тип Time и сравнява двата обекта (по - къснен / по - ранен)
//Член - функция за принтиране на часа.
//Да се направи масив от 10 времена и да се сортира с някоя от изучаваните сортировки.

namespace CONSTANTS
{
	constexpr int HOURS_InOneDay = 24;
	constexpr int MAX_MINUTES = 60;
	constexpr int MAX_SECONDS = 60;
	constexpr int SIZE = 10;
}
class Time
{
	int hours;
	int minutes;
	int seconds;
	Time* times=new Time[CONSTANTS::SIZE];

  public:
	Time() :hours(0), minutes(0), seconds(0) {}
	Time(int hours, int minutes, int seconds) :hours(hours), minutes(minutes), seconds(seconds) {}

	void printTime() const
	{
		std::cout << (hours < 10 ? "0" : "") << hours << ":"
			<< (minutes < 10 ? "0" : "") << minutes << ":"
			<< (seconds < 10 ? "0" : "") << seconds;
	}

	Time timeUntilMidnight() const
	{
		int currentSeconds = hours * 60 * 60 + minutes * 60 + seconds;
		int midnightSeconds = CONSTANTS::HOURS_InOneDay * 3600;
		int remainingSeconds = midnightSeconds - currentSeconds;
		int remainingHours = remainingSeconds / 3600;
		int remainingMinutes = (remainingSeconds % 3600) / 60;
		remainingSeconds = remainingSeconds % 60;
		return Time(remainingHours, remainingMinutes, remainingSeconds);
	}

	void timeAfterOneSecond() 
	{
		if (seconds <= 58)
		{
			seconds++;
		}
		else 
		{
			seconds = 0;
			if (minutes < 59)
			{
				minutes++;
			}
			else
			{
				minutes = 0;
				if (hours < 23)
				{
					hours++;
				}
				hours = 0; //00:00:00;
			}
		}
	}

	bool isDinnerTime() const
	{
		if (hours > 20 && hours < 22 || hours == 20 && minutes > 30)
		{
				return true;
		}
		return false;
	}

	bool isPartyTime() const
	{
		if (hours == 23 || (hours >= 0 && hours < 6))
		{
			return true;
		}
		return false;
	}

	Time differenseInTime(Time& second) const
	{
		int totalSeconds = hours * 3600 + minutes * 60 + seconds;
		int totalSeconds2 = second.hours * 3600 + second.minutes * 60 + second.seconds;
		int difference = std::abs(totalSeconds - totalSeconds2);
		int diffH = difference / 3600;
		int diffM = (difference % 3600) / 60;
		int diffS = difference % 60;
		return Time(diffH, diffM, diffS);
	}

	int compareTime(Time& second) const
	{
		int totalSeconds = hours * 3600 + minutes * 60 + seconds;
		int totalSeconds2 = second.hours * 3600 + second.minutes * 60 + second.seconds;
		if (totalSeconds > totalSeconds2)
		{
			std::cout << "The earlier time is: ";
			second.printTime();
		}
		return  totalSeconds - totalSeconds2;
	}

	void selectionSort(Time* times)
	{
		for (int i = 0; i < CONSTANTS::SIZE; i++)
		{
			int minIndex = i;
			for (int j = i + 1; j < CONSTANTS::SIZE; j++)
			{
				if (times[j].compareTime(times[minIndex]) < 0)
				{
					minIndex = j;
				}
			}
			if (minIndex != i)
			{
				std::swap(times[i], times[minIndex]);
			}
		}
	}

	~Time()
	{
		delete [] times;
	}
};

int main()
{

}

