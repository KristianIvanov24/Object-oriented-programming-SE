#include "SoftwareCompany.h"
#include <iostream>

unsigned raise10Percent(unsigned salary) {
    return salary + salary / 10;
}

int main() {
    Programmer p1("Alice", 25, 3000);
    p1.learnLanguage(Language::CPP);
    p1.learnLanguage(Language::PYTHON);

    Programmer p2("Bob", 30, 4500);
    p2.learnLanguage(Language::JAVA);

    Programmer p3("Carol", 22, 2800);
    p3.learnLanguage(Language::CPP);
    p3.learnLanguage(Language::JAVASCRIPT);

    SoftwareCompany company;
    company.addProgrammer(p1);
    company.addProgrammer(p2);
    company.addProgrammer(p3);

    std::cout << "=== All Programmers ===\n";
    company.printProgrammers();

    std::cout << "\n=== C++ Programmers ===\n";
    company.printProgrammersByLang(Language::CPP);

    std::cout << "\nAverage salary: " << company.getAverageSalary() << "\n";
    std::cout << "Average age: " << company.getAverageAge() << "\n";

    company.setSalaryByFormula("Alice", raise10Percent);

    std::cout << "\n=== After sorting by salary ===\n";
    company.sortBySalary();
    company.printProgrammers();
}