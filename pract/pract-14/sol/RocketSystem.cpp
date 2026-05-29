#include "RocketSystem.h"

#include <algorithm>

void RocketSystem::addLaunchCondition(const LaunchCondition& launchCondition)
{
    launchClearanceService.addCondition(launchCondition);
}

void RocketSystem::addRocket(const Rocket& rocket)
{
    if (hasRocket(rocket.getSerial()))
    {
        throw std::invalid_argument("Rocket already exists");
        // can make custom exception for example "RocketAlreadyExistsException"
    }
    rockets.push_back(rocket);
}

void RocketSystem::addRocket(Rocket&& rocket)
{
    if (hasRocket(rocket.getSerial()))
    {
        throw std::invalid_argument("Rocket already exists");
    }
    rockets.push_back(std::move(rocket));
}

bool RocketSystem::hasRocket(const std::string& serial) const
{
    return findRocketBySerial(serial) != nullptr;
}

const Rocket* RocketSystem::findRocketBySerial(const std::string& serial) const
{
    auto it = std::ranges::find_if(
        rockets,
        [&serial](const Rocket& rocket)
        {
            return rocket.getSerial() == serial;
        });

    return it != rockets.end() ? &(*it) : nullptr;
}

void RocketSystem::removeRocket(const std::string& serial)
{
    auto removed = std::erase_if(
        rockets,
        [&serial](const Rocket& rocket)
        {
            return rocket.getSerial() == serial;
        });

    if (removed == 0)
    {
        throw std::invalid_argument("Rocket not found");
        // can make custom exception for example "RocketNotFound"
    }
}

const Rocket& RocketSystem::operator[](const std::string& serial) const
{
    const Rocket* rocket = findRocketBySerial(serial);
    if (!rocket)
    {
        throw std::invalid_argument("Rocket not found");
        // can make custom exception for example "RocketNotFound"
    }

    return *rocket;
}

const std::vector<Rocket>& RocketSystem::getRockets() const
{
    return rockets;
}

std::optional<std::vector<std::string>> RocketSystem::checkRocketClearance(const std::string& serial) const
{
    const Rocket& rocket = (*this)[serial];
    return launchClearanceService.checkRocketClearance(rocket);
}