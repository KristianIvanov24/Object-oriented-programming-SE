#pragma once
#include "Treasure.h"
class TreasureMap
{
private:
	Treasure treasures[constants::MAX_TRESURES_IN_MAP];
	size_t amountOfTreasures=0;

	
public:
	bool addTreasure(const Treasure& tresure);
	void removeTresureByName(const char* name);
	Treasure findTresure(int x, int y)const;
	void sortByValue();
	void sortByDistance();
	void print()const;
	Treasure getMostValuable()const;
	bool saveToFile(const char* FILE_NAME)const;
	bool readFromFile(const char* FILE_NAME);
};

