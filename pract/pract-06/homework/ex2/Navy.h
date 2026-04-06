#pragma once

#include "Ship.h"
#include "constants.h"

class Navy
{
    char *country;
    Ship ships[constants::MAX_SHIPS];
    size_t numberOfShips;

    void free();
    void copyFrom(const Navy &);

public:
    Navy() = delete;
    Navy(const char *);
    Navy(const char *, const Ship *, size_t);
    Navy(const Navy &);
    Navy &operator=(const Navy &);
    ~Navy();

    void setCountry(const char *);
    void setShips(const Ship *, size_t);

    void addShip(Ship &);
    const Ship &getShip(size_t) const;
    size_t getNumberOfShips() const;
    int hasMoreShips(const Navy &) const;
};