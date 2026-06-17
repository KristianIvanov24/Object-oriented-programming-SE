#pragma once
#include <string>

class Ship {
public:
    enum class ShipClass { BB, BC };

    Ship(int launchYear, ShipClass shipClass, int numberOfGuns);

    const std::string& getName() const;
    int getLaunchYear() const;
    ShipClass getShipClass() const;
    int getNumberOfGuns() const;

    void setLaunchYear(int year);
    void setShipClass(ShipClass sc);
    void setNumberOfGuns(int guns);

private:
    static unsigned s_nextId;

    std::string m_name;
    int m_launchYear;
    ShipClass m_shipClass;
    int m_numberOfGuns;

    static std::string intToStr(unsigned n);
    static std::string buildName(ShipClass sc, int guns, unsigned id);
};
