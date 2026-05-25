#include "Validations.h"

bool Validations::isValidBase(int base) {
    return base >= 2 && base <= 36;
}
bool isValidDigit(char c, int base) {
    int value;
    if (c >= '0' && c <= '9')
        value = c - '0';
    else if (c >= 'A' && c <= 'Z')
        value = c - 'A' + 10;
    else if (c >= 'a' && c <= 'z')
        value = c - 'a' + 10;
    else
        return false;

    return value < base;
}

bool Validations::isValidNumber(const char* digits, int base) {
    if (digits == nullptr || digits[0] == '\0')
        return false;

    for (int i = 0; digits[i] != '\0'; ++i) {
        if (!isValidDigit(digits[i], base))
            return false;
    }
    return true;
}

bool Validations::isValidLength(const char* digits) {
    int len = 0;
    while (digits[len] != '\0')
        len++;
    return len >= 1 && len <= 64;
}