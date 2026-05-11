cmake_minimum_required(VERSION 4.2)

project(KECH)
 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
 
add_executable(KECH
    src/main.cpp
    src/constants/DateResources.h
    src/constants/TaskResources.h
    src/commands/AddTaskCommand.cpp
    src/commands/AddTaskCommand.h
    src/commands/CompleteTaskCommand.cpp
    src/commands/CompleteTaskCommand.h
    src/commands/DeleteTaskCommand.cpp
    src/commands/DeleteTaskCommand.h
    src/commands/ViewAllCommand.cpp
    src/commands/ViewAllCommand.h
    src/domain/Date.cpp
    src/domain/Date.h
    src/domain/Priority.h
    src/domain/ProjectTask.cpp
    src/domain/ProjectTask.h
    src/domain/RecurringTask.cpp
    src/domain/RecurringTask.h
    src/domain/SimpleTask.cpp
    src/domain/SimpleTask.h
    src/domain/Status.h
    src/domain/Task.cpp
    src/domain/Task.h
    src/repositories/Repository.hpp
    src/repositories/TaskRepository.h
    src/repositories/TaskRepository.cpp
    src/services/TaskService.h
    src/services/TaskService.cpp
    src/ui/ConsoleUI.cpp
    src/ui/ConsoleUI.h
    src/utils/DateUtils.h
    src/utils/DateUtils.cpp
    src/validator/DateValidation.h
    src/validator/DateValidation.cpp
    src/validator/RecurringTaskValidation.cpp
    src/validator/RecurringTaskValidation.h
    src/validator/TaskValidation.h
    src/validator/TaskValidation.cpp
    src/validator/Validation.h
)

target_include_directories(KECH PRIVATE src)
