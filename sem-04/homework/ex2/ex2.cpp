#include <iostream>
#include "Treasure.h"
#include "TreasureMap.h"

int main()
{
    TreasureMap map;

    map.addTreasure("GoldChest", 10, 5, 500);
    map.addTreasure("AncientCoin", -3, 7, 200);
    map.addTreasure("SilverRing", 2, 1, 150);

    map.print();

    map.sortByValue();
    map.print();

    Treasure t = map.getMostValuable();
    std::cout << t.getName() << std::endl;

    map.saveToFile("map.txt");

    TreasureMap map2;
    map2.readFromFile("map.txt");
    map2.print();

    return 0;
}