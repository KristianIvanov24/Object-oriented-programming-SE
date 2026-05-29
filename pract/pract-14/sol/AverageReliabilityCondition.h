#pragma once
#include "LaunchCondition.h"

class AverageReliabilityCondition : public LaunchCondition
{
    double requiredAverageReliability;

    void setRequiredAverageReliability(double requiredAverageReliability);

public:
    explicit AverageReliabilityCondition(double requiredAverageReliability);
    std::optional<std::string> checkRocketClearance(const Rocket& rocket) const override;
    std::unique_ptr<LaunchCondition> clone() const override;
};