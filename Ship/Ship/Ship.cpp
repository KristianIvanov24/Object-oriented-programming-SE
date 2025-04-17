#include "Ship.h"
#include <iostream>
#include<cstring>
#pragma warning(disable:4996)

Ship::Ship() {
	shipName = nullptr;
	age = 0;
	clas = classShip::bb;
	countWeapons = 0;
}

bool Ship::validAge() {
	if (age >= 0)
		return true;	
	return false;
}

bool Ship::validCountWeapons() {
	if (countWeapons >= 0)
		return true;
	return false;
}


void Ship::copyFrom(const Ship& other) {
	
	this->shipName = new char[strlen(other.shipName) + 1];
	
	strcpy(this->shipName, other.shipName);
	
	this->age = other.age;
	
	this->clas = other.clas;
	
	this->countWeapons = other.countWeapons;
}
void Ship::free() {
	delete[] shipName;
	shipName = nullptr;
}

Ship::~Ship() {
	free();
}
Ship::Ship(const Ship& other) {
	copyFrom(other);
}
Ship& Ship::operator=(const Ship& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Ship::Ship(const char* name, int age, classShip clas, int countWeapons) {
	shipName = new char[strlen(name) + 1];
	strcpy(shipName, name);
	this->age = age;
	this->clas = clas;
	this->countWeapons = countWeapons;
}
void Ship::printShip()const {
	std::cout << "Ship name: " << shipName << std::endl;
	std::cout << "Ship age: " << age << std::endl;
	std::cout << "Ship class: " << (clas == classShip::bb ? "battleship" : "battlecruiser") << std::endl;
	std::cout << "Ship count weapons: " << countWeapons << std::endl;
}

const char* Ship::getShipName()const {
	return shipName;
}
int Ship::getAge()const {
	return age;
}
void Ship::getClass()const {
	std::cout << (clas == classShip::bb ? "battleship" : "battlecruiser");
}
int Ship::getCountWeapons()const {
	return countWeapons;
}

void Ship::setShipName(const char* name) {
	if (!name || name == shipName) {
		this->shipName = nullptr;
		return;
	}

	this->shipName = new char[strlen(name) + 1];
	strcpy(this->shipName, name);
}

void Ship::setAge(int age) {
	if (validAge())
		this->age = age;
	else this->age = 0;
}
void Ship::setClass(classShip clas) {
	this->clas = clas;
}
void Ship::setCountWeapons(int countWeapons) {
	if (validCountWeapons()) this->countWeapons = countWeapons;
	else this->countWeapons = 0;	
}
