#pragma once
#include <string>

class Test
{
    std::string name;
    int testCycles;
    int result;
    bool isRequired;

public:
    Test(const std::string& name, int testCycles, int result, bool isRequired);

    std::string getName() const;
    int getTestCycles() const;
    int getResult() const;
    bool getIsRequired() const;
};
