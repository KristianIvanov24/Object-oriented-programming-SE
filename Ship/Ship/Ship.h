#pragma once

enum classShip {
	bb,
	bc
};

class Ship {
	char* shipName;
	int age;
	classShip clas;
	int countWeapons;

	void free();
	void copyFrom(const Ship& other);

	bool validAge();
	bool validCountWeapons();

public:
	Ship();
	~Ship();
	Ship& operator=(const Ship& other);
	Ship(const Ship& other);
	Ship(const char* name, int age, classShip clas, int countWeapons);
	void printShip()const;
	const char* getShipName()const;
	int getAge()const;
	void getClass()const;
	int getCountWeapons()const;

	void setShipName(const char* name);
	void setAge(int age);
	void setClass(classShip clas);
	void setCountWeapons(int countWeapons);

};