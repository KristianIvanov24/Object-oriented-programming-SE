#pragma once
#include "Ship.h"
#define MAX_SHIPS 30

class Navy {
	char* navyName;
	Ship ships[MAX_SHIPS];
	int shipsSize;

	void copyFrom(const Navy& other);
	void free();

	void swapShips(int i, int j);

	int sumWeapons()const;

public:

	Navy();
	~Navy();
	Navy& operator=(const Navy& other);
	Navy(const Navy& other);

	void setNavyName(const char* name);
	const char* getNavyName()const;
	int getShipsSize()const;

	void addShip(const Ship& ship);

	void printNavy()const;

	void removeShip(const char* name);

	const Ship* getShip(int index)const;

	int compareGuns(const Navy& other) const;
};