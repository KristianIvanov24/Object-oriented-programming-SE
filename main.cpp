#include <iostream>
#include "Ship.h"
#include "Navy.h"

int main() {

    Ship s1(1916, Ship::ShipClass::BB, 8);
    Ship s2(1918, Ship::ShipClass::BC, 6);
    Ship s3(1915, Ship::ShipClass::BB, 12);

    std::cout << "Ship names:\n";
    std::cout << "  " << s1.getName() << "  (guns: " << s1.getNumberOfGuns() << ")\n";
    std::cout << "  " << s2.getName() << "  (guns: " << s2.getNumberOfGuns() << ")\n";
    std::cout << "  " << s3.getName() << "  (guns: " << s3.getNumberOfGuns() << ")\n\n";


    Navy britishNavy("Britain");
    britishNavy.addShip(s1);
    britishNavy.addShip(s2);

    Navy germanNavy("Germany");
    germanNavy.addShip(s3);

    std::cout << "British navy ships: " << britishNavy.getShipCount() << "\n";
    std::cout << "German  navy ships: " << germanNavy.getShipCount() << "\n\n";

    int cmp = britishNavy.compareFirepower(germanNavy);
    if (cmp == -1) std::cout << "Britain has LESS firepower.\n";
    else if (cmp == 1) std::cout << "Britain has MORE firepower.\n";
    else std::cout << "Equal firepower.\n";

    return 0;
}
