#include "Ship.h"
#include <cstring>
#pragma warning (disable:4996)

void Ship::free()
{
	delete[] name;
	name = nullptr;

	launchYear = 0;
	caliber = ShipCaliber::BATTLESHIP;
	gunCount = 0;
}

void Ship::copyFrom(const Ship& other)
{
	name = new char[strlen(other.name) + 1];

	launchYear = other.launchYear;
	caliber = other.caliber;
	gunCount = other.gunCount;
}

Ship::Ship()
{
	char* name = nullptr;
	int launchYear = 0;
	ShipCaliber caliber = ShipCaliber::BATTLESHIP;
	unsigned gunCount = 0;
}

Ship::Ship(const char* name, int launchYear, ShipCaliber caliber, unsigned gunCount)
{
	if (!name)
		return;

	setName(name);
	setLaunchYear(launchYear);
	setCaliber(caliber);
	setGunCount(gunCount);
}

Ship::Ship(const Ship& other)
{
	copyFrom(other);
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

Ship::~Ship()
{
	free();
}

char* Ship::getName() const
{
	return name;
}

int Ship::getLaunchYear() const
{
	return launchYear;
}

ShipCaliber Ship::getCaliber() const
{
	return caliber;
}

unsigned Ship::getGunCount() const
{
	return gunCount;
}

void Ship::setName(const char* name)
{
	if (!name || this->name == name)
		return;

	delete[] this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Ship::setLaunchYear(int year)
{
	this->launchYear = year;
}

void Ship::setCaliber(ShipCaliber caliber)
{
	this->caliber = caliber;
}

void Ship::setGunCount(unsigned gunCount)
{
	this->gunCount = gunCount;
}