#pragma once
#include "Ship.h"

namespace constants {
	constexpr int MAX_SIZE = 30;
}

class Navy
{
private:
	char* country = nullptr;
	Ship ships[constants::MAX_SIZE];
	size_t countOfShip = 0;
public:
	void addShip(const Ship& ships);
	int findIndex( const char* name);
	void removeShip(const char* name);
	size_t getShipCount() const;
	void compareByWeapon(const Navy& other) const;
};