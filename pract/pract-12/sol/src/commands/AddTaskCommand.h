#pragma once
#include "Command.h"
#include "domain/Task.h"
#include "services/TaskService.h"
#include <memory>
#include <iostream>

class AddTaskCommand : public Command {
private:
    TaskService& service;
    std::unique_ptr<Task> task;

public:
    AddTaskCommand(TaskService& service, std::unique_ptr<Task> task);
    void execute() override;
};