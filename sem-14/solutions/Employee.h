#pragma once
#include <string>
#include <memory>

class Employee
{
protected:
    std::string name;
    int id;

private:
    static int nextId;

protected:
    Employee(const std::string& name);

public:
    Employee(const Employee&) = default;
    Employee& operator=(const Employee&) = default;
    
    virtual ~Employee() = default;

    int getId() const;

    virtual void printInfo() const;
    virtual std::unique_ptr<Employee> clone() const = 0;
};