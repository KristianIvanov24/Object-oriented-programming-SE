#pragma once

#include <iostream>

class NumberSeries
{
    int a0;
    int (*f)(int);
    int *numbers;
    size_t size;
    size_t capacity;

    void free();
    void copyFrom(const NumberSeries &);
    void generateNumbers(size_t);
    void resize();

public:
    NumberSeries(int, int (*f)(int));
    NumberSeries(const NumberSeries &);
    NumberSeries &operator=(const NumberSeries &);
    ~NumberSeries();

    int getAi(size_t);
    bool isFromNumberSeries(int);
    void setNewNumberSeries(int, int (*f)(int));
};