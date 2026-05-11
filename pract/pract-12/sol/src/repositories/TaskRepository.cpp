#include "TaskRepository.h"

TaskRepository::TaskRepository(const std::string& filename) {}

const Task* TaskRepository::findById(int id) const
{
    return findWhere([id](const Task& t) { return t.getId() == id; });
}

bool TaskRepository::removeById(int id)
{
    return removeWhere([id](const Task& t) { return t.getId() == id; });
}

bool TaskRepository::completeById(int id)
{
    return updateWhere(
        [id](const Task& t) { return t.getId() == id; },
        [](Task& t) { t.complete(); });
}

void TaskRepository::loadFromFile()
{
    // to implement
}

void TaskRepository::saveToFile() const
{
    // to implement
}
