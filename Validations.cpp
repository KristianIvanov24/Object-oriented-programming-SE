#include "Validations.h"
#include "Constants.h"
#include <cstring>

bool Validations::isValidName(const char* name) {
    if (name == nullptr || name[0] == '\0') {
        return false;
    }
    int len = strlen(name);
    if (len > Constants::MAX_NAME_LEN) {
        return false;
    }
    return true;
}

bool Validations::isValidValue(int value) {
    return value >= 0;
}

bool Validations::isValidCoordinates(int x, int y) {
    return x >= -10000 && x <= 10000 &&
        y >= -10000 && y <= 10000;
}

bool Validations::isValidCount(int count) {
    return count >= 0 && count <= Constants::MAX_TREASURES;
}