#pragma once
enum class Type
{
	bb,bc,unknown
};

const char* getType(Type t);
int amountOfDigits(int n);

class Ship
{
private:
	char* name=nullptr;
	static int id;
	int year;
	int amountOfGuns;
	Type type;

	void free();
	void copyFrom(const Ship& other);
public:
	Ship(int year, Type type, int amountOfuns);
	Ship();
	Ship(const Ship& other);
	Ship& operator=(const Ship& other);
	void setName();
	void setYear(int year);
	void setAmountOfGuns(int amountOfGuns);
	void setType(Type type);
	const char* getName()const;
	~Ship();
	int getAmountOfGuns()const;
};

