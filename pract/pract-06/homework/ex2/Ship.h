#pragma once

#include <cstdio>
#include "ShipClass.h"

class Ship {
 static size_t id;
 char* name;
 unsigned year;
 ShipClass type;
 unsigned numberOfGuns;

 void free();
 void copyFrom(const Ship& other);
 void setName();
 const char* typeToString() const;
 const char* intToString(unsigned) const;

public:
 Ship();
 Ship(unsigned, ShipClass, unsigned);
 Ship(const Ship&);
 Ship& operator=(const Ship&);
 ~Ship();

 void setYear(unsigned);
 void setType(ShipClass);
 void setNumberOfGuns(unsigned);

 const char* getName() const;
 unsigned getYear() const;
 ShipClass getType() const;
 unsigned getNumberOfGuns() const;
};