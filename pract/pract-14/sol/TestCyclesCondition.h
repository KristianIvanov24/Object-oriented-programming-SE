#pragma once
#include "LaunchCondition.h"

class TestCyclesCondition : public LaunchCondition
{
    int requiredTestCycles;

    void setRequiredTestCycles(int requiredTestCycles);

public:
    explicit TestCyclesCondition(int requiredTestCycles);
    std::optional<std::string> checkRocketClearance(const Rocket& rocket) const override;
    std::unique_ptr<LaunchCondition> clone() const override;
};
