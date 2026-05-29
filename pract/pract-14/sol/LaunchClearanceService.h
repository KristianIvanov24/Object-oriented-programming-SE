#pragma once
#include <memory>
#include <vector>

#include "LaunchCondition.h"

class LaunchClearanceService
{
    std::vector<std::unique_ptr<LaunchCondition>> launchConditions;

public:
    void addCondition(const std::unique_ptr<LaunchCondition>& launchCondition);
    void addCondition(const LaunchCondition& launchCondition);

    std::optional<std::vector<std::string>> checkRocketClearance(const Rocket& rocket) const;
};
