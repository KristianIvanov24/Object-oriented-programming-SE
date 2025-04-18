#include <iostream>
#include <cstring>
#pragma warning (disable : 4996)

namespace Constants
{
	constexpr size_t MAX_NAME_LEN = 32;
	constexpr unsigned MIN_AGE = 18;
	constexpr unsigned MIN_SALARY = 2500;
	constexpr unsigned MAX_SALARY = 5000;
	constexpr size_t PROGRAMMING_LANGUAGES_COUNT = 5;
}

enum class ProgrammingLanguages
{
	Cpp,
	Python,
	Java,
	Csharp,
	Javascript
};

const char* getLanguageString(ProgrammingLanguages langauge)
{
	switch (langauge)
	{
	case ProgrammingLanguages::Cpp:
		return "C++";
	case ProgrammingLanguages::Python:
		return "Python";
	case ProgrammingLanguages::Java:
		return "Java";
	case ProgrammingLanguages::Csharp:
		return "C#";
	case ProgrammingLanguages::Javascript:
		return "Javascript";
	}

	return "Unknown";
}

class Programmer
{
private:
	char name[Constants::MAX_NAME_LEN + 1]{};
	unsigned age = 0;
	unsigned salary = 0;
	uint8_t languages = 0;

	void setName(const char* name)
	{
		if (!name || strlen(name) > Constants::MAX_NAME_LEN)
		{
			strcpy(this->name, "Unknown");
		}

		strcpy(this->name, name);
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

	void printProgrammingLanguages() const
	{
		for (size_t i = 0; i < Constants::PROGRAMMING_LANGUAGES_COUNT; i++)
		{
			if (languages & (1 << i))
			{
				std::cout << getLanguageString((ProgrammingLanguages)i) << ' ';
			}
		}
	}

public:

	Programmer() = default;

	Programmer(const char* name, unsigned age, unsigned salary)
	{
		setName(name);
		setAge(age);
		setSalary(salary);
	}

	void setSalary(unsigned salary)
	{
		if (Constants::MIN_SALARY > salary || salary > Constants::MAX_SALARY)
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

	void learnProgrammingLanguage(ProgrammingLanguages language)
	{
		languages |= 1 << (int)language;
	}

	bool knowsProgrammingLanguage(ProgrammingLanguages language) const
	{
		return (languages & (1 << (int)languages)) != 0;
	}

	void print() const
	{
		std::cout << name << " | " << age << " | " << salary<< " | ";
		printProgrammingLanguages();
	}
};

int main()
{
	Programmer pr("Ivan", 40, 3000);

	pr.learnProgrammingLanguage(ProgrammingLanguages::Python);
	pr.learnProgrammingLanguage(ProgrammingLanguages::Cpp);

	std::cout << pr.knowsProgrammingLanguage(ProgrammingLanguages::Java)<<std::endl;
	pr.print();
	return 0;
}
