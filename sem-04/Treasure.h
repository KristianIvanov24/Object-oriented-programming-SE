#pragma once
#include "Constants.h"

class Treasure
{
	char name[constants::MAX_NAME];
	int x;
	int y;
	int value;

	bool isValidName(const char* name);
	bool isValidValue(int value) ;
	
public:

	Treasure();
	Treasure(const char* name, int x, int y, int value);
	~Treasure();

	const char* getName() const;
	int getX() const;
	int getY() const;
	int getValue() const;
	double getDistance() const;

	void setName(const char* name);
	void setX(int x);
	void setY(int y);
	void setValue(int value);
};
