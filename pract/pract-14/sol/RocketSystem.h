#pragma once
#include "LaunchClearanceService.h"

class RocketSystem
{
    LaunchClearanceService launchClearanceService;
    std::vector<Rocket> rockets; // can also be vector<unique_ptr<Rocket>>

public:
    void addLaunchCondition(const LaunchCondition& launchCondition);
    void addRocket(const Rocket& rocket);
    void addRocket(Rocket&& rocket);
    bool hasRocket(const std::string& serial) const;
    const Rocket* findRocketBySerial(const std::string& serial) const;
    void removeRocket(const std::string& serial);
    const Rocket& operator[](const std::string& serial) const;
    const std::vector<Rocket>& getRockets() const;
    std::optional<std::vector<std::string>> checkRocketClearance(const std::string& name) const;
};