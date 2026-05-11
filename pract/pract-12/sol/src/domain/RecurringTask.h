#pragma once
#include "Task.h"

class RecurringTask : public Task
{
private:
    int intervalDays;

public:
    RecurringTask(
        const std::string& title,
        const std::string& description,
        const Date& deadline,
        Priority priority,
        int intervalDays);

    void complete() override;

    int getIntervalDays() const;

private:
    void setIntervalDays(int intervalDays);
};