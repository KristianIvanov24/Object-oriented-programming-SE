#include "TextBox.h"

void TextBox::free()
{
	delete[] text;
}

void TextBox::copyFrom(const TextBox other)
{
	this->text = new char[strlen(other.text) + 1];
	strcpy(this->text, other.text);
}

void TextBox::moveFrom(TextBox&& other) noexcept
{
	this->text = other.text;
	other.text = nullptr;
}

TextBox::TextBox() : Control()
{
	text = nullptr;
}

TextBox::TextBox(const TextBox& other) : Control(other)
{
	copyFrom(other);
}

TextBox::TextBox(TextBox&& other) noexcept : Control(std::move(other))
{
	moveFrom(std::move(other));
}

TextBox& TextBox::operator=(const TextBox& other)
{
	if (this != &other)
	{
		Control::operator= (other);
		free();
		copyFrom(other);
	}

	return *this;
}

TextBox& TextBox::operator=(TextBox&& other) noexcept
{
	if (this != &other)
	{
		Control::operator= (std::move(other));
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

TextBox::~TextBox()
{
	free();
}

void TextBox::setDataDialog()
{
	std::cout << "Enter new text: ";
	char buffer[1024];
	std::cin.getline(buffer, 1024);
	delete[] text;
	text = new char[strlen(buffer) + 1];
	strcpy(text, buffer);
}

Control* TextBox::clone() const
{
	return new TextBox(*this);
}
