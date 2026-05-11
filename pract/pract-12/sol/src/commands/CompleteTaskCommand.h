#pragma once
#include "Command.h"
#include "services/TaskService.h"

class CompleteTaskCommand : public Command
{
private:
    TaskService& service;
    int taskId;

public:
    CompleteTaskCommand(TaskService& service, int taskId);
    void execute() override;
};