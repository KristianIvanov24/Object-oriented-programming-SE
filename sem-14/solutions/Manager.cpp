#include "Manager.h"
#include <iostream>

Manager::Manager(
    const std::string& name,
    const std::string& projectName)
    : Employee(name),
      projectName(projectName)
{
}
void Manager::printInfo() const
{
    std::cout
        << "Manager: " << name
        << ", ID: " << id
        << ", Project: " << projectName
        << std::endl;
}

std::unique_ptr<Employee> Manager::clone() const
{
    return std::make_unique<Manager>(*this);
}