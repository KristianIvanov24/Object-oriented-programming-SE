#define _CRT_SECURE_NO_WARNINGS
#include "Navy.h"
#include <iostream>
void Navy::free()
{
	delete[] country;
	country = nullptr;
	delete[] ships;
	ships = nullptr;
	amountOfShips = 0;
	capacity = 0;
}

void Navy::copyFrom(const Navy& other)
{
	country = new char[strlen(other.country) + 1];
	strcpy(this->country, other.country);
	this->amountOfShips = other.amountOfShips;
	this->capacity = other.capacity;
	ships = new Ship[capacity];
	for (int i = 0; i < amountOfShips; ++i)
	{
		ships[i] = other.ships[i];
	}
}

void Navy::changeCapacity()
{
	capacity += 10;
	Ship* copy = new Ship[capacity];
	for (int i = 0; i < amountOfShips; ++i)
	{
		copy[i] = ships[i];
	}
	delete[] ships;
	ships = copy;
}

Navy::Navy():amountOfShips(0),capacity(10),country(nullptr)
{
	ships = new Ship[capacity];
}

Navy::Navy(const char* country) : amountOfShips(0), capacity(10)
{
	this->country = new char[strlen(country) + 1];
	strcpy(this->country, country);
	ships = new Ship[capacity];
}

Navy::Navy(const Navy& other)
{
	copyFrom(other);
}

Navy& Navy::operator=(const Navy& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

void Navy::addShip(const Ship& s)
{
	if (amountOfShips >= capacity)
	{
		changeCapacity();
	}
	ships[amountOfShips++] = s;
}

const Ship& Navy::getShip(size_t index) const
{
	return ships[index];
}

size_t Navy::getAmountOfShips() const
{
	return amountOfShips;
}

int Navy::getAmountOfGuns()const
{
	int count = 0;
	for (int i = 0; i < amountOfShips; ++i)
	{
		count += ships[i].getAmountOfGuns();
	}
	return count;
}

int Navy::compare(const Navy& n) const
{
	if (getAmountOfGuns() > n.getAmountOfGuns())
		return 1;
	else if (getAmountOfGuns() < n.getAmountOfGuns())
		return -1;
	return 0;
}

Navy::~Navy()
{
	free();
}
