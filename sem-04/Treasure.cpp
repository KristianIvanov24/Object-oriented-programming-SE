#include "Treasure.h"
#include <iostream>
#pragma warning(disable : 4996)

bool Treasure::isValidName(const char* name) 
{
	if(strlen(name)>=constants::MAX_NAME)
	{
		strcpy(this->name, "Unknown");
		return false;
	}
	return true;
}

bool Treasure::isValidValue(int value)
{
	if (value < 0)
	{
		this->value = 0;
		return false;
	}
	return true;
}

Treasure::Treasure() : x(0),y(0),value(0)
{
	strcpy(name, "Unknown");
}

Treasure::Treasure(const char* name, int x, int y, int value)
{
	setName(name);
	setX(x);
	setY(y);
	setValue(value);
}

Treasure::~Treasure()
{
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
	return this->value;
}

double Treasure::getDistance() const
{
	return sqrt(x * x + y * y);
}

void Treasure::setName(const char* name)
{
	if (isValidName(name))
		strcpy(this->name, name);
}

void Treasure::setX(int x)
{
	this->x = x;
}

void Treasure::setY(int y)
{
	this->y = y;
}

void Treasure::setValue(int value)
{
	if (isValidValue(value))
		this->value = value;
}
