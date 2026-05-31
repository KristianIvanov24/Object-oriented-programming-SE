#pragma once
#include "Employee.h"
#include <vector>
#include <memory>

class Firm
{
private:
    std::vector<std::unique_ptr<Employee>> workers;

    void copyFrom(const Firm& other);

public:
    Firm() = default;
    Firm(const Firm& other);
    Firm& operator=(const Firm& other);

    Firm(Firm&&) noexcept = default;
    Firm& operator=(Firm&&) noexcept = default;

    ~Firm() = default;

    void addWorker(const Employee& employee);

    void removeWorker(int id);

    void printAllWorkers() const;
};