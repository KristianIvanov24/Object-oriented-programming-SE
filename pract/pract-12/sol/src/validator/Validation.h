// Validation.h
#pragma once
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

namespace Validation
{

    template <typename T>
    bool inRange(T value, T min, T max)
    {
        return value >= min && value <= max;
    }

    template <typename T>
    bool inRangeExclusive(T value, T min, T max)
    {
        return value > min && value < max;
    }

    template <typename T>
    bool isPositive(T value)
    {
        return value > T{0};
    }

    template <typename T>
    bool isNonNegative(T value)
    {
        return value >= T{0};
    }

    inline bool isNotEmpty(const std::string& str)
    {
        return !str.empty();
    }

    inline bool isEmpty(const std::string& str)
    {
        return str.empty();
    }

    inline bool hasLengthBetween(const std::string& str, size_t min, size_t max)
    {
        return str.length() >= min && str.length() <= max;
    }

    inline bool hasMaxLength(const std::string& str, size_t max)
    {
        return str.length() <= max;
    }

    inline bool hasMinLength(const std::string& str, size_t min)
    {
        return str.length() >= min;
    }
}