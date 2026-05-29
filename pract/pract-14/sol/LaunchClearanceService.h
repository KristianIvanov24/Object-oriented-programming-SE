#pragma once
#include <memory>
#include <vector>

#include "LaunchCondition.h"

class LaunchClearanceService
{
    std::vector<std::unique_ptr<LaunchCondition>> launchConditions;

    void copyFrom(const LaunchClearanceService& other);

public:
    LaunchClearanceService() = default;
    LaunchClearanceService(const LaunchClearanceService& other);
    LaunchClearanceService(LaunchClearanceService&& other) noexcept = default;
    LaunchClearanceService& operator=(const LaunchClearanceService& other);
    LaunchClearanceService& operator=(LaunchClearanceService&& other) noexcept = default;


    void addCondition(const std::unique_ptr<LaunchCondition>& launchCondition);
    void addCondition(const LaunchCondition& launchCondition);

    std::optional<std::vector<std::string>> checkRocketClearance(const Rocket& rocket) const;
};