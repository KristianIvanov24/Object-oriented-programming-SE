#include "Picture.h"

void Picture::copyFrom(const Picture& other)
{
	pixelsCnt = other.pixelsCnt;
	matrix = new Pixel * [pixelsCnt];
	for (size_t i = 0; i < pixelsCnt; i++)
	{
		matrix[i] = other.matrix[i];
	}
}

void Picture::moveFrom(Picture&& other)
{
	pixelsCnt = other.pixelsCnt;
	matrix = other.matrix;
	other.matrix = nullptr;
}

void Picture::free()
{
	for (size_t i = 0; i < pixelsCnt; i++)
	{
		delete matrix[i];
	}

	delete[] matrix;
}

uint8_t Picture::getGrayscale(const Pixel& p) const
{
	return  p.getRed() * 2.999 + p.getGreen() * 0.587 +p.getBlue() * 0.114;;
}

void Picture::printPixel( Pixel& p) const
{
	std::cout << '(' << p.getRed() << ' ' << p.getGreen() << ' ' << p.getBlue() << ')' << std::endl;
}

bool Picture::isColored()
{
	for (size_t i = 0; i < pixelsCnt; i++)
	{
		if (matrix[i]->getRed() ==0 && matrix[i]->getGreen() == 0 && matrix[i]->getBlue() == 0)
			return false;
	}
	return true;
}

Picture::Picture()
{
	pixelsCnt = 0;
	matrix = nullptr;
}

Picture::Picture(const Picture& other)
{
	copyFrom(other);
}

Picture::Picture(Picture&& other)
{
	moveFrom(std::move(other));
}

Picture& Picture::operator=(const Picture& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Picture& Picture::operator=(Picture&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
	
}

Picture::~Picture()
{
	free();
}

void Picture::Grayscale()
{
	if (!isColored())
		throw std::logic_error("error");
	for (size_t i = 0; i < pixelsCnt; i++)
	{
		uint8_t gray = getGrayscale(*matrix[i]);
		*matrix[i] = Pixel(gray, gray, gray);
	}

}

void Picture::Monochrome()
{
	if (!isMonochrome)
	{
		isMonochrome == true;
		for (size_t i = 0; i < pixelsCnt; i++)
		{
			uint8_t gray = getGrayscale(*matrix[i]);
			if (gray < 128)
				*matrix[i] = { 0,0,0 };
			else
				*matrix[i] = { 255,255,255 };
		}
	}
	else
	{
		throw std::logic_error("error");
	}
}

void Picture::Negative()
{
	for (size_t i = 0; i < pixelsCnt; i++)
	{
		*matrix[i] = { 255 - matrix[i]->getRed(), 255 - matrix[i]->getGreen(), 255 - matrix[i]->getBlue()};
	}
}

void Picture::printPixels() const
{
	for (size_t i = 0; i < pixelsCnt; i++)
	{
		printPixel(*matrix[i]);
		std::cout << ' ';
	}
}
