#pragma once

class Validations {
public:
    static bool isValidName(const char* name);
    static bool isValidValue(int value);
    static bool isValidCoordinates(int x, int y);
    static bool isValidCount(int count);
};