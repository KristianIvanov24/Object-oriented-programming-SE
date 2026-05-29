#include "TestCyclesCondition.h"
#include <format>

void TestCyclesCondition::setRequiredTestCycles(int requiredTestCycles)
{
    if (requiredTestCycles < 0)
    {
        throw std::invalid_argument("Required test cycles cannot be negative");
    }
    this->requiredTestCycles = requiredTestCycles;
}

TestCyclesCondition::TestCyclesCondition(int requiredTestCycles)
{
    setRequiredTestCycles(requiredTestCycles);
}

std::optional<std::string> TestCyclesCondition::checkRocketClearance(const Rocket& rocket) const
{
    if (rocket.getTestCycles() < requiredTestCycles)
    {
        return "Rocket cycles were "
            + std::to_string(rocket.getTestCycles())
            + " but must be "
            + std::to_string(requiredTestCycles);

        // or
        // return std::format(
        //      "Rocket cycles were {} but must be {}",
        //      rocket.getTestCycles(),
        //      requiredTestCycles);
    }

    return std::nullopt;
}

std::unique_ptr<LaunchCondition> TestCyclesCondition::clone() const
{
    return std::make_unique<TestCyclesCondition>(*this);
}
