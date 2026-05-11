#pragma once
#include <compare>
#include <string>

class Date
{
private:
    int year;
    int month;
    int day;

public:
    Date();
    Date(int day, int month, int year);

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    Date addDays(int days) const;
    int daysUntil(const Date& other) const;

    bool isBefore(const Date& other) const;
    bool isAfter(const Date& other) const;
    bool isPast() const;

    static Date today();
    static Date fromString(const std::string& str);

    std::string toString() const;

    auto operator<=>(const Date& other) const = default;
    bool operator==(const Date& other) const = default;

private:
    int toSerial() const;
    static Date fromSerial(int serial);
};
