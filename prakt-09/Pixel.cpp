#include "Pixel.h"

Pixel::Pixel()
{
	red = green = blue = 0;
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
