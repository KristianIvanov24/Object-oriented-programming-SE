#include<iostream>
#include<cstring>
#pragma warning(disable: 4996)

void newline();

namespace constants {
	constexpr size_t NAME_SIZE = 32;
	constexpr size_t MIN_AGE = 18;
	constexpr size_t MAX_SALARY = 5000;
	constexpr size_t MIN_SALARY = 2500;
	constexpr size_t MAX_PROGRAMMERS = 50;
	constexpr size_t MAX_COMPANY_NAME = 32;
}

enum class Languages{
	Cpp = 1,
	Python = 2,
	Java = 4,
	Csharp = 8,
	JavaScript = 16
};

using namespace constants;

class Programmer {
	uint8_t languagesMask;
	char name[NAME_SIZE + 1];
	unsigned salary;
	unsigned age;

	void setName(const char* name) {
		if (!name || strlen(name) > NAME_SIZE){
			strcpy(this->name, "");
			return;
		}
		strcpy(this->name, name);
	}
	void setAge(const int age) {
		if (age < MIN_AGE) {
			this->age = MIN_AGE;
			return;
		}

		this->age = age;
	}
	void printLanguages() const{
		if (knowsLanguage(Languages::Cpp)) {
			std::cout << "C++\t";
		}
		if (knowsLanguage(Languages::Python)) {
			std::cout << "Python\t";
		}
		if (knowsLanguage(Languages::Java)) {
			std::cout << "Java\t";
		}
		if (knowsLanguage(Languages::Csharp)) {
			std::cout << "Csharp\t";
		}
		if (knowsLanguage(Languages::JavaScript)) {
			std::cout << "JavaScript\t";
		}
	}

public:

	Programmer() {

		strcpy(name, "");
		age = MIN_AGE;
		salary = MIN_SALARY;
		languagesMask = 0;
	}

	Programmer(const char* name, unsigned age, unsigned salary) {
		setName(name);
		setAge(age);
		setSalary(salary);
		languagesMask = 0;
	}
	const char* getName() const{
		return name;
	}
	unsigned getSalary() const {
		return salary;
	}
	unsigned getAge() const {
		return age;
	}

	void setSalary(unsigned salary) {
		if (salary > MAX_SALARY || salary < MIN_SALARY) {
			this->salary = MIN_SALARY;
			return;
		}

		this->salary = salary;
	}
	void addLanguage(Languages lang) {
		languagesMask |= (uint8_t)lang;

	}
	void removeLanguage(Languages lang) {
		languagesMask &= ~(uint8_t)lang;
	}

	bool knowsLanguage(Languages lang) const {
		return (languagesMask & (uint8_t)lang) != 0;
	}

	void printProgrammer() const{
		std::cout << "Name: " << this->name << std::endl;
		std::cout << "Salary: " << this->salary << std::endl;
		std::cout << "Age: " << this->age << std::endl;
		std::cout << "Languages: "; printLanguages();
	}

};

class SoftwareCompany {
	char companyName[MAX_COMPANY_NAME + 1];
	Programmer programmers[MAX_PROGRAMMERS];
	unsigned size = 0;

	void printLanguage(const int number)const {
		switch (number) {
			case 1:std::cout << "C++"; break;
			case 4:std::cout << "Java"; break;
			case 2:std::cout << "Python"; break;
			case 8:std::cout << "Csharp"; break;
			case 16:std::cout << "JavaScript"; break;
			default: std::cout << "Unknown"; break;
		}
	}

public:

	SoftwareCompany() {
		strcpy(companyName, "");
	}
	SoftwareCompany(const char* companyName) {
		if (!companyName || strlen(companyName) > MAX_COMPANY_NAME) {
			strcpy(this->companyName, "");
			return;
		}
		strcpy(this->companyName, companyName);
	}

	void addProgrammer(const Programmer& programmer) {
		if (size >= constants::MAX_PROGRAMMERS) {
			return;
		}
		programmers[size++] = programmer;
	}
	unsigned getSize() const{
		return size;
	}
	const char* getCompanyName() const{
		return companyName;
	}
	void setCompanyName(const char* companyName) {
		if (!companyName || strlen(companyName) > MAX_COMPANY_NAME) {
			strcpy(this->companyName, "");
			return;
		}
		strcpy(this->companyName, companyName);
	}
	void printCompany() const{
		std::cout << this->companyName << ":";
		for (int i = 0; i < this->size; i++) {
			programmers[i].printProgrammer();
			newline();
		}
	}
	void printLanguage(Languages lang)const {
		printLanguage((int)lang); std::cout << ":";
		bool exist = false;
		for (int i = 0; i < size; i++) {
			if (programmers[i].knowsLanguage(lang)) {
				std::cout << std::endl;
				programmers[i].printProgrammer(); newline();
				exist = true;
			}
		}
		if (!exist) {
			std::cout << "\tNo programmers know this language";
		}
	}
	size_t getAverageSalary() const {
		if (size == 0) {
			return 0;
		}
		unsigned sum = 0;
		for (int i = 0; i < size; i++) {
			sum += programmers[i].getSalary();
		}
		return sum / size;
	}
	size_t getAverageAge() const {
		if (size == 0) {
			return 0;
		}
		unsigned sum = 0;
		for (int i = 0; i < size; i++) {
			sum += programmers[i].getAge();
		}
		return sum / size;
	}
	void updateSalary(double (*formula)(double), const char* name) {
		if (!name || strlen(name) > NAME_SIZE) {
			return;
		}

		for (int i = 0; i < size; i++) {
			if (strcmp(programmers[i].getName(), name) == 0) {
				programmers[i].setSalary(formula(programmers[i].getSalary()));
				return;
			}
		}
	}
	void sortProgrammersSalary() {
		for (int i = 0; i < size - 1; i++) {
			for (int j = i + 1; j < size; j++) {
				if (programmers[i].getSalary() > programmers[j].getSalary()) {
					std::swap(programmers[i], programmers[j]);
				}
			}
		}
	}
	void sortProgrammersAge() {
		for (int i = 0; i < size - 1; i++) {
			for (int j = i + 1; j < size; j++) {
				if (programmers[i].getAge() > programmers[j].getAge()) {
					std::swap(programmers[i], programmers[j]);
				}
			}
		}
	}
	
};
	
namespace salary {
	double increaseSalary(double currentSalary) {
		return currentSalary * 1.1;
	}
	double decreaseSalary(double currentSalary) {
		return currentSalary * 0.95;
	}
}



int main() {

	Programmer programmer("Nikola",19,3000);
	Programmer programmer2("Martin", 19, 2500);
	programmer.setSalary(4000);
	programmer2.addLanguage(Languages::Cpp);
	programmer2.addLanguage(Languages::Java);
	

	//std::cout<<programmer.getName();

	programmer.addLanguage(Languages::Cpp);
	programmer.addLanguage(Languages::Python);

	//std::cout<<programmer.knowsLanguage(Languages::Java);

	//programmer.addLanguage(Languages::JavaScript);
	std::cout << std::endl;
	programmer.printProgrammer(); newline();

	SoftwareCompany company("M2M services");

	company.addProgrammer(programmer);
	company.addProgrammer(programmer2);
	//std::cout << company.getSize();
	//std::cout << std::endl; newline();
	company.printCompany();
	newline();

	company.printLanguage(Languages::Java);

	std::cout << company.getAverageSalary();
	std::cout << "\t" << company.getAverageAge();

	company.updateSalary(salary::increaseSalary,"Nikola");
	company.printCompany();

	return 0;
}

void newline() {
	std::cout << std::endl << std::endl;
}