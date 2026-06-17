#include <iostream>
#include "Color.h"
#include "Constants.h"

using constants::COLOR_MAX;
using constants::COLOR_MIN;

void Color::clamp()
{
    for(int i = 0; i < 4; i++) {
        if (channels[i] < COLOR_MIN) {
            channels[i] = COLOR_MIN;
        }
        else if (channels[i] > COLOR_MAX) {
			channels[i] = COLOR_MAX;
        }
	}
}

Color::Color() : channels{COLOR_MIN, COLOR_MIN, COLOR_MIN, COLOR_MAX}
{
}

Color::Color(int r, int g, int b, int a) : channels{r, g, b, a}
{
    clamp();
}

int Color::getRed() const
{
    return channels[0];
}

int Color::getGreen() const
{
    return channels[1];
}

int Color::getBlue() const
{
    return channels[2];
}

int Color::getAlpha() const
{
    return channels[3];
}

Color& Color::operator+=(const Color& other)
{
    for (int i = 0; i < 4; i++) {
        channels[i] += other.channels[i];
    }

	clamp();
    return *this;
}

Color& Color::operator-=(const Color& other)
{
    for (int i = 0; i < 4; i++) {
        channels[i] -= other.channels[i];
    }

    clamp();
	return *this;
}

Color& Color::operator*=(double scalar)
{
    for (int i = 0; i < 3; i++) {
        channels[i] *= scalar;
    }

    clamp();
	return *this;
}


int Color::operator[](int index) const
{
    if(index >= 0 && index < 4)
		return channels[index];

	return COLOR_MIN;
}

int& Color::operator[](int index)
{
	if (index >= 0 && index < 4)
        return channels[index];

	return channels[0];
}

bool Color::operator==(const Color& other) const
{
    for (int i = 0; i < 4; i++) {
        if (channels[i] != other.channels[i])
			return false;
    }
	return true;
}

bool Color::operator!=(const Color& other) const
{
    return !(*this == other);
}

Color::operator bool() const {
	return channels[3] > COLOR_MIN;
}

Color operator+(const Color& lhs, const Color& rhs)
{
    Color result = lhs;
	return result += rhs;
}

Color operator-(const Color& lhs, const Color& rhs)
{
    Color result = lhs;
    return result -= rhs;
}

Color operator*(const Color& color, double scalar)
{
	Color result = color;
	return result *= scalar;
}

Color operator*(double scalar, const Color& color)
{
    Color result = color;
    return result *= scalar;
}

Color operator*(const Color& lhs, const Color& rhs)
{
    return Color(
        (lhs.getRed() * rhs.getRed()) / 255,
        (lhs.getGreen() * rhs.getGreen()) / 255,
        (lhs.getBlue() * rhs.getBlue()) / 255,
        (lhs.getAlpha() * rhs.getAlpha()) / 255
    );
}

Color operator~(const Color& c)
{
    return Color(255 - c.getRed(),
        255 - c.getGreen(),
        255 - c.getBlue(),
        c.getAlpha());
}

std::ostream& operator<<(std::ostream& os, const Color& color)
{

    os << "rgba(" << color.getRed()
       << ", " << color.getGreen()
       << ", " << color.getBlue()
		<< ", " << color.getAlpha() << ")";

    return os;
}

