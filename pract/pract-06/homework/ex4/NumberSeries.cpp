#include "NumberSeries.h"
#include "constants.h"

using namespace constants;

void NumberSeries::free()
{ 
    delete[] numbers;
    numbers = nullptr;
    a0 = 0;
    f = nullptr;
    capacity = 0;
    size = 0;
}

void NumberSeries::copyFrom(const NumberSeries &other)
{
    a0 = other.a0;
    f = other.f;
    capacity = other.capacity;
    size = other.size;

    if (!other.numbers)
    {
        numbers = nullptr;
        return;
    }

    numbers = new int[other.capacity];
    std::copy(other.numbers, other.numbers + other.size, numbers);
}

void NumberSeries::generateNumbers(size_t index)
{
    while (index >= capacity)
    {
        resize();
    }

    size_t start = size;
    int prev = (size == 0) ? a0 : numbers[size - 1];

    for (size_t i = start; i <= index; i++)
    {
        if (i == 0)
        {
            numbers[0] = a0;
            continue;
        }
        numbers[i] = f(prev);
        prev = numbers[i];
    }
    size = index + 1;
}

void NumberSeries::resize()
{
    size_t newCapacity = capacity == 0 ? 1 : capacity * 2;
    int *newNumbers = new int[newCapacity]{};
    std::copy(numbers, numbers + size, newNumbers);

    delete[] numbers;
    numbers = newNumbers;
    capacity = newCapacity;
}

NumberSeries::NumberSeries(int a0, int (*f)(int))
{
    this->a0 = a0;
    this->f = f;
    capacity = STARTING_CAPACITY;
    size = DEFAULT_MIN;
    numbers = new int[capacity]{};
}

NumberSeries::NumberSeries(const NumberSeries &other) 
    : numbers(nullptr), capacity(DEFAULT_MIN), size(DEFAULT_MIN), f(nullptr), a0(DEFAULT_MIN)
{
    copyFrom(other);
}

NumberSeries &NumberSeries::operator=(const NumberSeries &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

NumberSeries::~NumberSeries()
{
    free();
}

int NumberSeries::getAi(size_t i)
{
    if (i >= size)
    {
        generateNumbers(i);
    }
    return numbers[i];
}

bool NumberSeries::isFromNumberSeries(int a)
{
    while (size == 0 || numbers[size - 1] < a)
    {
        generateNumbers(size == 0 ? 0 : size * 2);
    }

    size_t left = 0, right = size - 1;
    while (left <= right)
    {
        size_t mid = left + (right - left) / 2;
        if (numbers[mid] < a)
        {
            left = mid + 1;
        }
        else if (numbers[mid] > a)
        {
            right = mid - 1;
        }
        else
        {
            return true;
        }
    }
    return false;
}

void NumberSeries::setNewNumberSeries(int a0, int (*f)(int))
{
    *this = NumberSeries(a0, f);
}