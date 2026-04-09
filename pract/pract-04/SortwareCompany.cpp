#include "SoftwareCompany.h"
#include <iostream>
#include <cstring>
#pragma warning(disable : 4996)

SoftwareCompany::SoftwareCompany() : programmersCount(0) {}

bool SoftwareCompany::addProgrammer(const Programmer& p) {
    if (programmersCount >= Constants::MAX_PROGRAMMERS)
        return false;
    programmers[programmersCount++] = p;
    return true;
}

unsigned SoftwareCompany::getProgrammersCount() const {
    return programmersCount;
}

void SoftwareCompany::printProgrammers() const {
    for (unsigned i = 0; i < programmersCount; i++)
        programmers[i].print();
}

void SoftwareCompany::printProgrammersByLang(Language language) const {
    for (unsigned i = 0; i < programmersCount; i++)
        if (programmers[i].knowsLanguage(language))
            programmers[i].print();
}

double SoftwareCompany::getAverageSalary() const {
    if (programmersCount == 0) return 0.0;
    double total = 0.0;
    for (unsigned i = 0; i < programmersCount; i++)
        total += programmers[i].getSalary();
    return total / programmersCount;
}

double SoftwareCompany::getAverageAge() const {
    if (programmersCount == 0) return 0.0;
    double total = 0.0;
    for (unsigned i = 0; i < programmersCount; i++)
        total += programmers[i].getAge();
    return total / programmersCount;
}

void SoftwareCompany::setSalaryByFormula(const char* name, unsigned (*formula)(unsigned)) {
    for (unsigned i = 0; i < programmersCount; i++) {
        if (strcmp(programmers[i].getName(), name) == 0) {
            unsigned newSalary = formula(programmers[i].getSalary());
            programmers[i].setSalary(newSalary);
            return;
        }
    }
}

void SoftwareCompany::sortBySalary() {
    for (unsigned i = 0; i < programmersCount - 1; i++)
        for (unsigned j = 0; j < programmersCount - i - 1; j++)
            if (programmers[j].getSalary() > programmers[j + 1].getSalary()) {
                Programmer temp = programmers[j];
                programmers[j] = programmers[j + 1];
                programmers[j + 1] = temp;
            }
}

void SoftwareCompany::sortByAge() {
    for (unsigned i = 0; i < programmersCount - 1; i++)
        for (unsigned j = 0; j < programmersCount - i - 1; j++)
            if (programmers[j].getAge() > programmers[j + 1].getAge()) {
                Programmer temp = programmers[j];
                programmers[j] = programmers[j + 1];
                programmers[j + 1] = temp;
            }
}