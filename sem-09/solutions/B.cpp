#include "B.h"
#include <utility>

void B::free()
{
    for(int i =0; i < size; i++)
        delete data[i];
    
    delete[] data;
}

void B::copyFrom(const B& other)
{
    size = other.size;
    capacity = other.capacity;

    data = new A*[capacity] {nullptr};
	for (int i = 0; i < capacity; i++)
	{
		data[i] = new A(*other.data[i]);
	}
}

void B::moveFrom(B&& other)
{
    data = other.data;
	other.data = nullptr;

	capacity = other.capacity;
	size = other.size;
	
	other.size = 0; 
}

void B::resize(size_t newCap)
{
    A** newDataPtr = new A * [newCap] {nullptr};
	
	for (int i = 0; i < capacity; i++)
		newDataPtr[i] = data[i];

	delete[] data;
	data = newDataPtr;

	capacity = newCap;
}

B::B()
{
    capacity = 8;
	data = new A*[capacity] {nullptr};
    size = 0;
}

B::B(const B& other)
{
    copyFrom(other);
}

B& B::operator=(const B& other)
{
    if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

B::~B()
{
    free();
}

B::B(B&& other) noexcept
{
    moveFrom(std::move(other));
}

B& B::operator=(B&& other) noexcept
{
    if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

void B::add(const A& obj)
{
    if(capacity == size)
        resize(capacity * 2);

    data[size++] = new A(obj);
}
