#define _CRT_SECURE_NO_WARNINGS
#include "Ship.h"
#include <iostream>
#include "Navy.h"
int Ship::id = 0;
void Ship::free()
{
	delete[] name;
	name = nullptr;
}

void Ship::copyFrom(const Ship& other)
{
	id = other.id;
	year = other.year;
	amountOfGuns = other.amountOfGuns;
	type = other.type;
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
}

Ship::Ship(int year, Type type, int guns)
{
	setType(type);
	setYear(year);
	setAmountOfGuns(guns);
	setName();
	id++;
}

Ship::Ship():name(nullptr),year(0),amountOfGuns(0),type(Type::unknown)
{
	id++;
}

Ship::Ship(const Ship& other)
{
	copyFrom(other);
	id++;
}

Ship& Ship::operator=(const Ship& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

void Ship::setName()
{
	const char* typeStr = getType(this->type);

	int gunsDigits = (amountOfGuns == 0) ? 1 : amountOfDigits(amountOfGuns);
	int idDigits = (id == 0) ? 1 : amountOfDigits(id);

	int totalLen = 5 + strlen(typeStr) + 1 + gunsDigits + 1 + idDigits + 1;

	name = new char[totalLen];

	strcpy(name, "ship-");
	strcat(name, typeStr);
	strcat(name, "-");

	char gunsBuf[100];
	int tempGuns = amountOfGuns;
	int posG = gunsDigits;
	gunsBuf[posG--] = '\0';
	if (tempGuns == 0) gunsBuf[0] = '0';
	while (tempGuns > 0)
	{
		gunsBuf[posG--] = (tempGuns % 10) + '0';
		tempGuns /= 10;
	}
	strcat(name, gunsBuf);

	strcat(name, "-");

	char idBuf[100];
	int tempId = id;
	int posI = idDigits;
	idBuf[posI--] = '\0';
	if (tempId == 0) idBuf[0] = '0';
	while (tempId > 0)
	{
		idBuf[posI--] = (tempId % 10) + '0';
		tempId /= 10;
	}
	strcat(name, idBuf);
}

void Ship::setYear(int year)
{
	if (year < 0)
	{
		year = 0;
	}
	this->year = year;
}

void Ship::setAmountOfGuns(int amountOfGuns)
{
	if (amountOfGuns < 0)
	{
		amountOfGuns = 0;
	}
	this->amountOfGuns = amountOfGuns;
}

void Ship::setType(Type type)
{
	this->type = type;
}

Ship::~Ship()
{
	free();
	id--;
}

int Ship::getAmountOfGuns() const
{
	return amountOfGuns;
}

const char* Ship::getName()const
{
	return name;
}

const char* getType(Type t)
{
	switch (t)
	{
	case Type::bb:return "battleship"; break;
	case Type::bc:return "battlecruiser"; break;
	default:return"Unknown";
	}
}

int amountOfDigits(int n)
{
	int digits = 0;
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	return digits;
}
