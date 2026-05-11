#include "DeleteTaskCommand.h"
#include <iostream>

DeleteTaskCommand::DeleteTaskCommand(TaskService& service, int taskId)
    : service(service), taskId(taskId)
{
}

void DeleteTaskCommand::execute()
{
    if (service.deleteTask(taskId))
    {
        std::cout << "Task deleted.\n";
    }
    else
    {
        std::cout << "Task not found.\n";
    }
}