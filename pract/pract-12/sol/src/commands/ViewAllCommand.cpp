#include "ViewAllCommand.h"
#include <iostream>

ViewAllCommand::ViewAllCommand(TaskService& service) : service(service) {}

void ViewAllCommand::execute()
{
    auto tasks = service.getAllSortedByPriority();
    if (tasks.empty())
    {
        std::cout << "No tasks.\n";
        return;
    }

    std::cout << "\n=== Tasks ===\n";
    for (const Task* t : tasks)
    {
        std::cout << "[" << t->getId() << "] " << t->getTitle() << " - due "
                  << t->getDeadline().toString() << "\n";
    }
}