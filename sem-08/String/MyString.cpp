#include "MyString.h"
#pragma warning(disable : 4996)

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
	size = other.size;
	data = new char[capacity];
	strcpy(data, other.data);
}

void MyString::moveFrom(MyString&& other)
{
	size = other.size;
	capacity = other.capacity;

	other.size = 0;
	other.capacity = 0;

	data = other.data;
	other.data = nullptr;
}

void MyString::resize(unsigned newCapacity)
{
	char* newData = new char[newCapacity + 1];
	strcpy(newData, data);

	delete[] data;

	data = newData;
	capacity = newCapacity;
}


MyString::MyString() : MyString("") {}

MyString::MyString(const char* str)
{
	if (!str)
		str = "";

	size = strlen(str);
	capacity = size;
	data = new char[capacity + 1];
	strcpy(data, str);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString::MyString(MyString&& other)
{
	moveFrom(std::move(other));
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

MyString& MyString::operator=(MyString&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
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
	return capacity;
}

const char* MyString::c_str() const
{
	return data;
}

MyString MyString::substr(unsigned begin, unsigned howMany)
{
	if (begin + howMany > size)
		return MyString("");

	MyString res;
	res.capacity = howMany + 1;
	res.data = new char[capacity];
	strncpy(res.data, data + begin, howMany);
	res.size = howMany;

	return res;
}


MyString& MyString::operator+=(const MyString& other)
{
	if (size + other.size > capacity)
		resize(size + other.size + 1);

	strcat(data + size, other.data);
	size += other.size;

	return *this;
}

char& MyString::operator[](unsigned index) // str[3] = '3'
{
	return data[index];
}

const char& MyString::operator[](unsigned index) const // std::cout << str[3]; char c = str[2];
{
	return data[index];
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	return os << str.data;
}

std::istream& operator>>(std::istream& is, MyString& str)
{
	char buff[1024];
	is >> buff;

	size_t buffSize = strlen(buff);
	if (buffSize >= str.capacity)
		str.resize(buffSize + 1);

	strcpy(str.data, buff);
	str.size = buffSize;

	return is;
}

bool operator==(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.data, rhs.data) == 0;
}

bool operator!=(const MyString& lhs, const MyString& rhs)
{
	return !(lhs == rhs);
}

std::strong_ordering operator<=>(const MyString& lhs, const MyString& rhs)
{
	int cmp = strcmp(lhs.data, rhs.data);
	if (cmp < 0)
		return std::strong_ordering::less;
	else if (cmp > 0)
		return std::strong_ordering::greater;
	else
		return std::strong_ordering::equal;
}


MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString res = lhs;
	res += rhs;

	return res;
}