#include "NumberSeries.h"
#include "Validations.h"
#include "Constants.h"
#include <iostream>

void NumberSeries::grow() {
    int  newCap = (m_capacity == 0) ? Constants::INITIAL_CAPACITY : m_capacity * Constants::GROWTH_FACTOR;
    int* newArr = new int[newCap];
    for (int i = 0; i < m_cacheSize; ++i)
        newArr[i] = m_cache[i];
    delete[] m_cache;
    m_cache = newArr;
    m_capacity = newCap;
}

void NumberSeries::resetCache() {
    delete[] m_cache;
    m_cache = new int[Constants::INITIAL_CAPACITY];
    m_capacity = Constants::INITIAL_CAPACITY;
    m_cacheSize = 0;
    m_cache[0] = m_startValue;
    m_cacheSize = 1;
}

void NumberSeries::copyFrom(const NumberSeries& other) {
    m_startValue = other.m_startValue;
    m_func = other.m_func;
    m_cacheSize = other.m_cacheSize;
    m_capacity = other.m_capacity;
    m_cache = new int[m_capacity];
    for (int i = 0; i < m_cacheSize; ++i)
        m_cache[i] = other.m_cache[i];
}

void NumberSeries::free() {
    delete[] m_cache;
}

NumberSeries::NumberSeries(int startValue, int (*func)(int))
    : m_startValue(startValue), m_func(func),
    m_cache(nullptr), m_cacheSize(0), m_capacity(0)
{
    if (!func) {
        std::cout << "Error: Transition function must not be null!\n";
        return;
    }
    resetCache();
}

NumberSeries::NumberSeries(const NumberSeries& other)
    : m_cache(nullptr), m_cacheSize(0), m_capacity(0)
{
    copyFrom(other);
}

NumberSeries& NumberSeries::operator=(const NumberSeries& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

NumberSeries::~NumberSeries() {
    free();
}

int NumberSeries::get(int index) {
    if (!Validations::isValidIndex(index)) {
        std::cout << "Error: Index must be >= 0!\n";
        return -1;
    }

    if (index < m_cacheSize)
        return m_cache[index];

    for (int i = m_cacheSize; i <= index; ++i) {
        if (m_cacheSize == m_capacity) grow();
        m_cache[m_cacheSize] = m_func(m_cache[m_cacheSize - 1]);
        ++m_cacheSize;
    }
    return m_cache[index];
}

bool NumberSeries::contains(int value) {
    for (int i = 0; i < m_cacheSize; ++i)
        if (m_cache[i] == value) return true;

    const int MAX_STEPS = 100000;
    int steps = 0;

    while (steps < MAX_STEPS) {
        int prev = m_cache[m_cacheSize - 1];
        int next = m_func(prev);

        if (m_cacheSize == m_capacity) grow();
        m_cache[m_cacheSize++] = next;

        if (next == value)      return true;
        if (next == m_cache[0]) return false;

        ++steps;
    }
    return false;
}

void NumberSeries::setStartValue(int startValue) {
    m_startValue = startValue;
    resetCache();
}

void NumberSeries::setTransitionFunc(int (*func)(int)) {
    if (!func) {
        std::cout << "Error: Transition function must not be null!\n";
        return;
    }
    m_func = func;
    resetCache();
}