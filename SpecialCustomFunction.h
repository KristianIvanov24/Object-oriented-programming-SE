#pragma once

class SpecialCustomFunction {
private:
    int* specialValues;
    int count;
    int(*func)(int);

public:
    SpecialCustomFunction(int* arr, int size, int(*f)(int));
    SpecialCustomFunction(const SpecialCustomFunction& other);
    SpecialCustomFunction& operator=(const SpecialCustomFunction& other);
    ~SpecialCustomFunction();

    int operator()(int value) const;

    SpecialCustomFunction& operator++();
    SpecialCustomFunction& operator--();

    SpecialCustomFunction operator++(int);
    SpecialCustomFunction operator--(int);


    SpecialCustomFunction operator!() const;
};