#include "LaunchClearanceService.h"
#include <stdexcept>

void LaunchClearanceService::copyFrom(const LaunchClearanceService& other)
{
    launchConditions.clear();
    launchConditions.reserve(other.launchConditions.size());
    for (const auto& launchCondition : other.launchConditions)
    {
        launchConditions.push_back(launchCondition->clone());
    }
}

LaunchClearanceService::LaunchClearanceService(const LaunchClearanceService& other)
{
    copyFrom(other);
}

LaunchClearanceService& LaunchClearanceService::operator=(const LaunchClearanceService& other)
{
    if (this != &other)
    {
        copyFrom(other);
    }
    return *this;
}

void LaunchClearanceService::addCondition(const std::unique_ptr<LaunchCondition>& launchCondition)
{
    if (launchCondition == nullptr)
    {
        throw std::invalid_argument("launchCondition is nullptr");
    }
    launchConditions.push_back(launchCondition->clone());
}

void LaunchClearanceService::addCondition(const LaunchCondition& launchCondition)
{
    launchConditions.push_back(launchCondition.clone());
}

std::optional<std::vector<std::string>> LaunchClearanceService::checkRocketClearance(const Rocket& rocket) const
{
    std::vector<std::string> errors;
    for (const auto& launchCondition : launchConditions)
    {
        std::optional<std::string> error = launchCondition->checkRocketClearance(rocket);
        if (error)
        {
            errors.push_back(*error);
        }
    }

    if (!errors.empty())
    {
        return errors;
    }

    return std::nullopt;
}