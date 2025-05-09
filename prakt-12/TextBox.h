#pragma once
#include "Control.h"
class TextBox : public Control
{
protected:
    char* text;

    void free();
    void copyFrom(const TextBox other);
    void moveFrom(TextBox&& other) noexcept;
public:
    TextBox();
    TextBox(const TextBox& other);
    TextBox(TextBox&& other) noexcept;
    TextBox& operator= (const TextBox& other);
    TextBox& operator= (TextBox&& other) noexcept;
    ~TextBox();

    void setDataDialog() override;
    Control* clone() const override;
};

