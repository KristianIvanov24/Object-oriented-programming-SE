#include "SimpleTask.h"
#include "Date.h"
#include "Priority.h"
#include "Status.h"
#include "Task.h"
#include <string>

SimpleTask::SimpleTask(
    const std::string& title,
    const std::string& description,
    const Date& deadline,
    Priority priority)
    : Task(title, description, deadline, priority)
{
}

void SimpleTask::complete()
{
    setStatus(Status::COMPLETED);
}
