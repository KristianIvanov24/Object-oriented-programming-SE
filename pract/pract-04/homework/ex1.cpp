#include <iostream>
#include <cstring>

namespace Constants
{
    const size_t MAX_NAME_LEN = 32;
    const unsigned MIN_AGE = 18;
    const unsigned MIN_SALARY = 2500;
    const unsigned MAX_SALARY = 5000;
    const char *DEFAULT_NAME = "Unknown";
    const size_t LANGUAGES_COUNT = 5;
    const size_t MAX_PROGRAMMERS = 50;
}

enum class Language
{
    CPP,
    PYTHON,
    JAVA,
    CS,
    JAVASCRIPT
};

namespace Validation
{
    bool isValidName(const char *name)
    {
        return name && strnlen(name, Constants::MAX_NAME_LEN) <= Constants::MAX_NAME_LEN;
    }

    bool isValidAge(unsigned age)
    {
        return age >= Constants::MIN_AGE;
    }

    bool isValidSalary(unsigned salary)
    {
        return salary >= Constants::MIN_SALARY && salary <= Constants::MAX_SALARY;
    }

    bool isValidLang(Language lang)
    {
        return (int)lang >= 0 && (int)lang < Constants::LANGUAGES_COUNT;
    }
}

const char *languageToString(Language language)
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

class Programmer
{
    char name[Constants::MAX_NAME_LEN + 1];
    unsigned age;
    unsigned salary;
    bool langs[Constants::LANGUAGES_COUNT]{};

public:
    Programmer()
    {
        setName(Constants::DEFAULT_NAME);
        setAge(Constants::MIN_AGE);
        setSalary(Constants::MIN_SALARY);
    }

    Programmer(const char *name, unsigned age, unsigned salary)
    {
        setName(name);
        setAge(age);
        setSalary(salary);
    }

    void setSalary(unsigned salary)
    {
        if (!Validation::isValidSalary(salary))
        {
            this->salary = Constants::MIN_SALARY;
            return;
        }

        this->salary = salary;
    }

    unsigned getAge() const
    {
        return age;
    }

    unsigned getSalary() const
    {
        return salary;
    }

    const char *getName() const
    {
        return name;
    }

    void learnLanguage(Language language)
    {
        if (!Validation::isValidLang(language))
        {
            return;
        }

        this->langs[languageToIndex(language)] = true;
    }

    bool knowsLanguage(Language language) const
    {
        if (!Validation::isValidLang(language))
        {
            return false;
        }

        return langs[languageToIndex(language)];
    }

    void print() const
    {
        std::cout << " | " << name << " | " << age << " | " << salary << " | ";
        printLanguages();
    }

private:
    void printLanguages() const
    {
        for (size_t i = 0; i < Constants::LANGUAGES_COUNT; i++)
        {
            Language lang = indexToLanguage(i);
            if (knowsLanguage(lang))
            {
                std::cout << languageToString(lang) << " ";
            }
        }
    }

    size_t languageToIndex(Language language) const
    {
        return (size_t)language;
    }

    Language indexToLanguage(size_t index) const
    {
        return (Language)index;
    }

    void setName(const char *name)
    {
        if (!Validation::isValidName(name))
        {
            strncpy(this->name, Constants::DEFAULT_NAME, Constants::MAX_NAME_LEN);
            return;
        }

        strncpy(this->name, name, Constants::MAX_NAME_LEN);
        this->name[Constants::MAX_NAME_LEN] = '\0';
    }

    void setAge(unsigned age)
    {
        if (!Validation::isValidAge(age))
        {
            this->age = Constants::MIN_AGE;
            return;
        }

        this->age = age;
    }
};

class SoftwareCompany
{
    Programmer programmers[Constants::MAX_PROGRAMMERS];
    size_t numberOfProgrammers;

    double getAverage(unsigned sum) const
    {
        return sum * 1.0 / numberOfProgrammers;
    }

    unsigned getSalarySum() const
    {
        unsigned sum = 0;
        for (size_t i = 0; i < numberOfProgrammers; i++)
        {
            sum += programmers[i].getSalary();
        }
        return sum;
    }

    unsigned getAgeSum() const
    {
        unsigned sum = 0;
        for (size_t i = 0; i < numberOfProgrammers; i++)
        {
            sum += programmers[i].getAge();
        }
        return sum;
    }

    void sort(bool (*cmp)(const Programmer &, const Programmer &))
    {
        for (size_t i = 0; i < numberOfProgrammers - 1; i++)
        {
            for (size_t j = 0; j < numberOfProgrammers - i - 1; j++)
            {
                if (cmp(programmers[j], programmers[j + 1]))
                {
                    std::swap(programmers[j], programmers[j + 1]);
                }
            }
        }
    }

public:
    SoftwareCompany() : numberOfProgrammers(0) {}

    void add(const Programmer &programmer)
    {
        if (numberOfProgrammers >= Constants::MAX_PROGRAMMERS)
        {
            std::cout << "Not looking for new hires!" << std::endl;
            return;
        }

        programmers[numberOfProgrammers++] = programmer;
    }

    size_t employedProgrammers() const
    {
        return numberOfProgrammers;
    }

    void print() const
    {
        for (size_t i = 0; i < numberOfProgrammers; i++)
        {
            programmers[i].print();
        }
    }

    void printLanguage(Language language)
    {
        for (size_t i = 0; i < numberOfProgrammers; i++)
        {
            if (programmers[i].knowsLanguage(language))
                programmers[i].print();
        }
    }

    double averageSalary() const
    {
        return getAverage(getSalarySum());
    }

    double averageAge() const
    {
        return getAverage(getAgeSum());
    }

    void changeSalary(size_t programmerIndex, unsigned (*calc)(unsigned))
    {
        if (programmerIndex >= numberOfProgrammers)
        {
            std::cout << "Out of bounds!" << std::endl;
            return;
        }
        programmers[programmerIndex].setSalary(calc(programmers[programmerIndex].getSalary()));
    }

    void sortBySalary()
    {
        sort([](const Programmer &p1, const Programmer &p2)
             { return p1.getSalary() > p2.getSalary(); });
    }

    void sortByAge()
    {
        sort([](const Programmer &p1, const Programmer &p2)
             { return p1.getAge() > p2.getAge(); });
    }
};