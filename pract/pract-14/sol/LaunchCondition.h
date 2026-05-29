#pragma once
#include <memory>
#include <optional>
#include "Rocket.h"

class LaunchCondition
{
public:
    // optional/expected/exception/pointer/custom class
    virtual std::optional<std::string> checkRocketClearance(const Rocket& rocket) const = 0;
    virtual std::unique_ptr<LaunchCondition> clone() const = 0;
    virtual ~LaunchCondition() = default;
};