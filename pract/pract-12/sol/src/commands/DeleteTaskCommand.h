#pragma once
#include "Command.h"
#include "services/TaskService.h"

class DeleteTaskCommand : public Command
{
private:
    TaskService& service;
    int taskId;

public:
    DeleteTaskCommand(TaskService& service, int taskId);
    void execute() override;
};