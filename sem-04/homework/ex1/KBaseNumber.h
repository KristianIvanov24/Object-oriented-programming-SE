#pragma once

#include <fstream>

namespace constants
{
    const size_t MAX_NUM_LEN = 64;
};

namespace char_ops
{
    unsigned charToNumber(char);
    char numberToChar(unsigned);
}

class KBaseNumber
{
    char number[constants::MAX_NUM_LEN + 1];
    unsigned base;

    unsigned toDecimal() const;
    KBaseNumber toBase(unsigned) const;

public:
    KBaseNumber();
    KBaseNumber(const char *, unsigned);

    void setNumber(const char *);
    void setBase(unsigned);

    void printConvertedTo(unsigned) const;
    int compareWith(const KBaseNumber &) const;
    void update(const char *, unsigned);
    void print() const;

    void saveToFile(std::ofstream&) const;
    void readFromFile(std::ifstream&);
};