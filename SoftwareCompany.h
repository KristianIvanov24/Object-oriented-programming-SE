#pragma once
#include "Programmer.h"

class SoftwareCompany {
    Programmer programmers[Constants::MAX_PROGRAMMERS];
    unsigned programmersCount;

public:
    SoftwareCompany();

    bool addProgrammer(const Programmer& p);
    unsigned getProgrammersCount() const;

    void printProgrammers() const;
    void printProgrammersByLang(Language language) const;

    double getAverageSalary() const;
    double getAverageAge() const;

    void setSalaryByFormula(const char* name, unsigned (*formula)(unsigned));

    void sortBySalary();
    void sortByAge();
};