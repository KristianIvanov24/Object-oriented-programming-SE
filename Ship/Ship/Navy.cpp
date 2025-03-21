#include "Navy.h"
#include <iostream> 
#include <cstring>
#pragma warning(disable:4996)


void Navy::copyFrom(const Navy& other) {
	this->navyName = new char[strlen(other.navyName) + 1];
	strcpy(this->navyName, other.navyName);
	this->shipsSize = other.shipsSize;

	for (int i = 0; i < this->shipsSize; i++) {
		this->ships[i] = other.ships[i];
	}
}

void Navy::swapShips(int i, int j) {
	Ship swap = ships[i];
	ships[i] = ships[j];
	ships[j] = swap;
}

void Navy::free() {
	delete[] navyName;
	navyName = nullptr;
}

Navy::Navy() {
	navyName = nullptr;
	shipsSize = 0;
}

Navy::~Navy() {
	free();
}

Navy::Navy(const Navy& other) {
	copyFrom(other);
}

Navy& Navy::operator=(const Navy& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

void Navy::setNavyName(const char* name) {
	
	if (!name) {
		strcpy(navyName, "No name");
		return;
	}

	navyName = new char[strlen(name) + 1];
	strcpy(navyName, name);
}

const char* Navy::getNavyName()const {
	return this->navyName;
}

void Navy::addShip(const Ship& ship) {
	this->ships[this->shipsSize++] = ship;
}

void Navy::printNavy()const {
	std::cout << "Navy name: " << navyName << std::endl;
	for (int i = 0; i < shipsSize; i++) {
		ships[i].printShip();
	}
}

void Navy::removeShip(const char* name) {
	for (int i = 0; i < shipsSize; i++) {
		if (strcmp(ships[i].getShipName(), name) == 0) {
			swapShips(i, shipsSize - 1);
			shipsSize--;
		}
	}
}

const Ship* Navy::getShip(int index)const {
	return &ships[index];
}

int Navy::getShipsSize()const {
	return shipsSize;
}

int Navy::sumWeapons()const {
	int sum = 0;
	for (int i = 0; i < shipsSize; i++) {
		sum += ships[i].getCountWeapons();
	}

	return sum;
}

int Navy::compareGuns(const Navy& other) const {
	int sumThis = this->sumWeapons();
	int sumOther = this->sumWeapons();

	if (sumThis < sumOther) return -1;
	else if (sumThis == sumOther) return 0;
	else return 1;
}