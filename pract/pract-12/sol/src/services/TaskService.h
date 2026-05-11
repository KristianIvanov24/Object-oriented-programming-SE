#pragma once
#include "repositories/TaskRepository.h"
#include "validator/TaskValidation.h"
#include <vector>

class TaskService {
private:
    TaskRepository& repo;

public:
    TaskService(TaskRepository& repo);

    bool addTask(std::unique_ptr<Task> task);
    bool completeTask(int id);
    bool deleteTask(int id);

    std::vector<const Task*> getAllSortedByPriority() const;
    const Task* findById(int id) const;
};