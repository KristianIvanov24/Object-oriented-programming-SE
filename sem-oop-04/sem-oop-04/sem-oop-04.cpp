#include <iostream>
#include "KBaseNumber.h"
#include "TreasureMap.h"

int main() {
    TreasureMap map;
    Treasure t1("GoldChest", 10, 5, 500);
    Treasure t2("AncientCoin", -3, 7, 200);
    Treasure t3("SilverRing", 2, 1, 150);;
    map.addTreasure(t1);
    map.addTreasure(t2);
    map.addTreasure(t3);

    map.print();
    /*
    GoldChest (10,5) value:500
    AncientCoin (-3,7) value:200
    SilverRing (2,1) value:150
    */

    map.sortByValue();
    map.print();

    Treasure t = map.getMostValuable();
    std::cout << t.getName() << std::endl; // GoldChest

    map.saveToFile("map.txt");

    TreasureMap map2;
    map2.readFromFile("map.txt");
    map2.print();
}