#pragma once
#include "Constants.h"
#include "Language.h"

class Programmer {
    char name[Constants::MAX_NAME_LEN + 1];
    unsigned age;
    unsigned salary;
    bool langs[Constants::LANGUAGES_COUNT]{};

public:
    Programmer();
    Programmer(const char* name, unsigned age, unsigned salary);

    void setSalary(unsigned salary);
    unsigned getAge() const;
    unsigned getSalary() const;
    const char* getName() const;

    void learnLanguage(Language language);
    bool knowsLanguage(Language language) const;
    void print() const;

private:
    void setName(const char* name);
    void setAge(unsigned age);
    int languageToIndex(Language language) const;
    void printLanguages() const;
};