#include "Date.h"
#include "constants/DateResources.h"
#include "utils/DateUtils.h"
#include "validator/DateValidation.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

using dateUtils::daysInMonth;
using dateUtils::isLeapYear;
using dateValidation::isValid;
using dateValidation::isValidDay;
using dateValidation::isValidMonth;
using dateValidation::isValidYear;

Date::Date(int day, int month, int year)
{
    if (!isValid(day, month, year))
    {
        *this = today();
        return;
    }

    this->day = day;
    this->month = month;
    this->year = year;
}

int Date::getDay() const
{
    return day;
}

int Date::getMonth() const
{
    return month;
}

int Date::getYear() const
{
    return year;
}

Date Date::addDays(int days) const
{
    return fromSerial(toSerial() + days);
}

int Date::daysUntil(const Date& other) const
{
    return other.toSerial() - toSerial();
}

bool Date::isBefore(const Date& other) const
{
    return *this < other;
}

bool Date::isAfter(const Date& other) const
{
    return *this > other;
}

bool Date::isPast() const
{
    return *this < today();
}

Date Date::today()
{
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&t);

    return Date(
        localTime->tm_mday,
        localTime->tm_mon + resources::date::MIN_MONTHS,
        localTime->tm_year + resources::date::MIN_YEAR);
}

Date Date::fromString(const std::string& str)
{
    int d, m, y;
    char dash1, dash2;
    std::istringstream iss(str);
    iss >> d >> dash1 >> m >> dash2 >> y;

    if (iss.fail() || dash1 != '-' || dash2 != '-')
    {
        return resources::date::ZERO_DATE;
    }

    return Date(d, m, y);
}

std::string Date::toString() const
{
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << day << "-" << std::setw(2)
        << month << "-" << std::setw(4) << year;

    return oss.str();
}

int Date::toSerial() const
{
    int serial = 0;

    for (int y = resources::date::MIN_YEAR; y < year; ++y)
    {
        serial += resources::date::DAYS_IN_YEAR;
        if (isLeapYear(y))
        {
            serial += 1;
        }
    }

    for (int m = 1; m < month; ++m)
    {
        serial += daysInMonth(m, year);
    }

    serial += day - 1;

    return serial;
}

Date Date::fromSerial(int serial)
{
    int serialYear = resources::date::MIN_YEAR;
    while (true)
    {
        int yearLen = resources::date::DAYS_IN_YEAR;
        if (isLeapYear(serialYear))
        {
            yearLen += 1;
        }

        if (serial < yearLen)
        {
            break;
        }

        serial -= yearLen;
        serialYear++;
    }

    int serialMonth = 1;
    while (true)
    {
        int monthLen = daysInMonth(serialMonth, serialYear);

        if (serial < monthLen)
        {
            break;
        }

        serial -= monthLen;
        serialMonth++;
    }

    int serialDay = serial + 1;
    return Date(serialDay, serialMonth, serialYear);
}
