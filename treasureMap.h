#pragma once
#include "treasure.h"
#include "constants.h"

class TreasureMap
{
	Treasure treasures[Constants::MAX_TREASURES_ON_MAP];
	size_t numOfTreasures = 0;

public:
	void addTreasure(const Treasure& treasure);
	void deleteByName(const char* name);
	Treasure findByCoordinates(int x, int y)const;
	void sortByValue();
	void sortByDistanceFrom0();
	void printAllTreasures()const;
	Treasure findMostValuable()const;
	bool saveToFile(const char* FILE_NAME)const;
	bool readFromFile(const char* FILE_NAME);
};