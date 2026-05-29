#pragma once
#include <string>
#include <vector>

#include "Test.h"

class Rocket
{
    std::string serial;
    std::string model;
    std::vector<Test> testsTaken;

    void setSerial(const std::string& serial);

public:
    Rocket(const std::string& serial, const std::string& model);

    void addTest(const Test& test);
    void removeTest(const std::string& name);

    std::string getSerial() const;
    std::string getModel() const;
    const std::vector<Test>& getTestsTaken() const;
    double averageReliability() const;
    int getTestCycles() const;
    bool hasTakenTest(const std::string& testName) const;
};
