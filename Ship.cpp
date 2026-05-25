#include "Ship.h"
#include <iostream>

unsigned Ship::s_nextId = 1;

std::string Ship::intToStr(unsigned n) {
    if (n == 0) return "0";

    std::string result = "";

    while (n > 0) {
        result = (char)('0' + n % 10) + result;
        n /= 10;
    }


    return result;
}

std::string Ship::buildName(ShipClass sc, int guns, unsigned id) {
    std::string type = (sc == ShipClass::BB ? "bb" : "bc");
    return "ship-" + type + "-" + Ship::intToStr(guns) + "-" + Ship::intToStr(id);
}

Ship::Ship(int launchYear, ShipClass shipClass, int numberOfGuns)
    : m_launchYear(launchYear),
    m_shipClass(shipClass),
    m_numberOfGuns(numberOfGuns)
{
    if (numberOfGuns < 0)
    {
        std::cout << "The number of guns must be >= 0! Number of guns set to 0.";
        numberOfGuns = 0;
    }

    unsigned id = s_nextId++;
    m_name = buildName(shipClass, numberOfGuns, id);
}


const std::string& Ship::getName() const { return m_name; }
int Ship::getLaunchYear() const { return m_launchYear; }
Ship::ShipClass Ship::getShipClass() const { return m_shipClass; }
int Ship::getNumberOfGuns() const { return m_numberOfGuns; }


void Ship::setLaunchYear(int year) { m_launchYear = year; }
void Ship::setShipClass(ShipClass sc) { m_shipClass = sc; }
void Ship::setNumberOfGuns(int guns) {
    if (guns < 0) {
        std::cout << "The number of guns must be >= 0! Number of guns set to 0.";
        m_numberOfGuns = 0;
    }
    else m_numberOfGuns = guns;
}
