#pragma once
#include "CheckBox.h"
class RadioButton : public CheckBox
{
private:
	CheckBox* options;
	size_t count;
	size_t choice = 0;

	void free();
	void copyFrom(const RadioButton& other);
	void moveFrom(RadioButton&& other) noexcept;
public:
	RadioButton();
	RadioButton(size_t count);
	RadioButton(const RadioButton& other);
	RadioButton(RadioButton&& other) noexcept;
	RadioButton& operator= (const RadioButton& other);
	RadioButton& operator= (RadioButton&& other) noexcept;
	~RadioButton();

	void setDataDialog() override;
	Control* clone() const override;
};

