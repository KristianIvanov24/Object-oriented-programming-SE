#include "Rocket.h"

#include <algorithm>
#include <stdexcept>

#include "Resources.h"

void Rocket::setSerial(const std::string& serial)
{
    if (serial.size() != resources::SERIAL_LEN)
    {
        throw std::invalid_argument("Rocket serial number length mismatch");
    }

    this->serial = serial;
}

void Rocket::copyFrom(const Rocket& other)
{
    serial = other.serial;
    model = other.model;
    testsTaken.clear();
    testsTaken.reserve(other.testsTaken.size());
    for (const auto& test : other.testsTaken)
    {
        testsTaken.push_back(std::make_unique<Test>(*test));
    }
}

Rocket::Rocket(const std::string& serial, const std::string& model)
    : model(model)
{
    setSerial(serial);
}

Rocket::Rocket()
    : model("Default model")
{
    setSerial("00000"); // should be in constants
}

Rocket::Rocket(const Rocket& other)
{
    serial = other.serial;
    model = other.model;
    testsTaken.reserve(other.testsTaken.size());
    for (const auto& test : other.testsTaken)
    {
        testsTaken.push_back(std::make_unique<Test>(*test));
    }
}

Rocket& Rocket::operator=(const Rocket& other)
{
    if (this != &other)
    {
        copyFrom(other);
    }
    return *this;
}

void Rocket::addTest(const Test& test)
{
    testsTaken.push_back(std::make_unique<Test>(test));
}

void Rocket::addTest(std::unique_ptr<Test> test)
{
    testsTaken.push_back(std::move(test));
}

void Rocket::removeTest(const std::string& name)
{
    std::erase_if(
        testsTaken,
        [&name](const std::unique_ptr<Test>& test)
        {
            return test->getName() == name;
        });
}

const std::string& Rocket::getSerial() const
{
    return serial;
}

const std::string& Rocket::getModel() const
{
    return model;
}

std::vector<const Test*> Rocket::getTestsTaken() const
{
    std::vector<const Test*> toReturn;
    toReturn.reserve(testsTaken.size());
    for (const auto& test : testsTaken)
    {
        toReturn.push_back(test.get());
    }
    return toReturn;
}

double Rocket::averageReliability() const
{
    if (testsTaken.empty())
    {
        return 0;
    }

    int sum = 0;
    for (const auto& test : testsTaken)
    {
        sum += test->getResult();
    }
    return sum / static_cast<double>(testsTaken.size());
}

int Rocket::getTestCycles() const
{
    int testCycles = 0;
    for (const auto& test : testsTaken)
    {
        testCycles += test->getTestCycles();
    }
    return testCycles;
}

bool Rocket::hasTakenTest(const std::string& testName) const
{
    return std::ranges::any_of(
        testsTaken,
        [&](const auto& test)
        {
            return test->getName() == testName;
        });
    // or
    // for (const auto& test : testsTaken)
    // {
    //     if (test.getName() == testName)
    //     {
    //         return true;
    //     }
    // }
    // return false;
}