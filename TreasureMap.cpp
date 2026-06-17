#include <iostream>
#include <cstring>
#include "treasureMap.h"
#include <fstream>

void TreasureMap::addTreasure(const Treasure& treasure)
{
	if (numOfTreasures >= Constants::MAX_TREASURES_ON_MAP)
	{
		std::cout << "The limit of the treasures is exceeded!";
		return;
	}
	treasures[numOfTreasures++] = treasure;
}

void TreasureMap::deleteByName(const char* name)
{
	size_t index = -1;
	for (size_t i = 0; i < numOfTreasures; i++)
	{
		if (strcmp(treasures[i].getName(), name) == 0)
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		std::cout << "This treasure was not found";
		return;
	}
	for (size_t i = index; i < numOfTreasures - 1; i++)
	{
		treasures[i] = treasures[i + 1];
	}
	numOfTreasures--;
}

Treasure TreasureMap::findByCoordinates(int x, int y) const
{
	for (size_t i = 0; i < numOfTreasures; i++)
	{
		if (treasures[i].getX() == x && treasures[i].getY() == y)
		{
			return treasures[i];
		}
	}
	return Treasure();
}

void TreasureMap::sortByValue()
{
	for (size_t i = 0; i < numOfTreasures - 1; i++)
	{
		for (size_t j = i; j < numOfTreasures; j++)
		{
			if (treasures[i].getValue() < treasures[j].getValue())
			{
				std::swap(treasures[i], treasures[j]);
			}
		}
	}
}

void TreasureMap::sortByDistanceFrom0()
{
	for (size_t i = 0; i < numOfTreasures - 1; i++)
	{
		for (size_t j = i; j < numOfTreasures; j++)
		{
			if (treasures[i].findDisgtanceFrom0() < treasures[j].findDisgtanceFrom0())
			{
				std::swap(treasures[i], treasures[j]);
			}
		}
	}
}

void TreasureMap::printAllTreasures()const
{
	for (int i = 0; i < numOfTreasures; i++)
	{
		std::cout << "Treasure" << i;
		treasures[i].printTreasure();
	}
}

Treasure TreasureMap::findMostValuable()const
{
	size_t indx = 0;
	Treasure temp = treasures[0];
	int tempValue = temp.getValue();
	for (size_t i = 1; i < numOfTreasures; i++)
	{
		if (treasures[i].getValue() > tempValue)
		{
			tempValue = treasures[i].getValue();
			indx = i;
		}
	}
	return treasures[indx];
}

bool TreasureMap::saveToFile(const char* FILE_NAME) const
{
	std::ofstream ofs(FILE_NAME);
	if (!ofs.is_open())
		return false;

	ofs << numOfTreasures << std::endl;

	for (size_t i = 0; i < numOfTreasures; i++)
	{
		ofs << treasures[i].getName() << " " << treasures[i].getX() << " " << treasures[i].getY() << " "" " << treasures[i].getValue() << std::endl;
	}
	ofs.close();
	return true;
}

bool TreasureMap::readFromFile(const char* FILE_NAME)
{
	std::ifstream ifs(FILE_NAME);
	if (!ifs.is_open())
		return false;

	size_t count;
	if (!(ifs >> count))
		return false;

	numOfTreasures = 0;
	for (size_t i = 0; i < count; i++)
	{
		char tempName[Constants::MAX_TREASURE_NAME_LEN+1];
		int tempX, tempY, tempVal;
		
		if(ifs>>tempName>>tempX>>tempY>>tempVal)
		{
			Treasure temp(tempName, tempX, tempY, tempVal);
			addTreasure(temp);
		}
	}
	ifs.close();
	return true;
}

int main()
{
	TreasureMap myMap;\

	Treasure t1("Gold_Coin", 10, 20, 100);
	Treasure t2("Silver_Ring", -5, 15, 50);
	Treasure t3("Magic_Sword", 0, 0, 500);

	myMap.addTreasure(t1);
	myMap.addTreasure(t2);
	myMap.addTreasure(t3);

	std::cout << "All treasures" << std::endl;
	myMap.printAllTreasures();
	std::cout << std::endl;
	std::cout << "Most valuable" << std::endl;
	Treasure best = myMap.findMostValuable();
	best.printTreasure();
	std::cout << std::endl;
	std::cout << "Sorted by value" << std::endl;
	myMap.sortByValue();
	myMap.printAllTreasures();
}
