#pragma once
#include "Treasure.h"

class TreasureMap
{
private:
    Treasure treasures[50];
    int count;

public:
    TreasureMap();

    bool addTreasure(const Treasure& t);
    bool removeTreasure(const char* name);

    Treasure* findByCoordinates(int x, int y);

    void sortByValue();
    void sortByDistance();

    void printAll() const;

    Treasure* findMostValuable();

    void saveToFile(const char* filename) const;
    void loadFromFile(const char* filename);
};