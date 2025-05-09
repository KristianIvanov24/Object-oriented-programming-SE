#pragma once
#include "TextBox.h"
class CheckBox : public TextBox
{
protected:
	bool on = false;
public:
	void setDataDialog() override;
	void setNewText();
	Control* clone() const override;
};

