#pragma once

#include "constants.h"
#include <fstream>

class Treasure
{
    char name[constants::MAX_NAME_LEN + 1];
    int x, y;
    int value;

public:
    Treasure();
    Treasure(const char *, int, int, int);

    void setName(const char *);

    const char *getName() const;
    int getX() const;
    int getY() const;
    int getValue() const;

    int distanceFromOrigin() const;
    void print() const;

    void saveToFile(std::ofstream &) const;
    void readFromFile(std::ifstream &file);
};