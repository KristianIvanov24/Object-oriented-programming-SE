#define _CRT_SECURE_NO_WARNINGS
#include "TreasureMap.h"
#include <iostream>
#include<cstring>
#include <fstream>

bool TreasureMap::addTreasure(const Treasure& treasure) {
    if (amountOfTreasures >= constants::MAX_TRESURES_IN_MAP)
        return false;
    treasures[amountOfTreasures++] = treasure;
    return true;
}

void TreasureMap::removeTresureByName(const char* name)
{
    int index = -1;
    for (int i = 0; i < amountOfTreasures; ++i)
    {
        if (strcmp(name, treasures[i].getName())==0)
        {
            index = i;
        }
    }
    if (index == -1)
        return;
    for (int i = index; i < amountOfTreasures - 1; ++i)
    {
        treasures[i] = treasures[i + 1];
    }
    amountOfTreasures--;
}

Treasure TreasureMap::findTresure(int x, int y) const
{
    for (int i = 0; i < amountOfTreasures; ++i)
    {
        if (treasures[i].getX() == x && treasures[i].getY() == y)
        {
            return treasures[i];
        }
    }
    return {};
}

void swapTreasures(Treasure& t1, Treasure& t2)
{
    Treasure temp = t1;
    t1 = t2;
    t2 = temp;
}

void TreasureMap::sortByValue()
{
    for (int i = 0; i < amountOfTreasures - 1; ++i)
    {
        for (int j = i + 1; j < amountOfTreasures; ++j)
        {
            if (treasures[i].getValue() > treasures[j].getValue())
            {
                swapTreasures(treasures[i], treasures[j]);
            }
        }
    }
}

void TreasureMap::sortByDistance()
{
    for (int i = 0; i < amountOfTreasures - 1; ++i)
    {
        for (int j = i + 1; j < amountOfTreasures; ++j)
        {
            if (treasures[i].findDistanceFrom0() > treasures[j].findDistanceFrom0())
            {
                swapTreasures(treasures[i], treasures[j]);
            }
        }
    }
}

void TreasureMap::print()const
{
    for (int i = 0; i < amountOfTreasures; ++i)
    {
        treasures[i].print();
        std::cout << std::endl;
    }
}

Treasure TreasureMap::getMostValuable() const
{
    if (amountOfTreasures == 0) return {};
    int mostValuable = 0;
    int index = 0;
    for (int i = 0; i < amountOfTreasures; ++i)
    {
        if (treasures[i].getValue() > mostValuable)
        {
            mostValuable = treasures[i].getValue();
            index = i;
        }
    }
    return treasures[index];
}

bool TreasureMap::saveToFile(const char* FILE_NAME) const {
    std::ofstream ofs(FILE_NAME);
    if (!ofs.is_open()) return false;

    ofs << amountOfTreasures << std::endl;
    for (size_t i = 0; i < amountOfTreasures; ++i) {
        ofs << treasures[i].getName() << " "
            << treasures[i].getX() << " "
            << treasures[i].getY() << " "
            << treasures[i].getValue() << "\n";
    }
    ofs.close();
    return true;
}

bool TreasureMap::readFromFile(const char* FILE_NAME) {
    std::ifstream ifs(FILE_NAME);
    if (!ifs.is_open()) return false;
    size_t count;
    if (!(ifs >> count)) return false;
    amountOfTreasures = 0;
    for (size_t i = 0; i < count; ++i) {
        char tempName[constants::MAX_TRESURE_NAME_LEN + 1];
        int tx, ty, tval;

        if (ifs >> tempName >> tx >> ty >> tval) {
            Treasure temp(tempName, tx, ty, tval);
            addTreasure(temp);
        }
    }
    ifs.close();
    return true;
}


