#include "ProjectTask.h"

ProjectTask::ProjectTask(
    const std::string& title,
    const std::string& description,
    const Date& deadline,
    Priority priority)
    : Task(title, description, deadline, priority)
{
}

void ProjectTask::complete()
{
    if (!allSubtasksCompleted())
    {
        // alternatively throw exception or something?
        return;
    }
    setStatus(Status::COMPLETED);
}

void ProjectTask::addSubtask(std::unique_ptr<Task> subtask)
{
    subtasks.push_back(std::move(subtask));
}

const std::vector<std::unique_ptr<Task>>& ProjectTask::getSubtasks() const
{
    return subtasks;
}

bool ProjectTask::allSubtasksCompleted() const
{
    for (const auto& s : subtasks)
    {
        if (!s->isCompleted())
        {
            return false;
        }
    }
    return true;
}