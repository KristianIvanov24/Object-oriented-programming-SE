#pragma warning(disable : 4996)
#include "SpecialCustomFunction.h"
#include <cstring>

SpecialCustomFunction::SpecialCustomFunction(int* arr, int size, int(*f)(int)) {
    count = size;
    func = f;
    specialValues = new int[count];
    for (int i = 0; i < count; i++)
        specialValues[i] = arr[i];
}

SpecialCustomFunction::SpecialCustomFunction(const SpecialCustomFunction& other) {
    count = other.count;
    func = other.func;
    specialValues = new int[count];
    for (int i = 0; i < count; i++)
        specialValues[i] = other.specialValues[i];
}

SpecialCustomFunction& SpecialCustomFunction::operator=(const SpecialCustomFunction& other) {
    if (this != &other) {
        delete[] specialValues;
        count = other.count;
        func = other.func;
        specialValues = new int[count];
        for (int i = 0; i < count; i++)
            specialValues[i] = other.specialValues[i];
    }
    return *this;
}

SpecialCustomFunction::~SpecialCustomFunction() {
    delete[] specialValues;
}

int SpecialCustomFunction::operator()(int value) const {
    for (int i = 0; i < count; i++)
        if (specialValues[i] == value)
            return value * value;
    return func(value);
}

SpecialCustomFunction& SpecialCustomFunction::operator++() {
    for (int i = 0; i < count; i++)
        specialValues[i]++;
    return *this;
}


SpecialCustomFunction& SpecialCustomFunction::operator--() {
    for (int i = 0; i < count; i++)
        specialValues[i]--;
    return *this;
}

SpecialCustomFunction SpecialCustomFunction::operator++(int) {
    SpecialCustomFunction old = *this;
    ++(*this);
    return old;
}


SpecialCustomFunction SpecialCustomFunction::operator--(int) {
    SpecialCustomFunction old = *this;
    --(*this);
    return old;
}

SpecialCustomFunction SpecialCustomFunction::operator!() const {
    SpecialCustomFunction result = *this;
    for (int i = 0; i < result.count; i++)
        result.specialValues[i] = -result.specialValues[i];
    return result;
}