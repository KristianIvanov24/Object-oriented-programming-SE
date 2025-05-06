#include "MyString.h"
#include <algorithm>
#pragma warning (disable : 4996)

void MyString::free()
{
	delete[] data;
	data = nullptr;
	size = 0;
	capacity = 0;
}

void MyString::copyFrom(const MyString& other)
{
	capacity = other.capacity;
	data = new char[capacity];
	strcpy(data, other.data);
	size = other.size;
}

void MyString::resize(unsigned newCapacity)
{
	char* newData = new char[newCapacity + 1];
	strcpy(newData, data);
	delete[] data;
	data = newData;
	capacity = newCapacity;
}

static unsigned roundToPowerOfTwo(unsigned v)
{
	unsigned res = 1;
	while (res < v)
	{
		res *= 2;
	}

	return res;
}

static unsigned getMaxResizeCapacity(unsigned v)
{
	return std::max(roundToPowerOfTwo(v), 16u);
}

MyString::MyString() : MyString("") {}

MyString::MyString(const char* str)
{
	if (!str)
		str = ""; 

	size = strlen(str);
	capacity = getMaxResizeCapacity(size);
	data = new char[capacity];
	strcpy(data, str);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

MyString::~MyString()
{
	free();
}

size_t MyString::getSize() const
{
	return size;
}

size_t MyString::getCapacity() const
{
	return capacity - 1;
}

const char* MyString::c_str() const
{
	return data;
}

char& MyString::operator[](unsigned index)
{
	return data[index];
}

const char& MyString::operator[](unsigned index) const
{
	return data[index];
}

MyString& MyString::operator+=(const MyString& other)
{
	if (size + other.size + 1 > capacity)
		resize(getMaxResizeCapacity(size + other.size));

	strncat(data, other.data, other.size);

	size += other.size;

	return *this;
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString res(lhs);
	res += rhs;

	return res;
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	return os << str.data;
}

std::istream& operator>>(std::istream& is, MyString& str)
{
	char buff[1024];
	is >> buff;

	size_t buffStringSize = strlen(buff);
	if (buffStringSize >= str.capacity)
		str.resize(getMaxResizeCapacity(buffStringSize));

	strcpy(str.data, buff);
	str.size = buffStringSize;

	return is;
}

MyString MyString::substr(unsigned begin, unsigned howMany)
{
	if (begin + howMany > size)
		return MyString("");

	MyString res;
	res.capacity = getMaxResizeCapacity(howMany + 1);
	res.data = new char[res.capacity];
	strncat(res.data, data + begin, howMany);
	res.size = howMany;

	return res;
}


bool operator==(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const MyString& lhs, const MyString& rhs)
{
	return !(lhs == rhs);
}

bool operator>(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator>=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}

bool operator<(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}