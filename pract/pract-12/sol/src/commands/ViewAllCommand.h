#pragma once
#include "services/TaskService.h"
#include "Command.h"

class ViewAllCommand : public Command
{
private:
    TaskService& service;

public:
    explicit ViewAllCommand(TaskService& service);
    void execute() override;
};