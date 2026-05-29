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

Rocket::Rocket(const std::string& serial, const std::string& model)
{
    setSerial(serial);
    this->model = model;
}

void Rocket::addTest(const Test& test)
{
    testsTaken.push_back(test);
}

void Rocket::removeTest(const std::string& name)
{
    std::erase_if(
        testsTaken,
        [&name](const Test& test) { return test.getName() == name; });
}

std::string Rocket::getSerial() const
{
    return serial;
}

std::string Rocket::getModel() const
{
    return model;
}

const std::vector<Test>& Rocket::getTestsTaken() const
{
    return testsTaken;
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
        sum += test.getResult();
    }
    return sum / static_cast<double>(testsTaken.size());
}

int Rocket::getTestCycles() const
{
    int testCycles = 0;
    for (const auto& test : testsTaken)
    {
        testCycles += test.getTestCycles();
    }
    return testCycles;
}

bool Rocket::hasTakenTest(const std::string& testName) const
{
    return std::ranges::any_of(
        testsTaken,
        [&](const auto& test) { return test.getName() == testName; });
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
