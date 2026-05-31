#include "Employee.h"
#include <iostream>

int Employee::nextId = 1;

Employee::Employee(const std::string& name)
    : name(name), id(nextId++)
{
}

int Employee::getId() const
{
    return id;
}

void Employee::printInfo() const
{
    std::cout
        << "Name: " << name
        << ", ID: " << id
        << '\n';
}