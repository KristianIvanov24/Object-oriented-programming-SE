#include "Navy.h"

#include <algorithm>
#include <cstring>

void Navy::free()
{
    delete[] country;
    country = nullptr;
    numberOfShips = constants::DEFAULT_MIN;
}

void Navy::copyFrom(const Navy &other)
{
    setCountry(other.country);
    setShips(other.ships, other.numberOfShips);
}

Navy::Navy(const char *country) : country(nullptr), numberOfShips(0)
{
    setCountry(country);
}

Navy::Navy(const char *country, const Ship *ships, size_t numberOfShips)
    : country(nullptr), numberOfShips(constants::DEFAULT_MIN)
{
    setCountry(country);
    setShips(ships, numberOfShips);
}

Navy::Navy(const Navy &other)
{
    copyFrom(other);
}

Navy &Navy::operator=(const Navy &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

Navy::~Navy()
{
    free();
}

void Navy::setCountry(const char *country)
{
    delete[] this->country;
    if (!country)
    {
        this->country = nullptr;
        return;
    }
    this->country = new char[strlen(country) + 1];
    strcpy(this->country, country);
}

void Navy::setShips(const Ship *ships, size_t numberOfShips)
{
    if (!ships || numberOfShips > constants::MAX_SHIPS)
    {
        this->numberOfShips = constants::DEFAULT_MIN;
        return;
    }
    this->numberOfShips = numberOfShips;
    std::copy(ships, ships + numberOfShips, this->ships);
}

void Navy::addShip(Ship &ship)
{
    if (numberOfShips > constants::MAX_SHIPS)
    {
        return;
    }
    this->ships[numberOfShips++] = ship;
}

const Ship &Navy::getShip(size_t index) const
{
    return ships[index];
}

size_t Navy::getNumberOfShips() const
{
    return numberOfShips;
}

int Navy::hasMoreShips(const Navy &other) const
{
    return (numberOfShips > other.numberOfShips) - (numberOfShips < other.numberOfShips);
}
