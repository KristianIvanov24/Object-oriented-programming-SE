#include "Task.h"
#include "validator/TaskValidation.h"

int Task::nextId = 1;

Task::Task(
    const std::string& title,
    const std::string& description,
    const Date& deadline,
    Priority priority)
    : deadline(deadline), priority(priority), status(Status::PENDING),
      id(nextId)
{

    setTitle(title);
    setDescription(description);
    nextId++;
}

int Task::getId() const
{
    return id;
}

const std::string& Task::getTitle() const
{
    return title;
}

const std::string& Task::getDescription() const
{
    return description;
}

const Date& Task::getDeadline() const
{
    return deadline;
}

Priority Task::getPriority() const
{
    return priority;
}

Status Task::getStatus() const
{
    return status;
}

bool Task::isOverdue() const
{
    return deadline < Date::today();
}

bool Task::isCompleted() const
{
    return status == Status::COMPLETED;
}

void Task::setStatus(Status status)
{
    this->status = status;
}

void Task::setTitle(const std::string& title)
{
    if (!TaskValidation::isValidTitle(title))
    {
        // throw exception instead (soon enough)
        this->title = "";
        return;
    }

    this->title = title;
}

void Task::setDescription(const std::string& description)
{
    if (!TaskValidation::isValidDescription(description))
    {
        // throw exception instead
        this->description = "";
        return;
    }

    this->description = description;
}
