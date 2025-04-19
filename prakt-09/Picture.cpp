#include "Picture.h"

void Picture::copyFrom(const Picture& other)
{
	rows = other.rows;
	matrix = new Pixel * [rows];
	for (size_t i = 0; i < rows; i++)
	{
		matrix[i] = new Pixel[cols];
		for (size_t j = 0; j < cols; j++)
		{
			matrix[j][i] = other.matrix[i][j];
		}
	}
}

void Picture::moveFrom(Picture&& other)
{
	rows = other.rows;
	cols = other.cols;
	matrix = other.matrix;
	other.matrix = nullptr;
}

void Picture::free()
{
	for (size_t i = 0; i < rows; i++)
	{
		delete[] matrix[i];
	}

	delete[] matrix;
}


bool Picture::isColored() const
{
	for(size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			if (matrix[i][j].getRed() == 0 && matrix[i][j].getGreen() == 0 && matrix[i][j].getBlue() == 0)
				return false;
		}
	}
	return true;
}

Picture::Picture()
{
	cols = rows = 0;
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
	for (size_t i = 0; i < rows; i++)
	{
		for(size_t j = 0; j < cols; j++)
			matrix[i][j].Grayscale();
	}

}

void Picture::Monochrome()
{
	if (!isMonochrome)
	{
		isMonochrome == true;
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < cols; j++)
				matrix[i][j].Monochrome();
		}
	}
	else
	{
		throw std::logic_error("error");
	}
}

void Picture::Negative()
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
			matrix[i][j].Negative();
	}
}

void Picture::printPixels() const
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			matrix[i][j].printPixel();
			std::cout << ' ';
		}
	}
	
}
