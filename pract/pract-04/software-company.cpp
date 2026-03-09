#include <iostream>
#include <cstring>
#pragma warning(disable : 4996)

namespace Constants
{
    const size_t NAME_MAX_LEN = 32;
    const size_t PROGRAMMING_LANGUAGES_COUNT = 5;
    const unsigned MIN_AGE = 18;
    const unsigned MIN_SALARY = 2500;
    const unsigned MAX_SALARY = 5000;
    const char* const DEFAULT_NAME = "Unknown";

    const size_t PROGRAMMERS_MAX_COUNT = 50;
}

enum class ProgrammingLanguage
{
    CPP,
    PYTHON,
    JAVA,
    CS,
    JAVASCRIPT
};

const char* languageToString(ProgrammingLanguage language)
{
    switch (language)
    {
    case ProgrammingLanguage::CPP:
        return "C++";
    case ProgrammingLanguage::PYTHON:
        return "Python";
    case ProgrammingLanguage::JAVA:
        return "Java";
    case ProgrammingLanguage::CS:
        return "C#";
    case ProgrammingLanguage::JAVASCRIPT:
        return "JavaScript";
    default:
        return "Unknown";
    }
}

class Programmer
{
    char name[Constants::NAME_MAX_LEN + 1];
    unsigned age;
    unsigned salary;
    bool languages[Constants::PROGRAMMING_LANGUAGES_COUNT]{};

public:
    Programmer()
    {
        setName(Constants::DEFAULT_NAME);
        setAge(Constants::MIN_AGE);
        setSalary(Constants::MIN_SALARY);
    }

    Programmer(const char* name, unsigned age, unsigned salary)
    {
        setName(name);
        setAge(age);
        setSalary(salary);
    }

    void setName(const char* name)
    {
        if (!name || strlen(name) > Constants::NAME_MAX_LEN)
        {
            strncpy(this->name, Constants::DEFAULT_NAME, Constants::NAME_MAX_LEN);
            return;
        }

        strncpy(this->name, name, Constants::NAME_MAX_LEN);
    }

    void setAge(unsigned age)
    {
        if (age < Constants::MIN_AGE)
        {
            this->age = Constants::MIN_AGE;
            return;
        }

        this->age = age;
    }

    void setSalary(unsigned salary)
    {
        if (salary < Constants::MIN_SALARY || salary > Constants::MAX_SALARY)
        {
            this->salary = Constants::MIN_SALARY;
            return;
        }

        this->salary = salary;
    }

    const char* getName() const
    {
        return name;
    }

    unsigned getAge() const
    {
        return age;
    }

    unsigned getSalary() const
    {
        return salary;
    }

    void learnProgrammingLanguage(ProgrammingLanguage language)
    {
        languages[getIndexByLanguage(language)] = true;
    }

    unsigned knowsProgrammingLanguage(ProgrammingLanguage language) const
    {
        return languages[getIndexByLanguage(language)];
    }

    void print() const
    {
        std::cout << " | " << name << " | " << age << " | " << salary << " | ";
        printLanguages();
    }

private:
    size_t getIndexByLanguage(ProgrammingLanguage language) const
    {
        return (size_t)language;
    }

    void printLanguages() const
    {
        for (unsigned i = 0; i < Constants::PROGRAMMING_LANGUAGES_COUNT; i++)
        {
            if (languages[i])
            {
                std::cout << languageToString((ProgrammingLanguage)i) << " | ";
            }
        }
    }
};

class SoftwareCompany
{
    Programmer programmers[Constants::PROGRAMMERS_MAX_COUNT];
    unsigned programmersCount;

public:
    SoftwareCompany()
    {
        programmersCount = 0;
    }

    bool addProgrammer(const Programmer& programmer)
    {
        if (programmersCount == Constants::PROGRAMMERS_MAX_COUNT)
        {
            return false;
        }

        programmers[programmersCount++] = programmer;
        return true;
    }

    unsigned getHiredCount() const
    {
        return programmersCount;
    }

    double getAverageSalary() const
    {
        return getAverageFromSum(getSumOfSalaries());
    }

    double getAverageAge() const
    {
        return getAverageFromSum(getSumOfAges());
    }

    bool changeSalaryBy(size_t programmerIndex, unsigned (*formula)(unsigned))
    {
        if (programmerIndex >= programmersCount)
        {
            return false;
        }

        Programmer &programmer = programmers[programmerIndex];
        unsigned newSalary = formula(programmer.getSalary());
        programmer.setSalary(newSalary);

        return true;
    }

    void sortBySalary()
    {
        sortBy([](const Programmer& lhs, const Programmer& rhs)
               { return lhs.getSalary() < rhs.getSalary(); });
    }

    void sortByAge()
    {
        sortBy([](const Programmer& lhs, const Programmer& rhs)
               { return lhs.getAge() < rhs.getAge(); });
    }

private:
    unsigned getSumOfSalaries() const
    {
        return getSumOf([](const Programmer& p)
                        { return p.getSalary(); });
    }

    unsigned getSumOfAges() const
    {
        return getSumOf([](const Programmer& p)
                        { return p.getAge(); });
    }

    unsigned getSumOf(unsigned (*getter)(const Programmer&)) const
    {
        unsigned sum = 0;
        for (unsigned i = 0; i < programmersCount; i++)
        {
            sum += getter(programmers[i]);
        }

        return sum;
    }

    double getAverageFromSum(unsigned sum) const
    {
        if (programmersCount == 0)
        {
            return 0;
        }

        return sum * 1.0 / programmersCount;
    }

    void sortBy(bool (*pred)(const Programmer& , const Programmer&))
    {
        if (programmersCount == 0)
        {
            return;
        }

        for (unsigned i = 0; i < programmersCount - 1; i++)
        {
            for (unsigned j = 0; j < programmersCount - i - 1; j++)
            {
                if (!pred(programmers[j], programmers[j + 1]))
                {
                    std::swap(programmers[j], programmers[j + 1]);
                }
            }
        }
    }
};
