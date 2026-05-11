#include "ConsoleUI.h"
#include "commands/AddTaskCommand.h"
#include "commands/CompleteTaskCommand.h"
#include "commands/DeleteTaskCommand.h"
#include "commands/ViewAllCommand.h"
#include "domain/ProjectTask.h"
#include "domain/RecurringTask.h"
#include "domain/SimpleTask.h"
#include <iostream>
#include <limits>
#include <memory>

ConsoleUI::ConsoleUI(TaskService& service) : service(service) {}

void ConsoleUI::run()
{
    while (true)
    {
        showMenu();
        int choice = readMenuChoice();

        switch (choice)
        {
        case 1:
            handleAddTask();
            break;
        case 2:
            handleCompleteTask();
            break;
        case 3:
            handleDeleteTask();
            break;
        case 4:
            handleViewAll();
            break;
        case 0:
            break;
        default:
            std::cout << "Invalid choice.\n";
        }
    }
}

void ConsoleUI::showMenu() const
{
    std::cout << "\n=== Task Manager ===\n"
              << "1. Add task\n"
              << "2. Complete task\n"
              << "3. Delete task\n"
              << "4. View all tasks\n"
              << "0. Exit\n"
              << "Choice: ";
}

int ConsoleUI::readMenuChoice() const
{
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}

void ConsoleUI::handleAddTask()
{
    std::cout << "\nTask type:\n"
              << "  1) Simple\n"
              << "  2) Recurring\n"
              << "  3) Project\n";
    int type = readInt("Type: ");

    std::string title = readLine("Title: ");
    std::string description = readLine("Description: ");
    Date deadline = readDate("Deadline (DD-MM-YYYY): ");
    Priority priority = readPriority();

    std::unique_ptr<Task> task;
    switch (type)
    {
    case 1:
        task = std::make_unique<SimpleTask>(
            title, description, deadline, priority);
        break;
    case 2:
    {
        int interval = readInt("Interval days: ");
        task = std::make_unique<RecurringTask>(
            title, description, deadline, priority, interval);
        break;
    }
    case 3:
        task = std::make_unique<ProjectTask>(
            title, description, deadline, priority);
        break;
    default:
        std::cout << "Invalid type.\n";
        return;
    }

    AddTaskCommand cmd(service, std::move(task));
    cmd.execute();
}

void ConsoleUI::handleCompleteTask()
{
    int id = readInt("Task ID to complete: ");
    CompleteTaskCommand cmd(service, id);
    cmd.execute();
}

void ConsoleUI::handleDeleteTask()
{
    int id = readInt("Task ID to delete: ");
    DeleteTaskCommand cmd(service, id);
    cmd.execute();
}

void ConsoleUI::handleViewAll()
{
    ViewAllCommand cmd(service);
    cmd.execute();
}

std::string ConsoleUI::readLine(const std::string& prompt) const
{
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return line;
}

int ConsoleUI::readInt(const std::string& prompt) const
{
    std::cout << prompt;
    int value;
    std::cin >> value;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

Date ConsoleUI::readDate(const std::string& prompt) const
{
    std::string str = readLine(prompt);
    return Date::fromString(str);
}

Priority ConsoleUI::readPriority() const
{
    std::cout << "Priority:\n"
              << "  1) LOW\n"
              << "  2) MEDIUM\n"
              << "  3) HIGH\n";
    int p = readInt("Choice: ");
    switch (p)
    {
    case 1:
        return Priority::LOW;
    case 3:
        return Priority::HIGH;
    default:
        return Priority::MEDIUM;
    }
}