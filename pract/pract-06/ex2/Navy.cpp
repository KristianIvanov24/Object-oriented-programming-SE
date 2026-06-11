#include "Navy.h"
#include "Constants.h"
#include <iostream>
#pragma warning(disable : 4996)

void Navy::free()
{
    delete[] name;
    name = nullptr;

    delete[] ships;
    ships = nullptr;
    
    size = 0;
}

void Navy::copyFrom(const Navy& other)
{
    name = new char[strlen(other.getName()) + 1];
    strcpy(name, other.getName());

    size = other.getShipsCount();
    ships = new Ship[size];

    for (int i = 0; i < size; i++) {
        ships[i] = other.getShipInPos(i);
    }
}

Navy::Navy() : name(nullptr), ships(nullptr), size(0) {
    name = new char[strlen(constants::DEFAULT_NAVY_NAME) + 1];
    strcpy(name, constants::DEFAULT_NAVY_NAME);
}

Navy::~Navy()
{
    free();
}

Navy::Navy(const Navy& other) : name(nullptr), ships(nullptr), size(0)
{
    copyFrom(other);
}

Navy& Navy::operator=(const Navy& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

void Navy::addShip(const Ship& ship)
{
    Ship* newShips = new Ship[size + 1];

    if (ships) {
        for (int i = 0; i < size; i++) {
            newShips[i] = ships[i];
        }
        delete[] ships;
    }

    newShips[size] = ship;
    ships = newShips;
    size++;
}

Ship Navy::getShipInPos(int pos) const
{
    if (pos < 0 || pos >= size) {
        return Ship();
    }
    return ships[pos];
}

size_t Navy::getShipsCount() const
{
    return size;
}

int Navy::compareGunsAmount(const Navy& other)
{
    int myTotal = 0;
    for (int i = 0; i < size; i++) {
        myTotal += ships[i].getGunsAmount();
    }

    int otherTotal = 0;
    for (int i = 0; i < other.getShipsCount(); i++) {
        otherTotal += other.getShipInPos(i).getGunsAmount();
    }

    if (myTotal > otherTotal) return 1;
    if (myTotal < otherTotal) return -1;
    return 0;
}

const char* Navy::getName() const {
    return name;
}
const Ship* Navy::getShips() const {
    return ships;
}

void Navy::printNavyInfo() const
{
    std::cout << "--- Navy: " << name << " ---" << std::endl;
    std::cout << "Ships count: " << size << std::endl;

    for (size_t i = 0; i < size; i++) {
        ships[i].printShipInfo();
    }
    std::cout << "--------------------------" << std::endl;
}
