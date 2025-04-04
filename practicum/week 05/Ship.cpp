#include "Ship.h"
#include <cstring>
#pragma warning (disable:4996)

namespace constants {
	constexpr int MIN_YEAR = 0;
}

void Ship::copyFrom(const Ship& other)
{
	this->shipName = new char[strlen(shipName) + 1];
	strcpy(this->shipName, other.shipName);
	this->shipClass = other.shipClass;
	this->year = other.year;
	this->weaponCount = other.weaponCount;
}


void Ship::free()
{
	delete[] shipName;
}

Ship::Ship()
{
}

Ship::Ship(const char* name, int year, classOfShip shipClass, unsigned int countWeapon)
{
	if (!name)
	{
		strcpy(shipName, " ");
		return;
	}
	strcpy(shipName, name);

	this->year = year;
	this->shipClass = shipClass;
	this->weaponCount = weaponCount;
}

Ship::Ship(const Ship& other)
{
	copyFrom(other);
}

Ship& Ship::operator=(const Ship& other)
{
	if (this != &other)
	{
		return;
	}
	free();
	copyFrom(other);
}

Ship::~Ship()
{
	free();
}

const char* Ship::getShipName() const
{
	return shipName;
}

int Ship::getYear() const
{
	return year;
}

classOfShip Ship::getClass() const
{
	return classOfShip();
}

unsigned int Ship::getWeaponCount() const
{
	return weaponCount;
}

void Ship::setShipName(char* shipName)
{
	if (!shipName || this->shipName == shipName)
	{
		return;
	}
	
	shipName = new char[strlen(shipName) + 1];
	strcpy(shipName, this->shipName);
}

void Ship::setYear(int year)
{
	if (year < constants::MIN_YEAR)
	{
		return;
	}

	this->year = year;
}

void Ship::setShipClass(classOfShip shipClass)
{
	this->shipClass = shipClass;
}

void Ship::setWeaponCount(unsigned int weaponCount)
{
	this->weaponCount = weaponCount;
}

