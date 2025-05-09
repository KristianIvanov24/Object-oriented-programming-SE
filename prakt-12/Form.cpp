#include "Form.h"

void Form::free()
{
	delete[] name;
	for (size_t i = 0; i < size; i++)
		delete collection[i];

	delete[] collection;
}

void Form::copyFrom(const Form& other)
{
	size = other.size;
	capacity = other.capacity;
	width = other.width;
	lenght = other.lenght;

	name = new char(strlen(other.name) + 1);
	strcpy(name, other.name);

	collection = new Control * [capacity];
	for (size_t i = 0; i < size; i++)
	{
		collection[i] = other.collection[i]->clone();
	}
}

void Form::moveFrom(Form&& other) noexcept
{
	size = other.size;
	capacity = other.capacity;
	width = other.width;
	lenght = other.lenght;

	name = other.name;
	other.name = nullptr;

	collection = other.collection;
	other.collection = nullptr;
}

Form::Form()
{
	size = 0;
	capacity = 16;
	width = 0;
	lenght = 0;
	name = nullptr;
	collection = nullptr;
}

Form::Form(const Form& other)
{
	copyFrom(other);
}

Form::Form(Form&& other) noexcept
{
	moveFrom(std::move(other));
}

Form& Form::operator=(const Form& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Form& Form::operator=(Form&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Form::~Form()
{
	free();
}

void Form::add(const Control* toAdd)
{
	if (size == capacity)
		throw "there is no space";

	collection[size++] = toAdd->clone();
}

void Form::resizeForm(size_t width, size_t lenght)
{
	this->width = width;
	this->lenght = lenght;
}

void Form::resizeControl(size_t index, size_t size)
{
	collection[index]->resize(size);
}

void Form::changeLocation(size_t index, const Pos& location)
{
	collection[index]->changeLocation(location);
}

void Form::change(size_t index)
{
	collection[index]->setDataDialog();
}
