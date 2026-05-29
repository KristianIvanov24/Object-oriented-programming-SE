#pragma once
#include <string>
#include "LaunchCondition.h"

class RequiredTestsTakenCondition : public LaunchCondition
{
    std::string name;

public:
    explicit RequiredTestsTakenCondition(const std::string& name);

    std::optional<std::string> checkRocketClearance(const Rocket& rocket) const override;
    std::unique_ptr<LaunchCondition> clone() const override;
};