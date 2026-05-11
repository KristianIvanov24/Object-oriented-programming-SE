#include "DateValidation.h"
#include "constants/DateResources.h"
#include "utils/DateUtils.h"

bool dateValidation::isValid(int day, int month, int year)
{
    return dateValidation::isValidYear(year)
        && dateValidation::isValidMonth(month)
        && dateValidation::isValidDay(day, month, year);
}

bool dateValidation::isValidYear(int year)
{
    return year >= resources::date::MIN_YEAR
        && year <= resources::date::MAX_YEAR;
}

bool dateValidation::isValidMonth(int month)
{
    return month >= resources::date::MIN_MONTHS
        && month <= resources::date::MAX_MONTHS;
}

bool dateValidation::isValidDay(int day, int month, int year)
{
    return day >= resources::date::MIN_DAY
        && day <= dateUtils::daysInMonth(month, year);
}
