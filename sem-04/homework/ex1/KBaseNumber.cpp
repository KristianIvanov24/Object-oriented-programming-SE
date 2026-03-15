#include "KBaseNumber.h"
#include <iostream>
#include <algorithm>

namespace char_ops
{
    unsigned charToNumber(char c)
    {
        if (c >= '0' && c <= '9')
            return c - '0';
        if (c >= 'A' && c <= 'Z')
            return c - 'A' + 10;
        return 0;
    }

    char numberToChar(unsigned number)
    {
        if (number <= 9)
            return number + '0';
        if (number <= 35)
            return number + 'A' - 10;
        return '?';
    }
}


unsigned KBaseNumber::toDecimal() const {
    unsigned convertedNumber = 0;
    size_t len = strlen(number);

    for (size_t i = 0; i < len; i++) {
        convertedNumber = convertedNumber * base + char_ops::charToNumber(number[i]);
    }

    return convertedNumber;
}

KBaseNumber KBaseNumber::toBase(const unsigned k) const {
    KBaseNumber convertedNumber;
    convertedNumber.setBase(k);

    unsigned decimal = toDecimal();
    if (decimal == 0) {
        strcpy(convertedNumber.number, "0");
        return convertedNumber;
    }

    size_t i = 0;
    while (decimal) {
        convertedNumber.number[i++] = char_ops::numberToChar(decimal % k);
        decimal /= k;
    }

    convertedNumber.number[i] = '\0';
    std::reverse(convertedNumber.number, convertedNumber.number + i);

    return convertedNumber;
}

KBaseNumber::KBaseNumber() : base(10) {
    setNumber("");
}

KBaseNumber::KBaseNumber(const char *number, unsigned k) : base(k) {
    setNumber(number);
}

void KBaseNumber::setNumber(const char *number) {
    if (strlen(number) > constants::MAX_NUM_LEN) {
        strcpy(this->number, "");
        return;
    }

    for (size_t i = 0; i < strlen(number); i++) {
        if (char_ops::charToNumber(number[i]) >= base) {
            strcpy(this->number, "");
            return;
        }
    }

    strncpy(this->number, number, constants::MAX_NUM_LEN + 1);
    this->number[constants::MAX_NUM_LEN] = '\0';
}

void KBaseNumber::setBase(unsigned k) {
    this->base = k;
}

void KBaseNumber::printConvertedTo(unsigned k) const {
    KBaseNumber convertedNumber = toBase(k);
    convertedNumber.print();
}

int KBaseNumber::compareWith(const KBaseNumber &other) const {
    unsigned decimal = toDecimal();
    unsigned otherDecimal = other.toDecimal();

    if (decimal > otherDecimal) {
        return 1;
    } else if (decimal < otherDecimal) {
        return -1;
    } else {
        return 0;
    }
}

void KBaseNumber::update(const char *newNumber, unsigned newK) {
    setBase(newK);
    setNumber(newNumber);
}

void KBaseNumber::print() const {
    std::cout << number << "(" << base << ")" << std::endl;
}

void KBaseNumber::saveToFile(std::ofstream& file) const {
    file.write((const char *) this, sizeof(KBaseNumber));
}

void KBaseNumber::readFromFile(std::ifstream& file) {
    file.read((char *) this, sizeof(KBaseNumber));
}