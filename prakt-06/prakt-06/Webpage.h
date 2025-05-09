#pragma once
#include <iostream>

class Webpage
{
private:
	char* adress;
	char* ip;

	void free();
	void moveFrom(Webpage&& other);
	void copyFrom(const Webpage& other);
public:
	Webpage();
	Webpage(const Webpage& other);
	Webpage(Webpage&& other);
	Webpage& operator=(const Webpage& other);
	Webpage& operator=(Webpage&& other);
	~Webpage();

	const char* getIp() const;
	const char* getAdress() const;

	void setIp(const char* str);
	void setAdress(const char* str);

	friend std::ostream& operator<<(std::ostream& os, const Webpage& other);
	friend std::istream& operator>>(std::istream& is, Webpage& other);
};

