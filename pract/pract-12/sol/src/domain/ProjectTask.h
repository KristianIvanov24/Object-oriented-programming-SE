#pragma once
#include "Task.h"
#include <memory>
#include <vector>

class ProjectTask : public Task
{
private:
    std::vector<std::unique_ptr<Task>> subtasks;

public:
    ProjectTask(
        const std::string& title,
        const std::string& description,
        const Date& deadline,
        Priority priority);

    void complete() override;

    void addSubtask(std::unique_ptr<Task> subtask);
    const std::vector<std::unique_ptr<Task>>& getSubtasks() const;
    bool allSubtasksCompleted() const;
};