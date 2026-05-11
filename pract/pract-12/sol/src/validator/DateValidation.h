#pragma once

namespace dateValidation
{
    bool isValid(int day, int month, int year);
    bool isValidYear(int year);
    bool isValidMonth(int month);
    bool isValidDay(int day, int month, int year);
};