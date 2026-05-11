#include "AddTaskCommand.h"

AddTaskCommand::AddTaskCommand(TaskService& service, std::unique_ptr<Task> task)
    : service(service), task(std::move(task))
{
}

void AddTaskCommand::execute()
{
    if (service.addTask(std::move(task)))
    {
        std::cout << "Task added.\n";
    }
    else
    {
        std::cout << "Failed to add task.\n";
    }
}