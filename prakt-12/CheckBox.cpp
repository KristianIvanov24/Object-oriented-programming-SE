#include "CheckBox.h"

void CheckBox::setDataDialog()
{
	std::cout << "Choose default state: 1-on, 2-off: ";
	int choice;
	std::cin >> choice;
	switch (choice)
	{
	case '1': on = true; break;
	case '2': on = false; break;
	default: break;
	}
}

void CheckBox::setNewText()
{
	TextBox::setDataDialog();
}

Control* CheckBox::clone() const
{
	return new CheckBox(*this);
}
