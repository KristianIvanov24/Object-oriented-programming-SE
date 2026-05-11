#pragma once
#include "domain/Date.h"

namespace resources::date
{
    constexpr int MONTH_DAYS[]
        = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    constexpr int MIN_YEAR = 1900;
    constexpr int MAX_YEAR = 2100;

    constexpr int MAX_MONTHS = 12;
    constexpr int MIN_MONTHS = 1;
    constexpr int FEBRUARY = 2;
    constexpr int FEBRUARY_LEAP_DAYS = 29;

    constexpr int MIN_DAY = 1;
    constexpr int DAYS_IN_YEAR = 365;
    constexpr int DAYS_IN_LEAP_YEAR = DAYS_IN_YEAR + 1;

    const Date ZERO_DATE = Date(1, 1, 1900);
}
