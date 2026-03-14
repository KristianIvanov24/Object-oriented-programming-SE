#pragma once
#include "Constants.h" 
#include <math.h>
class Treasure
{
private:
	char name[constants::MAX_TRESURE_NAME_LEN+1];
	int x;
	int y;
	int value;

public:
	Treasure() = default;
	Treasure(const char* name, int x, int y, int value);
	void setName(const char* name);
	void setCoordinates(int x, int y);
	void setValue(int value);
	const char* getName()const;
	int getX()const;
	int getY()const;
	int getValue()const;
	void print()const;
	double findDistanceFrom0()const;
};

