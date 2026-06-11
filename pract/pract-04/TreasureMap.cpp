#include "TreasureMap.h"
#include <iostream>
#include <fstream>
#include <cstring>

TreasureMap::TreasureMap()
{
    count = 0;
}

bool TreasureMap::addTreasure(const Treasure& t)
{
    if (count >= 50)
        return false;

    treasures[count++] = t;
    return true;
}

bool TreasureMap::removeTreasure(const char* name)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(treasures[i].getName(), name) == 0)
        {
            for (int j = i; j < count - 1; j++)
                treasures[j] = treasures[j + 1];

            count--;
            return true;
        }
    }
    return false;
}

Treasure* TreasureMap::findByCoordinates(int x, int y)
{
    for (int i = 0; i < count; i++)
    {
        if (treasures[i].getX() == x && treasures[i].getY() == y)
            return &treasures[i];
    }
    return nullptr;
}

void TreasureMap::sortByValue()
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (treasures[i].getValue() > treasures[j].getValue())
            {
                Treasure temp = treasures[i];
                treasures[i] = treasures[j];
                treasures[j] = temp;
            }
        }
    }
}

void TreasureMap::sortByDistance()
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (treasures[i].distanceFromOrigin() >
                treasures[j].distanceFromOrigin())
            {
                Treasure temp = treasures[i];
                treasures[i] = treasures[j];
                treasures[j] = temp;
            }
        }
    }
}

void TreasureMap::printAll() const
{
    for (int i = 0; i < count; i++)
        treasures[i].print();
}

Treasure* TreasureMap::findMostValuable()
{
    if (count == 0)
        return nullptr;

    int index = 0;

    for (int i = 1; i < count; i++)
    {
        if (treasures[i].getValue() > treasures[index].getValue())
            index = i;
    }

    return &treasures[index];
}

void TreasureMap::saveToFile(const char* filename) const
{
    std::ofstream out(filename);

    out << count << std::endl;

    for (int i = 0; i < count; i++)
    {
        out << treasures[i].getName() << " "
            << treasures[i].getX() << " "
            << treasures[i].getY() << " "
            << treasures[i].getValue() << std::endl;
    }

    out.close();
}

void TreasureMap::loadFromFile(const char* filename)
{
    std::ifstream in(filename);

    in >> count;

    char name[33];
    int x, y, value;

    for (int i = 0; i < count; i++)
    {
        in >> name >> x >> y >> value;
        treasures[i] = Treasure(name, x, y, value);
    }

    in.close();
}
