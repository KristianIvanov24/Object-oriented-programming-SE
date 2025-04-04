#pragma once

namespace constants {
	constexpr int MIN_AGE = 0;
}

enum class Type {
	mammal, 
	reptile, 
	fish, 
	bird, 
	amphibian, 
	ivertebrates,
	insect
};

class Animal
{
private:
	Type type;
	char* name;
	int age;

public:
	Animal();
	Animal(const Animal& other);
	Animal& operator=(const Animal& other);
	~Animal();

	void setType(Type& type);
	void setName(char* name);
	void setAge(int age);

	Type getType() const;
	char* getName() const;
	int getAge() const;

	void free();
	void copyFrom(const Animal& other);
};

