#include "DateUtils.h"
#include "constants/DateResources.h"

bool dateUtils::isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int dateUtils::daysInMonth(int month, int year)
{
    if (month == resources::date::FEBRUARY && isLeapYear(year))
    {
        return resources::date::FEBRUARY_LEAP_DAYS;
    }

    return resources::date::MONTH_DAYS[month - 1];
}