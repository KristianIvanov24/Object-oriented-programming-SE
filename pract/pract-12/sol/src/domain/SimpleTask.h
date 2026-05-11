#pragma once
#include "Task.h"

class SimpleTask : public Task
{
public:
    SimpleTask(
        const std::string& title,
        const std::string& description,
        const Date& deadline,
        Priority priority);

    void complete() override;
};