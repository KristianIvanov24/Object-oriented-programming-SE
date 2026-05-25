#include "Ship.h"
#include "Constants.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#pragma warning(disable : 4996)

using constants::BUFFER_SIZE;

void Ship::setName()
{
    const char* prefix = "ship-";
    const char* shipType = shipClassToString(shipClass);

    char gunsBuffer[BUFFER_SIZE];
    char idBuffer[BUFFER_SIZE];

    intToChars(gunsAmount, gunsBuffer);
    intToChars(std::rand(), idBuffer);

    size_t totalLen = std::strlen(prefix) + std::strlen(shipType) + 1 +
                      std::strlen(gunsBuffer) + 1 +std::strlen(idBuffer) + 1;


    if (name) {
        delete[] name;
    }

    name = new char[totalLen];

    std::strcpy(this->name, prefix);
    std::strcat(this->name, shipType);
    std::strcat(this->name, "-");
    std::strcat(this->name, gunsBuffer);
    std::strcat(this->name, "-");
    std::strcat(this->name, idBuffer);
}

void Ship::setYear(int year)
{
    if (year < constants::YEAR_LOWER_LIMIT || year > constants::CURRENT_YEAR) {
        this->year = constants::DEFAULT_YEAR;
    }
    else {
        this->year = year;
    }
}

void Ship::setGunsAmount(int gunsAmount)
{
    if (gunsAmount < 0) {
        this->gunsAmount = constants::DEFAULT_GUNS_AMOUNT;
    }
    else {
        this->gunsAmount = gunsAmount;
    }
}

void Ship::intToChars(int n, char* buffer) const
{
    if (n == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    int i = 0;
    while (n > 0) {
        buffer[i++] = digitToChar(n % 10);
        n /= 10;
    }
    buffer[i] = '\0';

    reverseString(buffer, i);
}

char Ship::digitToChar(int n) const
{
    return n + '0';
}

void Ship::reverseString(char* str, int len) const 
{
    int start = 0;
    int end = len - 1;
    while (start < end) {
        std::swap(str[start], str[end]);
        
        start++;
        end--;
    }
}
void Ship::free()
{
    delete[] name;
    name = nullptr;
}

void Ship::copyFrom(const Ship& other)
{
    name = new char[strlen(other.getName()) + 1];
    strcpy(name, other.getName());

    year = other.getYear();
    shipClass = other.getShipClass();
    gunsAmount = other.getGunsAmount();
}

Ship::Ship() : year(constants::DEFAULT_YEAR), gunsAmount(constants::DEFAULT_GUNS_AMOUNT), shipClass(ShipClass::bb), name(nullptr)
{
    setName();
}

Ship::Ship(int year, int gunsAmount, ShipClass shipClass) : shipClass(shipClass), name(nullptr)
{
    setYear(year);
    setGunsAmount(gunsAmount);
    setName();
}

Ship::~Ship()
{
    free();
}

Ship::Ship(const Ship& other) : name(nullptr)
{
    copyFrom(other);
}

Ship& Ship::operator=(const Ship& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

const char* Ship::getName() const
{
    return name;
}

int Ship::getYear() const
{
    return year;
}

int Ship::getGunsAmount() const
{
    return gunsAmount;
}

ShipClass Ship::getShipClass() const
{
    return shipClass;
}

void Ship::printShipInfo() const
{
    std::cout << "  > " << name
        << " | Year: " << year
        << " | Guns: " << gunsAmount << std::endl;
}
