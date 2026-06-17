#include <iostream>
#include <fstream>
#include "Treasure.h"
#include "constants.h"

Treasure::Treasure() : x(0), y(0), value(0) {
    setName("DEFAULT");
}

Treasure::Treasure(const char *name, int x, int y, int value) : x(x), y(y), value(value) {
    setName(name);
}

void Treasure::setName(const char *name) {
    if (strlen(name) > constants::MAX_NAME_LEN) {
        strcpy(this->name, "DEFAULT");
        return;
    }
    strncpy(this->name, name, constants::MAX_NAME_LEN + 1);
    this->name[constants::MAX_NAME_LEN] = '\0';
}

const char *Treasure::getName() const {
    return name;
}

int Treasure::getX() const {
    return x;
}

int Treasure::getY() const {
    return y;
}

int Treasure::getValue() const {
    return value;
}

int Treasure::distanceFromOrigin() const {
    return x * x + y * y;
}

void Treasure::print() const {
    std::cout << name << " (" << x << ", " << y << ") value: " << value << std::endl;
}

void Treasure::saveToFile(std::ofstream &file) const {
    file << name << " " << x << " " << y << " " << value << std::endl;
}

void Treasure::readFromFile(std::ifstream &file) {
    file >> name >> x >> y >> value;
}
