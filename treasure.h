#pragma once
#include "constants.h"

class Treasure
{
	char name[Constants::MAX_TREASURE_NAME_LEN+1];
	int x;
	int y;
	int valueOfTreasure;

public:
	Treasure() : x(0), y(0), valueOfTreasure(0) { name[0] = '\0'; }
	Treasure(const char* name, int x, int y, int value);
	void setName(const char* name);
	void setCoordinates(int x, int y);
	void setValue(int value);
	const char* getName()const;
	int getX()const;
	int getY()const;
	int getValue()const;
	void printTreasure()const;
	double findDisgtanceFrom0()const;
};