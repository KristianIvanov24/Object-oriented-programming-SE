#pragma once
#include <iostream>
#include <stdexcept>

class Pixel
{
private:
	uint8_t red, green, blue;

	uint8_t getGrayscale() const;
public:
	Pixel();
	Pixel(const Pixel& other);
	Pixel(uint8_t r, uint8_t g, uint8_t b);
	uint8_t getRed() const;
	uint8_t getGreen() const;
	uint8_t getBlue() const;

	void Grayscale();
	void Monochrome();
	void Negative();
	void printPixel() const;
};

