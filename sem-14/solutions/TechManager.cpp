#include "TechManager.h"
#include <iostream>

TechManager::TechManager(
    const std::string& name,
    const std::string& projectName,
    const std::string& specialization)
    : Employee(name),
      Manager(name, projectName),
      Engineer(name, specialization)
{
}

void TechManager::assignTask(const std::string& task) const
{
    std::cout
        << "TechManager "
        << name
        << " assigns task: "
        << task
        << std::endl;
}

void TechManager::printInfo() const
{
    std::cout
        << "TechManager: " << name
        << ", ID: " << id
        << ", Project: " << projectName
        << ", Specialization: " << specialization
        << std::endl;
}

std::unique_ptr<Employee> TechManager::clone() const
{
    return std::make_unique<TechManager>(*this);
}