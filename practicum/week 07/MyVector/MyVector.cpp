#include "MyVector.h"

size_t MyVector::getNextPowerOfTwo(size_t number)
{
	number |= (number >> 1);
	number |= (number >> 2);
	number |= (number >> 4);
	number |= (number >> 8);
	number |= (number >> 16);
	number |= (number >> 32);
	++number;
	return number;
}

void MyVector::resize(size_t newCapacity)
{	
	int* newData = new int[newCapacity];
	for (size_t i = 0; i < size; ++i)
	{
		newData[i] = data[i];
	}
	delete[] data;
	data = newData;
	capacity = newCapacity;
}

void MyVector::copyFrom(const MyVector& other)
{
	data = new int[other.capacity];
	for (size_t i = 0; i < other.size; ++i)
	{
		data[i] = other.data[i];
	}
	size = other.size;
	capacity = other.capacity;
}

void MyVector::free()
{
	delete[] data;
	data = nullptr;
	size = 0;
	capacity = 0;
}

MyVector::MyVector()
{
	data = new int[INITIAL_CAPACITY];
	capacity = INITIAL_CAPACITY;
	size = 0;
}

MyVector::MyVector(size_t size)
{
	capacity = getNextPowerOfTwo(size);
	data = new int[capacity];
	this->size = size;
}

MyVector::MyVector(const MyVector& other)
{
	copyFrom(other);
}

MyVector& MyVector::operator=(const MyVector& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

MyVector::~MyVector()
{
	free();
}

void MyVector::push_back(int element)
{
	if (size == capacity)
	{
		resize(getNextPowerOfTwo(capacity)); // or 2 * capacity 
	}
	data[size++] = element;
}

void MyVector::pop_back()
{
	if (size > 0)
	{
		--size;
	}
}

void MyVector::insertAt(size_t index, int element)
{
	if (index > size)
	{
		return;
	}
	if (size == capacity)
	{
		resize(getNextPowerOfTwo(capacity)); // or 2 * capacity
	}
	for (size_t i = size; i > index; --i)
	{
		data[i] = data[i - 1];
	}
	data[index] = element;
	++size;
}

void MyVector::removeAt(size_t index)
{
	if (index >= size)
	{
		return;
	}
	for (size_t i = index; i < size - 1; ++i)
	{
		data[i] = data[i + 1];
	}
	--size;
}

void MyVector::clear()
{
	size = 0;
}

void MyVector::shrink_to_fit()
{
	capacity = size;
	int* newData = new int[capacity];
	for (size_t i = 0; i < size; ++i)
	{
		newData[i] = data[i];
	}
	delete[] data;
	data = newData;
}

bool MyVector::isEmpty() const
{
	return size == 0;
}

size_t MyVector::getSize() const
{
	return size;
}

size_t MyVector::getCapacity() const
{
	return capacity;
}

int& MyVector::operator[](size_t index)
{
	return data[index];
}

const int& MyVector::operator[](size_t index) const
{
	return data[index];
}
