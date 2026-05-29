#pragma once
#include <memory>
#include <optional>
#include "Rocket.h"

class LaunchCondition
{
public:
    // optional or expected or exception or a pointer
    virtual std::optional<std::string> checkRocketClearance(const Rocket& rocket) const = 0;
    virtual std::unique_ptr<LaunchCondition> clone() const = 0;
    virtual ~LaunchCondition() = default;
};
