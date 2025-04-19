#pragma once
#include "Pixel.h"

class Picture
{
private:
	Pixel** matrix;
	size_t rows, cols;

	void copyFrom(const Picture& other);
	void moveFrom(Picture&& other);
	void free();

	bool isColored() const;
	bool isMonochrome = false;
public:
	Picture();
	Picture(const Picture& other);
	Picture(Picture&& other);
	Picture& operator=(const Picture& other);
	Picture& operator=(Picture&& other);
	~Picture();

	void Grayscale();
	void Monochrome();
	void Negative();
	void printPixels() const;
};

