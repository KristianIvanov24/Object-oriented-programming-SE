#include "TaskService.h"
#include "repositories/TaskRepository.h"
#include <algorithm>
#include <vector>

TaskService::TaskService(TaskRepository& repo) : repo(repo) {}

bool TaskService::addTask(std::unique_ptr<Task> task)
{
    if (!task)
    {
        return false;
    }

    repo.add(std::move(task));
    return true;
}

bool TaskService::completeTask(int id)
{
    return repo.completeById(id);
}

bool TaskService::deleteTask(int id)
{
    return repo.removeById(id);
}

std::vector<const Task*> TaskService::getAllSortedByPriority() const
{
    std::vector<const Task*> tasks = repo.getAll();
    std::sort(
        tasks.begin(),
        tasks.end(),
        [](const Task* a, const Task* b)
        { return a->getPriority() > b->getPriority(); });
    return tasks;
}

const Task* TaskService::findById(int id) const
{
    return repo.findById(id);
}
