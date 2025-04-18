#pragma once
#include <iostream>
#include <stdexcept>

class Pixel
{
private:
	uint8_t red, green, blue;
public:
	Pixel();
	Pixel(uint8_t r, uint8_t g, uint8_t b);
	uint8_t getRed() const;
	uint8_t getGreen() const;
	uint8_t getBlue() const;

};

