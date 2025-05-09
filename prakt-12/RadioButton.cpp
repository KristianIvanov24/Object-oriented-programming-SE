#include "RadioButton.h"

void RadioButton::free()
{
    delete[] options;
}

void RadioButton::copyFrom(const RadioButton& other)
{
    count = other.count;
    choice = other.choice;
    options = new CheckBox[count];
    options[choice].setDataDialog(); // turn it on?
}

void RadioButton::moveFrom(RadioButton&& other) noexcept
{
    count = other.count;
    choice = other.choice;
    options = other.options;
    other.options = nullptr;
}

RadioButton::RadioButton() : CheckBox()
{
    count = 0;
    choice = 0;
    options = nullptr;
}

RadioButton::RadioButton(const RadioButton& other) : CheckBox(other)
{
    copyFrom(other);
}

RadioButton::RadioButton(RadioButton&& other) noexcept : CheckBox(std::move(other))
{
    moveFrom(std::move(other));
}

RadioButton& RadioButton::operator=(const RadioButton& other)
{
    if (this != &other)
    {
        CheckBox:: operator=(other);
        free();
        copyFrom(other);
    }

    return *this;
}

RadioButton& RadioButton::operator=(RadioButton&& other) noexcept
{
    if (this != &other)
    {
        CheckBox:: operator=(std::move(other));
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

RadioButton::~RadioButton()
{
    free();
}

void RadioButton::setDataDialog()
{
    options[choice].setDataDialog(); // turn it off
    std::cout << "Choose between options (0-" << count << ": ";
    std::cin >> choice;
    options[choice].setDataDialog(); // turn it on
}

Control* RadioButton::clone() const
{
    return new RadioButton(*this);
}
