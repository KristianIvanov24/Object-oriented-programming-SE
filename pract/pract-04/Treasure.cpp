#include "Treasure.h"
#include <iostream>
#include <cstring>
#include <cmath>

Treasure::Treasure()
{
    name[0] = '\0';
    x = y = value = 0;
}

Treasure::Treasure(const char* name, int x, int y, int value)
{
    strncpy(this->name, name, 32);
    this->name[32] = '\0';
    this->x = x;
    this->y = y;
    this->value = value;
}

const char* Treasure::getName() const
{
    return name;
}

int Treasure::getX() const
{
    return x;
}

int Treasure::getY() const
{
    return y;
}

int Treasure::getValue() const
{
    return value;
}

double Treasure::distanceFromOrigin() const
{
    return sqrt(x * x + y * y);
}

void Treasure::print() const
{
    std::cout << name << " (" << x << ", " << y << ") value: " << value << std::endl;
}
