#pragma once
class KBaseNumber
{
private:
	char* numberInKBase = nullptr;
	unsigned base = 10;
public:
	void free();
	void copyFrom(const KBaseNumber&);

	KBaseNumber();
	KBaseNumber(const char*, unsigned);
	KBaseNumber(const KBaseNumber&);
	KBaseNumber& operator=(const KBaseNumber&);
	~KBaseNumber();

	void update(const char*, unsigned);
	void print() const;
	char* getNumber() const;

	KBaseNumber convertToDecimal() const;
	KBaseNumber convertTo(unsigned);

	int compareWith(const KBaseNumber&);

	void saveToFile(const char*) const;
	void readFromFile(const char*);

};

