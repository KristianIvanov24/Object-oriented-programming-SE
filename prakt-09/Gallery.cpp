#include "Gallery.h"


void Gallery::copyFrom(const Gallery& other)
{
	capacity = other.capacity;
	pictureCnt = other.pictureCnt;
	collection = new Picture * [capacity] {nullptr};
	for (size_t i = 0; i < pictureCnt; i++)
	{
		collection[i] = other.collection[i];
	}
}

void Gallery::moveFrom(Gallery&& other)
{
	capacity = other.capacity;
	pictureCnt = other.pictureCnt;
	collection = other.collection;
	other.collection = nullptr;
}

void Gallery::free()
{
	for (size_t i = 0; i < pictureCnt; i++)
	{
		delete collection[i];
		collection[i] = nullptr;
	}

	delete[] collection;
}

void Gallery::resize()
{
	Picture** newCollection = new Picture * [capacity*2] {nullptr};
	for (size_t i = 0; i < pictureCnt; i++)
	{
		newCollection[i] = collection[i];
	}

	for (size_t i = 0; i < pictureCnt; i++)
	{
		delete collection[i];
		collection[i] = nullptr;
	}
	delete[] collection;

	collection = newCollection;
}

Gallery::Gallery()
{
	collection = nullptr;
	capacity = 0;
	pictureCnt = 0;
}

Gallery::Gallery(const Gallery& other)
{
	copyFrom(other);
}

Gallery::Gallery(Gallery&& other)
{
	moveFrom(std::move(other));
}

Gallery& Gallery::operator=(const Gallery& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Gallery& Gallery::operator=(Gallery&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Gallery::~Gallery()
{
	free();
}

void Gallery::addPicture(Picture& pic)
{
	if (pictureCnt == capacity)
		resize();

	collection[pictureCnt++] = &pic;
}

void Gallery::removePicByIndex(size_t index)
{
	delete collection[index];
	for (size_t i = index; i < pictureCnt; i++)
	{
		collection[i] = collection[i + 1];
	}
	collection[pictureCnt--] = nullptr;
}

void Gallery::filterOne(Filter filter, size_t index)
{
	switch (filter)
	{
	case Filter::grayscale: collection[index]->Grayscale();
	case Filter::monochrome: collection[index]->Monochrome();
	case Filter::negative: collection[index]->Negative();
	}
}

void Gallery::filterAll(Filter filter)
{
	for (size_t i = 0; i < pictureCnt; i++)
	{
		filterOne(filter, i);
	}
}

const Picture& Gallery::operator[](size_t index) const
{
	return *collection[index];
}

void Gallery::print() const
{
	for (size_t i = 0; i < pictureCnt; i++)
	{
		collection[i]->printPixels();
	}
}


