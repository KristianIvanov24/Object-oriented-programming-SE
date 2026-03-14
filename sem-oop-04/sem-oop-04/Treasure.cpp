#define _CRT_SECURE_NO_WARNINGS
#include "Treasure.h"
#include <cstring>
#include <iostream>

double Treasure::findDistanceFrom0() const
{
	double dis = x * x + y * y;
	return sqrt(dis);
}

Treasure::Treasure(const char* name, int x, int y, int value)
{
	setName(name);
	setCoordinates(x, y);
	setValue(value);
}

void Treasure::setName(const char* name)
{
	if (strlen(name) >= constants::MAX_TRESURE_NAME_LEN)
	{
		this->name[0] = '\0';
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
	this->value = value;
}

const char* Treasure::getName() const
{
	return this->name;
}

int Treasure::getX()const
{
	return x;
}

int Treasure::getY()const
{
	return y;
}

int Treasure::getValue() const
{
	return value;
}

void Treasure::print()const
{
	std::cout << name << " (" << x << ',' << y << ')' << " value:" << value;
}
