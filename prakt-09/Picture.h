#pragma once
#include "Pixel.h"

class Picture
{
private:
	Pixel** matrix;
	size_t pixelsCnt;

	void copyFrom(const Picture& other);
	void moveFrom(Picture&& other);
	void free();
	
	uint8_t getGrayscale(const Pixel& p) const;
 	void printPixel(Pixel& p) const;

	bool isColored();
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

