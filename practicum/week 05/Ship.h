#pragma once

enum class classOfShip {
	battleship,
	battlecruiser
};

class Ship
{
private:
	char* shipName = nullptr;
	int year = 0;
	classOfShip shipClass;
	unsigned int weaponCount = 0;
public:
	Ship();
	Ship(const char* name, int year, classOfShip shipClass,unsigned int countWeapon);
	Ship(const Ship& other);
	Ship& operator=(const Ship& other);
	~Ship();

	void free();
	void copyFrom(const Ship& other);

	const char* getShipName() const;
	int getYear() const;
	classOfShip getClass() const;
	unsigned int getWeaponCount() const;

	void setShipName(char* shipName);
	void setYear(int year);
	void setShipClass(classOfShip shipClass);
	void setWeaponCount(unsigned int weaponCount);
};

