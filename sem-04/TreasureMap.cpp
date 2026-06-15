#include "TreasureMap.h"
#include <fstream>
#include <iostream>

TreasureMap::TreasureMap(): size(0)
{
}

void TreasureMap::addTreasure(const char* name, int x, int y, int value)
{
	if (size < constants::MAX_TREASURES)
	{
		treasures[size].setName(name);
		treasures[size].setX(x);
		treasures[size].setY(y);
		treasures[size].setValue(value);
		size++;
	}
}

void TreasureMap::removeTreasure(char* name)
{
	if (size > 0)
		size--;
}

Treasure TreasureMap::findByCoordinates(int x, int y) const
{
	for (int i = 0;i < size;i++)
	{
		if (treasures[i].getX() == x && treasures[i].getY() == y)
			return treasures[i];
	}
	return Treasure();
}

void TreasureMap::insertionSort(bool(*compare)(const Treasure& treasure1, const Treasure& treasure2))
{
	for (int i = 1; i < size; i++)
	{
		Treasure currEl = treasures[i];
		int currIndex = i - 1;
		while (currIndex >= 0 && compare(treasures[currIndex],currEl))
		{
			treasures[currIndex + 1] = treasures[currIndex];
			currIndex--;
		}
		treasures[currIndex + 1] = currEl;
	}
}

void TreasureMap::sortByValue()
{
	insertionSort([](const Treasure& treasure1, const Treasure& treasure2) -> bool {return treasure1.getValue() > treasure2.getValue();});
}

void TreasureMap::sortByDistance()
{
	insertionSort([](const Treasure& treasure1, const Treasure& treasure2) -> bool {return treasure1.getDistance() > treasure2.getDistance();});
}

void TreasureMap::print() const
{
	for (int i = 0;i < size;i++)
	{
		std::cout << treasures[i].getName() << " (" << treasures[i].getX() << ',' << treasures[i].getY() << ") value:" << treasures[i].getValue() << std::endl;
	}
}

Treasure TreasureMap::getMostValuable() const
{
	Treasure max = treasures[0];
	for (int i = 1;i < size;i++)
	{
		if (max.getValue() < treasures[i].getValue())
			max = treasures[i];
	}
	return max;
}

void TreasureMap::save(const char* filename)
{
	std::ofstream file(filename);
	if (!file.is_open())
		return;
	for (int i = 0;i < size;i++)
	{
		file << treasures[i].getName() << std::endl;
		file << treasures[i].getX() << ' ' << treasures[i].getY() << ' ' << treasures[i].getValue() << std::endl;
	}
	file.close();
}

void TreasureMap::load(const char* filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
		return;
	char name[constants::MAX_NAME];
	int x,y,value;
	while (!file.eof())
	{
		file.getline(name, constants::MAX_NAME);
		file>>x>>y>>value;
		this->addTreasure(name, x, y, value);
	}
	file.close();
}
