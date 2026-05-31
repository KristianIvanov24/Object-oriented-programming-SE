#include "Engineer.h"
#include <iostream>

Engineer::Engineer(
    const std::string& name,
    const std::string& specialization)
    : Employee(name),
      specialization(specialization)
{
}

void Engineer::printInfo() const
{
    std::cout
        << "Engineer: " << name
        << ", ID: " << id
        << ", Specialization: " << specialization
        << std::endl;
}

std::unique_ptr<Employee> Engineer::clone() const
{
    return std::make_unique<Engineer>(*this);
}