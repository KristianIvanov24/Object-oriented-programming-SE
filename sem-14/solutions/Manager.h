#pragma once
#include "Employee.h"

class Manager : virtual public Employee
{
protected:
    std::string projectName;

public:
    Manager(
        const std::string& name,
        const std::string& projectName);

    void printInfo() const override;

    std::unique_ptr<Employee> clone() const override;
};