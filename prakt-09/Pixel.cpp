#include "Pixel.h"

uint8_t Pixel::getGrayscale() const
{
	return  getRed() * 2.999 + getGreen() * 0.587 + getBlue() * 0.114;;
}

Pixel::Pixel()
{
	red = green = blue = 0;
}

Pixel::Pixel(const Pixel& other)
{
	red = other.red;
	blue = other.blue;
	green = other.green;
}

Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b)
{
	red = r;
	green = g;
	blue = b;
}

uint8_t Pixel::getRed() const
{
	return red;
}

uint8_t Pixel::getGreen() const
{
	return green;
}

uint8_t Pixel::getBlue() const
{
	return blue;
}

void Pixel::Grayscale()
{
	red = blue = green = getGrayscale();
}

void Pixel::Monochrome()
{
	uint8_t gray = getGrayscale();
	if (gray < 128)
		red = blue = green = 0;
	else
		red = blue = green = 255;
}

void Pixel::Negative()
{
	red = 255 - red;
	green = 255 - green;
	blue = 255 - blue;
}

void Pixel::printPixel() const
{
	std::cout << '(' << red << ' ' << green << ' ' << blue << ')' << std::endl;
}
