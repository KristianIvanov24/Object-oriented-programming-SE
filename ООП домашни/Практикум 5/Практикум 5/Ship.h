#pragma once

enum class ShipCaliber
{
	BATTLESHIP,
	BATTLECRUISER
};

class Ship
{
private:
	char* name = nullptr;
	int launchYear = 0;
	ShipCaliber caliber = ShipCaliber::BATTLESHIP;
	unsigned gunCount = 0;

	void copyFrom(const Ship&);

	void free();
public:
	Ship();
	Ship(const char*, int, ShipCaliber, unsigned);
	Ship(const Ship&);
	Ship& operator=(const Ship&);
	~Ship();

	char* getName() const;
	int getLaunchYear() const;
	ShipCaliber getCaliber() const;
	unsigned getGunCount() const;

	void setName(const char*);
	void setLaunchYear(int);
	void setCaliber(ShipCaliber caliber);
	void setGunCount(unsigned gunCount);

};

