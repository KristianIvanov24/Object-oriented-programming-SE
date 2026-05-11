#pragma once
#include "services/TaskService.h"
#include <string>

class ConsoleUI {
private:
    TaskService& service;

    void showMenu() const;
    int readMenuChoice() const;

    void handleAddTask();
    void handleCompleteTask();
    void handleDeleteTask();
    void handleViewAll();

    std::string readLine(const std::string& prompt) const;
    int readInt(const std::string& prompt) const;
    Date readDate(const std::string& prompt) const;
    Priority readPriority() const;

public:
    ConsoleUI(TaskService& service);
    void run();
};