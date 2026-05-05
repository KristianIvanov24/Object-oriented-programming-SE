#include "Ship.h"
#include "constants.h"

#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace constants;

size_t Ship::id = 0;

void Ship::free() {
    delete[] name;
    name = nullptr;
    year = DEFAULT_MIN;
    type = ShipClass::BB;
    numberOfGuns = DEFAULT_MIN;
}

void Ship::copyFrom(const Ship &other) {
    if (!other.name) {
        this->name = nullptr;
    } else {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
    }
    setYear(other.getYear());
    setType(other.getType());
    setNumberOfGuns(other.getNumberOfGuns());
}

Ship::Ship(unsigned year, ShipClass type, unsigned numberOfGuns)
: year(DEFAULT_MIN), type(ShipClass::BB), numberOfGuns(DEFAULT_MIN) {
    id++;
    setYear(year);
    setType(type);
    setNumberOfGuns(numberOfGuns);
    setName();
}

Ship::Ship(const Ship &other) {
    id++;
    copyFrom(other);
}

Ship & Ship::operator=(const Ship &other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Ship::~Ship() {
    free();
}

void Ship::setName() {
    delete[] this->name;
    this->name = new char[BUFFER_SIZE];
    strcpy(this->name, "ship-");
    strcat(this->name, typeToString());
    strcat(this->name, "-");

    const char* gunsString = intToString(numberOfGuns);
    const char* idString = intToString(id);
    
    strcat(this->name, gunsString);
    strcat(this->name, "-");
    strcat(this->name, idString);

    delete[] gunsString;
    delete[] idString;
}

const char * Ship::typeToString() const {
    switch (this->type) {
        case ShipClass::BB: return "BB";
        case ShipClass::BC: return "BC";
        default: return "?";
    }
}

const char * Ship::intToString(unsigned n) const {
    char* res = new char[BUFFER_SIZE];
    size_t i = 0;
    if (n == 0) {
        res[i++] = '0';
        res[i] = '\0';
        return res;
    }

    while (n > 0) {
        res[i++] = n % 10 + '0';
        n /= 10;
    }
    res[i] = '\0';

    std::reverse(res, res + i);
    return res;
}

Ship::Ship() : name(nullptr), year(DEFAULT_MIN), type(ShipClass::BB), numberOfGuns(DEFAULT_MIN) {
}

void Ship::setYear(unsigned year) {
    this->year = year;
}

void Ship::setType(ShipClass type) {
    this->type = type;
}

void Ship::setNumberOfGuns(unsigned numberOfGuns) {
    this->numberOfGuns = numberOfGuns;
}

const char * Ship::getName() const {
    return name;
}

unsigned Ship::getYear() const {
    return year;
}

ShipClass Ship::getType() const {
    return type;
}

unsigned Ship::getNumberOfGuns() const {
    return numberOfGuns;
}