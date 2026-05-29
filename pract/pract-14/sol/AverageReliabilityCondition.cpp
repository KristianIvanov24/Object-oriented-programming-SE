#include "AverageReliabilityCondition.h"
#include <format>
#include <stdexcept>

void AverageReliabilityCondition::setRequiredAverageReliability(double requiredAverageReliability)
{
    if (requiredAverageReliability < 1 || requiredAverageReliability > 10)
    {
        throw std::invalid_argument("RequiredAverageReliability must be between 1 and 10");
    }

    this->requiredAverageReliability = requiredAverageReliability;
}

AverageReliabilityCondition::AverageReliabilityCondition(double requiredAverageReliability)
{
    setRequiredAverageReliability(requiredAverageReliability);
}

std::optional<std::string> AverageReliabilityCondition::checkRocketClearance(const Rocket& rocket) const
{
    if (rocket.averageReliability() < requiredAverageReliability)
    {
        return std::format(
            "Average reliability was {} but must be {}",
            rocket.averageReliability(),
            requiredAverageReliability);
    }

    return std::nullopt;
}

std::unique_ptr<LaunchCondition> AverageReliabilityCondition::clone() const
{
    return std::make_unique<AverageReliabilityCondition>(*this);
}