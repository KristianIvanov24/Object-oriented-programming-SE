#pragma once
#include "Treasure.h"
#include "Constants.h"
#include "Validations.h"

class TreasureMap {
    Treasure m_treasures[Constants::MAX_TREASURES];
    int m_count;

    double distanceFromOrigin(const Treasure& t) const;

public:
    TreasureMap();

    bool addTreasure(const char* name, int x, int y, int value);
    bool removeByName(const char* name);
    Treasure* findByCoordinates(int x, int y);

    void sortByValue();
    void sortByDistance();

    void print() const;
    Treasure getMostValuable() const;

    void saveToFile(const char* filename) const;
    void readFromFile(const char* filename);
};