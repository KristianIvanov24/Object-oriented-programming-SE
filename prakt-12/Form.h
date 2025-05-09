#pragma once
#include "Control.h"

class Form
{
private:
	size_t width, lenght;
	char* name;
	Control** collection;
	size_t size;
	size_t capacity;

	void free();
	void copyFrom(const Form& other);
	void moveFrom(Form&& other) noexcept;
public:
	Form();
	Form(const Form& other);
	Form(Form&& other) noexcept;
	Form& operator= (const Form& other);
	Form& operator= (Form&& other) noexcept;
	~Form();

	void add(const Control* toAdd);
	void resizeForm(size_t width, size_t lenght);
	void resizeControl(size_t index, size_t size);
	void changeLocation(size_t index, const Pos& location);
	void change(size_t index);
};

