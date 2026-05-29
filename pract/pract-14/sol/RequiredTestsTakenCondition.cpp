#include "RequiredTestsTakenCondition.h"

RequiredTestsTakenCondition::RequiredTestsTakenCondition(const std::string& name)
    : name(name)
{
}

std::optional<std::string> RequiredTestsTakenCondition::checkRocketClearance(const Rocket& rocket) const
{
    if (!rocket.hasTakenTest(name))
    {
        return "Rocket hasn't taken test " + name;
    }

    return std::nullopt;
}

std::unique_ptr<LaunchCondition> RequiredTestsTakenCondition::clone() const
{
    return std::make_unique<RequiredTestsTakenCondition>(*this);
}