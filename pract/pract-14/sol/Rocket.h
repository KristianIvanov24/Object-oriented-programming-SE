#pragma once
#include <string>
#include <vector>

#include "Test.h"

#include <memory>

class Rocket
{
    std::string serial;
    std::string model;
    std::vector<std::unique_ptr<Test>> testsTaken; // can also be vector<Test>

    void setSerial(const std::string& serial);

    void copyFrom(const Rocket& other);

public:
    Rocket(const std::string& serial, const std::string& model);
    Rocket();
    Rocket(const Rocket& other);
    Rocket(Rocket&& other) noexcept = default;
    Rocket& operator=(const Rocket& other);
    Rocket& operator=(Rocket&& other) noexcept = default;

    void addTest(const Test& test);
    void addTest(std::unique_ptr<Test> test);
    void removeTest(const std::string& name);

    const std::string& getSerial() const;
    const std::string& getModel() const;
    std::vector<const Test*> getTestsTaken() const;
    // can also do const Test* getTest(size_t index) const; for accessing tests
    double averageReliability() const;
    int getTestCycles() const;
    bool hasTakenTest(const std::string& testName) const;
};