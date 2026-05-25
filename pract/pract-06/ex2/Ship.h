#pragma once
#include "ShipClass.h"

class Ship
{
private:

	char* name;
	int year;
	int gunsAmount;
	ShipClass shipClass;

	void setName();
	void setYear(int year);
	void setGunsAmount(int gunsAmount);

	void intToChars(int n, char* buffer) const;
	char digitToChar(int n) const;
	void reverseString(char* str, int len) const;

	void free();
	void copyFrom(const Ship& other);

public:
	Ship();
	Ship(int year, int gunsAmount, ShipClass shipClass);

	~Ship();
	Ship(const Ship& other);
	Ship& operator=(const Ship& other);

	const char* getName() const;
	int getYear() const;
	int getGunsAmount() const;
	ShipClass getShipClass() const;

	void printShipInfo() const;
};

