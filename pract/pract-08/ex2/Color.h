#pragma once
class Color
{
private:

	int channels[4];

	void clamp();

public:

	Color();
	Color(int r, int g, int b, int a = 255);

	int getRed() const;
	int getGreen() const;
	int getBlue() const;
	int getAlpha() const;

	Color& operator+=(const Color& other);
	Color& operator-=(const Color& other);
	Color& operator*=(double scalar);

	int operator[](int index) const;
	int& operator[](int index);

	bool operator==(const Color& other) const;
	bool operator!=(const Color& other) const;

	operator bool() const;

};

Color operator+(const Color& lhs, const Color& rhs);
Color operator-(const Color& lhs, const Color& rhs);
Color operator*(const Color& color, double scalar);
Color operator*(double scalar, const Color& color);

Color operator*(const Color& lhs, const Color& rhs);

Color operator~(const Color& color);

std::ostream& operator<<(std::ostream& os, const Color& color);