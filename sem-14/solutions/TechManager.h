#pragma once
#include "Manager.h"
#include "Engineer.h"

class TechManager : public Manager, public Engineer
{
public:
    TechManager(
        const std::string& name,
        const std::string& projectName,
        const std::string& specialization);

    void assignTask(const std::string& task) const;

    void printInfo() const override;

    std::unique_ptr<Employee> clone() const override;
};