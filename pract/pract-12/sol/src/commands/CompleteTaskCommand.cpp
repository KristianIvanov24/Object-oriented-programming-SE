#include "CompleteTaskCommand.h"
#include <iostream>

CompleteTaskCommand::CompleteTaskCommand(TaskService& service, int taskId)
    : service(service), taskId(taskId)
{
}

void CompleteTaskCommand::execute()
{
    if (service.completeTask(taskId))
    {
        std::cout << "Task completed.\n";
    }
    else
    {
        std::cout << "Task not found.\n";
    }
}