#pragma once

class Treasure
{
private:
    char name[33];
    int x;
    int y;
    int value;

public:
    Treasure();
    Treasure(const char* name, int x, int y, int value);

    const char* getName() const;
    int getX() const;
    int getY() const;
    int getValue() const;

    double distanceFromOrigin() const;

    void print() const;
};

