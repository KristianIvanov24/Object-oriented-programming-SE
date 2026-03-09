#include <iostream>
#include <cstring>
#pragma warning (disable : 4996)

namespace Constants {
    const size_t MAX_NAME_LEN = 32;
    const unsigned MIN_AGE = 18;
    const unsigned MIN_SALARY = 2500;
    const unsigned MAX_SALARY = 5000;
    const char* DEFAULT_NAME = "Unknown";
    const size_t LANGUAGES_COUNT = 5;
}

enum class Language {
    CPP,
    PYTHON,
    JAVA,
    CS,
    JAVASCRIPT
};

namespace Validation {
    bool isValidName(const char* name) {
        return name && strlen(name) <= Constants::MAX_NAME_LEN;
    }

    bool isValidAge(unsigned age) {
        return age >= Constants::MIN_AGE;
    }

    bool isValidSalary(unsigned salary) {
        return salary >= Constants::MIN_SALARY
            && salary <= Constants::MAX_SALARY;
    }

    bool isValidLang(Language lang) {
        return (int)lang >= 0 && (int)lang <= Constants::LANGUAGES_COUNT;
    }
}

const char* languageToString(Language language)
{
    switch (language)
    {
    case Language::CPP:
        return "C++";
    case Language::PYTHON:
        return "Python";
    case Language::JAVA:
        return "Java";
    case Language::CS:
        return "C#";
    case Language::JAVASCRIPT:
        return "JavaScript";
    default:
        return "Unknown";
    }
}
class Programmer {
    char name[Constants::MAX_NAME_LEN + 1];
    unsigned age;
    unsigned salary;
    bool langs[Constants::LANGUAGES_COUNT]{};
public:
    Programmer(const char* name, unsigned age, unsigned salary) {
        setName(name);
        setAge(age);
        setSalary(salary);
    }

    void setSalary(unsigned salary) {
        if (!Validation::isValidSalary(salary)) {
            this->salary = salary;
            return;
        }

        this->salary = salary;
    }

    unsigned getAge() const {
        return age;
    }

    unsigned getSalary() const {
        return salary;
    }

    const char* getName() const {
        return name;
    }

    void learnLanguage(Language language) {
        if (!Validation::isValidLang(language)) {
            return;
        }

        this->langs[languageToIndex(language)] = true;
    }

    bool knowsLanguage(Language language) {
        if (!Validation::isValidLang(language)) {
            return false;
        }

        return langs[languageToIndex(language)];
    }

    void print() {
        std::cout << "|" << name << "|" << age << "|" << salary;
    }

private:
    void printLanguages() {
        for (size_t i = 0; i < Constants::LANGUAGES_COUNT; i++) {
            Language lang = (Language)i;
            if (knowsLanguage(lang)) {
                std::cout << languageToString(lang) << " ";
            }
        }
    }

    int languageToIndex(Language language) {
        return (int)language;
    }

    void setName(const char* name) {
        if (!Validation::isValidName(name)) {
            strcpy(this->name, Constants::DEFAULT_NAME);
            return;
        }

        strcpy(this->name, name);
    }

    void setAge(unsigned age) {
        if (!Validation::isValidAge(age)) {
            this->age = Constants::MIN_AGE;
            return;
        }

        this->age = age;
    }
};

int main() {
    Programmer programmer("asd", 20, 2500);
    programmer.knowsLanguage((Language)50);
}