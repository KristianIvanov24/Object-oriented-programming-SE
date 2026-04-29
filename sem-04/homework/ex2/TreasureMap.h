#pragma once

#include "constants.h"
#include "Treasure.h"

class TreasureMap
{
    Treasure treasures[constants::MAX_TREASURES];
    size_t treasureCount = 0;

    size_t findBy(const char *) const;
    void sort(bool (*cmp)(const Treasure &, const Treasure &));

public:
    bool addTreasure(const Treasure &);
    bool addTreasure(const char *, int, int, int);
    bool remove(const char *);
    size_t findBy(int, int) const;
    void sortByValue();
    void sortByDistanceFromOrigin();
    void print() const;
    Treasure getMostValuable() const;

    bool saveToFile(const char *) const;
    bool readFromFile(const char *);
};