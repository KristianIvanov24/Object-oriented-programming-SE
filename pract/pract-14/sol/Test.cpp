#include "Test.h"

Test::Test(const std::string& name, int testCycles, int result, bool isRequired)
    : name(name), testCycles(testCycles), result(result), isRequired(isRequired)
{
}

const std::string& Test::getName() const
{
    return name;
}

int Test::getTestCycles() const
{
    return testCycles;
}

int Test::getResult() const
{
    return result;
}

bool Test::getIsRequired() const
{
    return isRequired;
}