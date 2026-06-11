#pragma once

#include <iostream>

class MultiSet
{
    size_t n;
    unsigned k;
    size_t size;
    uint8_t *numbers;

    void free();
    void copyFrom(const MultiSet &);

    size_t getArrayIndex(unsigned) const;
    unsigned getBitIndex(unsigned) const;
    uint16_t getData(unsigned) const;
    void setCount(unsigned, unsigned);

public:
    MultiSet(size_t, unsigned);
    MultiSet(const MultiSet &);
    MultiSet &operator=(const MultiSet &);
    ~MultiSet();

    void insert(unsigned);
    unsigned count(unsigned) const;
    void print() const;
    void printMemoryRepresentation() const;
    void serialize(std::ofstream &) const;
    void deserialize(std::ifstream &);

    static MultiSet intersection(const MultiSet &, const MultiSet &);
    static MultiSet difference(const MultiSet &, const MultiSet &);
    static MultiSet complement(const MultiSet &);
};