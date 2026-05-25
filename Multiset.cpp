#include "MultiSet.h"
#include "Validations.h"
#include <iostream>
#include <fstream>
#include <cstring>

int MultiSet::maxCount() const {
    return (1 << m_k) - 1; 
}

int MultiSet::getCount(int number) const {
    int result = 0;
    int bitStart = number * m_k;

    for (int b = 0; b < m_k; ++b) {
        int bitPos = bitStart + b;
        int byteIdx = bitPos / 8;
        int bitIdx = bitPos % 8;

        if (m_data[byteIdx] & (1 << bitIdx))
            result |= (1 << b);
    }
    return result;
}

void MultiSet::setCount(int number, int count) {
    int bitStart = number * m_k;

    for (int b = 0; b < m_k; ++b) {
        int bitPos = bitStart + b;
        int byteIdx = bitPos / 8;
        int bitIdx = bitPos % 8;

        if (count & (1 << b))
            m_data[byteIdx] |= (1 << bitIdx);
        else
            m_data[byteIdx] &= ~(1 << bitIdx);
    }
}

void MultiSet::copyFrom(const MultiSet& other) {
    m_n = other.m_n;
    m_k = other.m_k;
    m_dataSize = other.m_dataSize;
    m_data = new unsigned char[m_dataSize];
    for (int i = 0; i < m_dataSize; ++i)
        m_data[i] = other.m_data[i];
}

void MultiSet::free() {
    delete[] m_data;
}

MultiSet::MultiSet(int n, int k)
    : m_n(n), m_k(k), m_data(nullptr)
{
    if (!Validations::isValidN(n)) 
    {
        std::cout << "n must be >= 0. n set to 0.";
        n = 0;
    }
    if (!Validations::isValidK(k)) 
    {
        std::cout << "k must be between 1 and 8. k set to 1.";
        k = 1;
    }

    int totalBits = (n + 1) * k;
    m_dataSize = (totalBits + 7) / 8;
    m_data = new unsigned char[m_dataSize];
    memset(m_data, 0, m_dataSize);
}

MultiSet::MultiSet(const MultiSet& other) : m_data(nullptr) {
    copyFrom(other);
}

MultiSet& MultiSet::operator=(const MultiSet& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

MultiSet::~MultiSet() {
    free();
}

void MultiSet::add(int number) {
    if (!Validations::isValidNumber(number, m_n))
    {
        std::cout<<"Number out of range [0, n]. Number set to 0.";
        number = 0;
    }

    int current = getCount(number);
    if (current < maxCount())
        setCount(number, current + 1);
}

int MultiSet::count(int number) const {
    if (!Validations::isValidNumber(number, m_n))
    {
        std::cout << "Number out of range [0, n]. Number set to 0.";
        number = 0;
    }
    return getCount(number);
}

void MultiSet::print() const {
    std::cout << "{ ";
    for (int i = 0; i <= m_n; ++i) {
        int c = getCount(i);
        for (int j = 0; j < c; ++j)
            std::cout << i << " ";
    }
    std::cout << "}\n";
}

void MultiSet::printMemory() const {
    std::cout << "Memory (" << m_dataSize << " bytes): ";
    for (int i = 0; i < m_dataSize; ++i) {
        for (int b = 7; b >= 0; --b)
            std::cout << ((m_data[i] >> b) & 1);
        std::cout << " ";
    }
    std::cout << "\n";
}

void MultiSet::serialize(const char* filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Cannot open file for writing";
        return;
    }

    file << m_n << "\n";
    file << m_k << "\n";
    file << m_dataSize << "\n";
    for (int i = 0; i < m_dataSize; ++i)
        file << (int)m_data[i] << "\n";
}

MultiSet MultiSet::deserialize(const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Cannot open file for reading";
        return MultiSet(0, 1);
    }

    int n, k, dataSize;
    file >> n >> k >> dataSize;

    MultiSet ms(n, k);
    for (int i = 0; i < dataSize; ++i) {
        int byte;
        file >> byte;
        ms.m_data[i] = (unsigned char)byte;
    }
    return ms;
}

MultiSet MultiSet::intersection(const MultiSet& other) const {
    if (m_n != other.m_n || m_k != other.m_k) {
        std::cout << "MultiSets must have same n and k";
        return MultiSet(0, 1);
    }

    MultiSet result(m_n, m_k);
    for (int i = 0; i <= m_n; ++i) {
        int a = getCount(i);
        int b = other.getCount(i);
        result.setCount(i, a < b ? a : b);
    }
    return result;
}

MultiSet MultiSet::difference(const MultiSet& other) const {
    if (m_n != other.m_n || m_k != other.m_k) {
        std::cout << "MultiSets must have same n and k";
        return MultiSet(0, 1);
    }

    MultiSet result(m_n, m_k);
    for (int i = 0; i <= m_n; ++i) {
        int a = getCount(i);
        int b = other.getCount(i);
        int diff = a - b;
        result.setCount(i, diff > 0 ? diff : 0);
    }
    return result;
}

MultiSet MultiSet::complement() const {
    MultiSet result(m_n, m_k);
    int max = maxCount();
    for (int i = 0; i <= m_n; ++i)
        result.setCount(i, max - getCount(i));
    return result;
}