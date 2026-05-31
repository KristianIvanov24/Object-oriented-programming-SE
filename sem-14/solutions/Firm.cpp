#include "Firm.h"
#include <iostream>

void Firm::copyFrom(const Firm& other)
{
    for (const auto& worker : other.workers)
    {
        workers.push_back(worker->clone());
    }
}

Firm::Firm(const Firm& other)
{
    copyFrom(other);
}

Firm& Firm::operator=(const Firm& other)
{
    if (this != &other)
    {
        workers.clear();
        copyFrom(other);
    }

    return *this;
}

void Firm::addWorker(const Employee& employee)
{
    workers.push_back(employee.clone());
}

void Firm::removeWorker(int id)
{
    for (auto it = workers.begin(); it != workers.end(); ++it)
    {
        if ((*it)->getId() == id)
        {
            workers.erase(it);
            return;
        }
    }
}

void Firm::printAllWorkers() const
{
    for (const auto& worker : workers)
    {
        worker->printInfo();
    }
}