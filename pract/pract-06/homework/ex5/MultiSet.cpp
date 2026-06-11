#include "MultiSet.h"
#include "constants.h"

#include <fstream>
#include <algorithm>
#include <iostream>

using namespace constants;

void MultiSet::free()
{
    n = 0;
    k = 0;
    size = 0;
    delete[] numbers;
    numbers = nullptr;
}

void MultiSet::copyFrom(const MultiSet &other)
{
    n = other.n;
    k = other.k;
    size = other.size;
    numbers = new uint8_t[size];
    std::copy(other.numbers, other.numbers + size, numbers);
}

size_t MultiSet::getArrayIndex(unsigned number) const
{
    return (number * k) / BITS_IN_BYTE;
}

unsigned MultiSet::getBitIndex(unsigned number) const
{
    return (number * k) % BITS_IN_BYTE;
}

uint16_t MultiSet::getData(unsigned number) const
{
    size_t index = getArrayIndex(number);

    uint16_t data = numbers[index];
    if (index + 1 < size)
    {
        data |= numbers[index + 1] << BITS_IN_BYTE;
    }
    return data;
}

void MultiSet::setCount(unsigned number, unsigned countMask)
{
    size_t index = getArrayIndex(number);
    unsigned startBit = getBitIndex(number);
    uint16_t data = getData(number);

    uint8_t bucketMask = (1 << k) - 1;
    data &= ~(bucketMask << startBit);
    data |= countMask << startBit;

    uint8_t byteMask = (1 << BITS_IN_BYTE) - 1;
    numbers[index] = data & byteMask;
    if (index + 1 < size)
    {
        numbers[index + 1] = (data >> BITS_IN_BYTE) & byteMask;
    }
}

MultiSet::MultiSet(size_t n, unsigned k)
{
    this->n = n;
    this->k = k;
    size = (n * k + (BITS_IN_BYTE - 1)) / BITS_IN_BYTE;
    numbers = new uint8_t[size]{};
}

MultiSet::MultiSet(const MultiSet &other)
{
    copyFrom(other);
}

MultiSet &MultiSet::operator=(const MultiSet &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

MultiSet::~MultiSet()
{
    free();
}

void MultiSet::insert(unsigned number)
{
    if (number >= n)
    {
        return;
    }

    unsigned countMask = count(number);
    if (countMask >= (1 << k) - 1)
    {
        return;
    }

    countMask++;
    setCount(number, countMask);
}

unsigned MultiSet::count(unsigned number) const
{
    if (number >= n)
    {
        return 0;
    }

    unsigned startBit = getBitIndex(number);
    uint16_t data = getData(number);

    uint8_t bucketMask = (1 << k) - 1;
    return (data >> startBit) & bucketMask;
}

void MultiSet::print() const
{
    for (size_t number = 0; number < n; number++)
    {
        for (unsigned k = 0; k < count(number); k++)
        {
            std::cout << number << " ";
        }
    }
    std::cout << std::endl;
}

void MultiSet::printMemoryRepresentation() const
{
    for (size_t i = 0; i < size; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            size_t bitIndex = i * BITS_IN_BYTE + ((BITS_IN_BYTE - 1) - j);
            if (bitIndex % k == 0 && bitIndex / k < n)
            {
                std::cout << " | ";
            }
            std::cout << ((numbers[i] >> j) & 1);
        }
    }
}

void MultiSet::serialize(std::ofstream &out) const
{
    out.write((const char *)&n, sizeof(n));
    out.write((const char *)&k, sizeof(k));
    out.write((const char *)&size, sizeof(size));
    out.write((const char *)numbers, size);
}

void MultiSet::deserialize(std::ifstream &in)
{
    in.read((char *)&n, sizeof(n));
    in.read((char *)&k, sizeof(k));
    in.read((char *)&size, sizeof(size));
    delete[] numbers;
    numbers = new uint8_t[size]{};
    in.read((char *)numbers, size);
}

MultiSet MultiSet::intersection(const MultiSet &a, const MultiSet &b)
{
    MultiSet res(std::min(a.n, b.n), std::min(a.k, b.k));

    for (size_t number = 0; number < res.n; number++)
    {
        unsigned countMask = std::min(a.count(number), b.count(number));
        res.setCount(number, countMask);
    }

    return res;
}

MultiSet MultiSet::difference(const MultiSet &a, const MultiSet &b)
{
    MultiSet res(a.n, a.k);

    for (size_t number = 0; number < a.n; number++)
    {
        unsigned bCount = number < b.n ? b.count(number) : 0;
        unsigned countMask = std::max(0, (int)(a.count(number) - bCount));
        res.setCount(number, countMask);
    }
    return res;
}

MultiSet MultiSet::complement(const MultiSet &a)
{
    MultiSet res(a.n, a.k);

    for (size_t number = 0; number < res.n; number++)
    {
        unsigned countMask = a.count(number);
        countMask = (1 << a.k) - 1 - countMask;
        res.setCount(number, countMask);
    }

    return res;
}