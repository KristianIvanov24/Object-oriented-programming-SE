#pragma once
#include "Ship.h"

class Navy {
public:
    Navy(const char* country);
    Navy(const Navy& other);
    Navy& operator=(const Navy& other);
    ~Navy();

    void addShip(const Ship& ship);
    const Ship& getShip(int index) const;
    int getShipCount() const;

    int compareFirepower(const Navy& other) const;

private:
    char* m_country;
    Ship** m_ships;
    int m_count;
    int m_capacity;

    void grow();
    void copyFrom(const Navy& other);
    void free();
};
