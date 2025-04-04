#include "Navy.h"
#include "Ship.h"
#include <cstring>
#pragma warning (disable:4996)

void Navy::addShip(const Ship& ships)
{
	if (countOfShip > constants::MAX_SIZE)
	{
		return;
	}

	this->ships[countOfShip] = ships;
	countOfShip++;
}

int Navy::findIndex(const char* name)
{
	if (!name)
	{
		return;
	}

	for (int i = 0; i < countOfShip; i++)
	{
		if (!strcmp(ships[i].getShipName(), name))
		{
			return i;
		}
	}
	return -1;
}

void Navy::removeShip( const char* name)
{
	if (!name)
	{
		return;
	}

	int currentIndex = findIndex(name);

	if (currentIndex != -1)
	{
		return;
	}

	std::swap(ships[currentIndex], ships[countOfShip - 1]);
	countOfShip--;

}

size_t Navy::getShipCount() const
{
	return countOfShip;
}

int Navy::compareByWeapon(const Navy& other) const
{
	size_t weaponCurrent = 0;
	size_t weaponOther = 0;
	for (int i = 0; i < countOfShip; i++)
	{
		 weaponCurrent = ships[i].getWeaponCount();
	}
		
	for (int i = 0; i < countOfShip; i++)
	{
		 weaponOther = other.ships[i].getWeaponCount();
	}	
		if (weaponCurrent < weaponOther)
			return -1;
		else if (weaponCurrent > weaponOther)
			return 1;
		else
			return 0;
	
}




