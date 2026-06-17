#pragma once
#include "Ship.h"
class Navy
{
private:
	char* country;
	Ship* ships;
	size_t amountOfShips;
	size_t capacity;
	void free();
	void copyFrom(const Navy& other);
	void changeCapacity();
public:
	Navy();
	Navy(const char* country);
	Navy(const Navy& other);
	Navy& operator=(const Navy& other);
	void addShip(const Ship& s);
	const Ship& getShip(size_t index)const;
	size_t getAmountOfShips()const;
	int getAmountOfGuns()const;
	int compare(const Navy& n)const;
	~Navy();
};

