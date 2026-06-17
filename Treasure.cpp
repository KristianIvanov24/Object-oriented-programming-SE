#define _CRT_SECURE_NO_WARNINGS
#include "treasure.h"
#include "constants.h"
#include <iostream>
#include <cstring>

void Treasure::setName(const char* name)
{
	if (strlen(name) > Constants::MAX_TREASURE_NAME_LEN)
	{
		strcpy(this->name, "Invalid");
		std::cout << "Exceeded limit of characters" << std::endl;
		return;
	}

	strcpy(this->name, name);
}

void Treasure::setCoordinates(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Treasure::setValue(int value)
{
	this->valueOfTreasure = value;
}

const char* Treasure::getName() const
{
	return this->name;
}

int Treasure::getX() const
{
	return this->x;
}

int Treasure::getY() const
{
	return this->y;
}

int Treasure::getValue() const
{
	return this->valueOfTreasure;
}

void Treasure::printTreasure() const
{
	std::cout << name << "(" << x << ";" << y << ")" << valueOfTreasure << std::endl;
}

double Treasure::findDisgtanceFrom0() const
{
	double distance = x * x + y * y;
	return sqrt(distance);
}

Treasure::Treasure(const char* name, int x, int y, int value)
{
	setName(name);
	setCoordinates(x, y);
	setValue(value);
}