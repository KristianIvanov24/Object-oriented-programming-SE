#pragma once
#include "Treasure.h"

class TreasureMap
{
	Treasure treasures[constants::MAX_TREASURES];
	size_t size;

	void insertionSort(bool(*compare)(const Treasure& treasure1,const Treasure& treasure2));

public:
	TreasureMap();

	void addTreasure(const char* name, int x, int y, int value);
	void removeTreasure(char* name);
	Treasure findByCoordinates(int x, int y) const;
	void sortByValue();
	void sortByDistance();
	void print() const;
	Treasure getMostValuable() const;

	void save(const char* file);
	void load(const char* file);
};