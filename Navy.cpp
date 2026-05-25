#pragma warning(disable: 4996)
#include "Navy.h"
#include <iostream>
#include <cstring>

void Navy::grow() {
    int newCap = (m_capacity == 0) ? 4 : m_capacity * 2;
    Ship** newArr = new Ship*[newCap];
    for (int i = 0; i < m_count; ++i)
        newArr[i] = m_ships[i];
    delete[] m_ships;
    m_ships = newArr;
    m_capacity = newCap;
}

void Navy::copyFrom(const Navy& other) {

    m_country = new char[std::strlen(other.m_country) + 1];
    std::strcpy(m_country, other.m_country);


    m_count = other.m_count;
    m_capacity = other.m_capacity;
    m_ships = new Ship * [m_capacity];
    for (int i = 0; i < m_count; ++i)
        m_ships[i] = new Ship(*other.m_ships[i]);
}

void Navy::free() {
    for (int i = 0; i < m_count; ++i)
        delete m_ships[i];
    delete[] m_ships;
    delete[] m_country;
}

Navy::Navy(const char* country)
    : m_country(nullptr), m_ships(nullptr), m_count(0), m_capacity(0)
{
    if (!country) {
       std::cout<<"Country must not be null!";
       country = "Unknown";
    }
    m_country = new char[std::strlen(country) + 1];
    std::strcpy(m_country, country);
}

Navy::Navy(const Navy& other)
    : m_country(nullptr), m_ships(nullptr), m_count(0), m_capacity(0)
{
    copyFrom(other);
}

Navy& Navy::operator=(const Navy& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Navy::~Navy() {
    free();
}

void Navy::addShip(const Ship& ship) {
    if (m_count == m_capacity) grow();
    m_ships[m_count++] = new Ship(ship);
}

const Ship& Navy::getShip(int index) const {
    if (index < 0 || index >= m_count)
    {
        std::cout<<"Ship index out of range! Index set to 0.";
        return *m_ships[0];
    }
    return *m_ships[index];
}

int Navy::getShipCount() const {
    return m_count;
}

int Navy::compareFirepower(const Navy& other) const {
    int myGuns = 0;
    int otherGuns = 0;
    for (int i = 0; i < m_count; ++i) myGuns += m_ships[i]->getNumberOfGuns();
    for (int i = 0; i < other.m_count; ++i) otherGuns += other.m_ships[i]->getNumberOfGuns();

    if (myGuns < otherGuns) return -1;
    if (myGuns > otherGuns) return  1;
    return 0;
}
