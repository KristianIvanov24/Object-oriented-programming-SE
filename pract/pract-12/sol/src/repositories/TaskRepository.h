#pragma once
#include "domain/Task.h"
#include "Repository.hpp"
#include <string>

class TaskRepository : public Repository<Task> {
private:
    std::string filename;

public:
    explicit TaskRepository(const std::string& filename);

    const Task* findById(int id) const;
    bool removeById(int id);
    bool completeById(int id);

    void loadFromFile();
    void saveToFile() const;
};