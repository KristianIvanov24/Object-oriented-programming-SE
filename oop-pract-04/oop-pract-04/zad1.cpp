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
    const size_t MAX_PROGRAMMERS_IN_COMPANY = 50;
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
            this->salary = Constants::MIN_SALARY;
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

    bool knowsLanguage(Language language) const {
        if (!Validation::isValidLang(language)) {
            return false;
        }

        return langs[languageToIndex(language)];
    }

    void print()const {
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

    int languageToIndex(Language language)const {
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

void swapProgrammers(Programmer& p1, Programmer& p2)
{
    Programmer temp = p1;
    p1 = p2;
    p2 = temp;
}

class SoftwareCompany
{
private:
    Programmer workers[Constants::MAX_PROGRAMMERS_IN_COMPANY];
    size_t amountOfProgrammers = 0;

public:
    bool addProgrammer(const Programmer& p)
    {
        if (amountOfProgrammers >= Constants::MAX_PROGRAMMERS_IN_COMPANY)
        {
            return false;
        }
        workers[amountOfProgrammers++] = p;
        return true;
    }

    size_t returnAmountOfProgrammers() const
    {
        return amountOfProgrammers;
    }

    void printCompany() const
    {
        for (size_t i = 0; i < amountOfProgrammers; ++i)
        {
            workers[i].print();
        }
    }

    void printCompanyBySelectedLanguage(Language language) const
    {
        std::cout << "Programmers working on" << languageToString(language) << ":" << std::endl;
        for (size_t i = 0; i < amountOfProgrammers; ++i)
        {
            if (workers[i].knowsLanguage(language))
            {
                workers[i].print();
            }
        }
    }

    double calculateAverageSalary() const
    {
        double sum = 0;
        for (size_t i = 0; i < amountOfProgrammers; ++i)
        {
            sum += workers[i].getSalary();
        }
        return sum / amountOfProgrammers;
    }

    double calculateAverageAge() const
    {
        double sum = 0;
        for (size_t i = 0; i < amountOfProgrammers; ++i)
        {
            sum += workers[i].getAge();
        }
        return sum / amountOfProgrammers;
    }

    void changeSalary(unsigned(*p)(unsigned), Programmer& p1)
    {
        p1.setSalary(p(p1.getSalary()));
    }

    void sortBySalary()
    {
        for (int i = 0; i < amountOfProgrammers - 1; ++i)
        {
            for (int j = i + 1; j < amountOfProgrammers; ++j)
            {
                if (workers[i].getSalary() < workers[j].getSalary())
                {
                    swapProgrammers(workers[i], workers[j]);
                }
            }
        }
    }
};