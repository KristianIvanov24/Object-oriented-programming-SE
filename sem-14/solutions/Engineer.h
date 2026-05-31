#pragma once
#include "Employee.h"

class Engineer : virtual public Employee
{
protected:
    std::string specialization;

public:
    Engineer(
        const std::string& name,
        const std::string& specialization);

    void printInfo() const override;

    std::unique_ptr<Employee> clone() const override;
};