#pragma once
#include "Ship.h"
#include "Constants.h"

class Navy
{
private:

	char* name;
	Ship* ships;
	size_t size;

	void free();
	void copyFrom(const Navy& other);

public:
	
	Navy();
	~Navy();
	Navy(const Navy& other);
	Navy& operator=(const Navy& other);

	void addShip(const Ship& ship);
	Ship getShipInPos(int pos) const;
	size_t getShipsCount() const;
	int compareGunsAmount(const Navy& other);

	const char* getName() const;
	const Ship* getShips() const;

	void printNavyInfo() const;
};

