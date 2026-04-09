#include "Bitset.h"
#include <cstdint>
#include <iostream>

Bitset::Bitset(unsigned n) {
    this->maxN = n;
    this->bucketsCount = n / elementsInBucket + 1;
    this->data = new uint8_t[this->bucketsCount]{};
}

void Bitset::free() {
    delete[] data;
    maxN = bucketsCount = 0;
}

void Bitset::copyFrom(const Bitset &other) {
    maxN = other.maxN;
    bucketsCount = other.bucketsCount;

    data = new uint8_t[bucketsCount];

    for (int i = 0; i < bucketsCount; i++) {
        data[i] = other.data[i];
    }
}

Bitset::Bitset(const Bitset &other) { copyFrom(other); }

Bitset &Bitset::operator=(const Bitset &other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

Bitset::~Bitset() { free(); }

unsigned Bitset::getBucketIndex(unsigned n) const {
    return n / elementsInBucket;
}

unsigned Bitset::getBitIndex(unsigned n) const { return n % elementsInBucket; }

bool Bitset::contains(unsigned n) const {
    if (n > maxN) {
        return false;
    }

    unsigned bucketIndex = getBucketIndex(n);
    unsigned bitIndex = getBitIndex(n);

    uint8_t mask = 1 << bitIndex;

    return data[bucketIndex] & mask;
}

unsigned Bitset::getN() const { return maxN; }

void Bitset::add(unsigned n) {
    if (n > maxN) {
        return;
    }

    unsigned bucketIndex = getBucketIndex(n);
    unsigned bitIndex = getBitIndex(n);

    uint8_t mask = 1 << bitIndex;

    data[bucketIndex] |= mask;
}

void Bitset::remove(unsigned n) {
    if (n > maxN) {
        return;
    }

    unsigned bucketIndex = getBucketIndex(n);
    unsigned bitIndex = getBitIndex(n);

    uint8_t mask = 1 << bitIndex;

    data[bucketIndex] &= (~mask);
}

void Bitset::print() const {
    std::cout << "{ ";

    for (unsigned i = 0; i <= maxN; i++) {
        if (contains(i)) {
            std::cout << i << " ";
        }
    }

    std::cout << "}";
}

Bitset Bitset::unionSets(const Bitset &lhs, const Bitset &rhs) {
    Bitset res(std::max(lhs.getN(), rhs.getN()));

    unsigned minBucketsCount = std::min(lhs.bucketsCount, rhs.bucketsCount);

    for (unsigned i = 0; i < minBucketsCount; i++) {
        res.data[i] = lhs.data[i] | rhs.data[i];
    }

    const Bitset &bigger = lhs.getN() > rhs.getN() ? lhs : rhs;

    for (unsigned i = minBucketsCount; i < bigger.bucketsCount; i++) {
        res.data[i] = bigger.data[i];
    }

    return res;
}

// алтернативна версия на unionSets
Bitset Bitset::unionSets(const Bitset &lhs, const Bitset &rhs) {
    const Bitset &bigger  = lhs.getN() > rhs.getN() ? lhs : rhs;
    const Bitset &smaller = lhs.getN() > rhs.getN() ? rhs : lhs;

    Bitset res(bigger);
    for (unsigned i = 0; i < smaller.bucketsCount; i++) {
        res.data[i] |= smaller.data[i];
    }
    return res;
}

Bitset Bitset::intersection(const Bitset &lhs, const Bitset &rhs) {
    Bitset res(std::min(lhs.getN(), rhs.getN()));

    for (unsigned i = 0; i < res.bucketsCount; i++) {
        res.data[i] = lhs.data[i] & rhs.data[i];
    }

    return res;
}
