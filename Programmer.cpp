#include "Programmer.h"
#include "Validation.h"
#include <iostream>
#include <cstring>
#pragma warning(disable : 4996)

Programmer::Programmer() {
    strcpy(name, Constants::DEFAULT_NAME);
    age = Constants::MIN_AGE;
    salary = Constants::MIN_SALARY;
}

Programmer::Programmer(const char* name, unsigned age, unsigned salary) {
    setName(name);
    setAge(age);
    setSalary(salary);
}

void Programmer::setSalary(unsigned salary) {
    if (!Validation::isValidSalary(salary))
        return;
    this->salary = salary;
}

unsigned Programmer::getAge() const { return age; }
unsigned Programmer::getSalary() const { return salary; }
const char* Programmer::getName() const { return name; }

void Programmer::learnLanguage(Language language) {
    if (!Validation::isValidLang(language)) return;
    langs[languageToIndex(language)] = true;
}

bool Programmer::knowsLanguage(Language language) const {
    if (!Validation::isValidLang(language)) return false;
    return langs[languageToIndex(language)];
}

void Programmer::print() const {
    std::cout << name << " | " << age << " | " << salary << " | ";
    printLanguages();
    std::cout << "\n";
}

void Programmer::setName(const char* name) {
    if (!Validation::isValidName(name)) {
        strcpy(this->name, Constants::DEFAULT_NAME);
        return;
    }
    strcpy(this->name, name);
}

void Programmer::setAge(unsigned age) {
    this->age = Validation::isValidAge(age) ? age : Constants::MIN_AGE;
}

int Programmer::languageToIndex(Language language) const {
    return (int)language;
}

void Programmer::printLanguages() const {
    for (size_t i = 0; i < Constants::LANGUAGES_COUNT; i++) {
        Language lang = (Language)i;
        if (langs[i])
            std::cout << languageToString(lang) << " ";
    }
}