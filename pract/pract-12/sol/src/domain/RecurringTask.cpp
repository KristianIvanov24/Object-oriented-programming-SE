#include "RecurringTask.h"
#include "Date.h"
#include "Priority.h"
#include "Status.h"
#include "Task.h"
#include "validator/RecurringTaskValidation.h"
#include <string>

RecurringTask::RecurringTask(
    const std::string& title,
    const std::string& description,
    const Date& deadline,
    Priority priority,
    int intervalDays)
    : Task(title, description, deadline, priority)
{

    setIntervalDays(intervalDays);
}

void RecurringTask::complete()
{
    deadline.addDays(intervalDays);
}

int RecurringTask::getIntervalDays() const
{
    return intervalDays;
}

void RecurringTask::setIntervalDays(int intervalDays)
{
    if (!recurringTaskValidation::areValidIntervalDays(intervalDays))
    {
        // throw exception instead
        this->intervalDays = 7;
        return;
    }

    this->intervalDays = intervalDays;
}
