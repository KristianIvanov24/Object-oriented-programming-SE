#pragma once
#include "Picture.h"
enum Filter
{
	monochrome,
	grayscale,
	negative
};
class Gallery
{
private:
	Picture** collection;
	size_t pictureCnt;
	size_t capacity;

	void copyFrom(const Gallery& other);
	void moveFrom(Gallery&& other);
	void free();

	void resize();
public:
	Gallery();
	Gallery(const Gallery& other);
	Gallery(Gallery&& other);
	Gallery& operator=(const Gallery& other);
	Gallery& operator=(Gallery&& other);
	~Gallery();

	void addPicture(Picture& pic);
	void removePicByIndex(size_t index);
	void filterOne(Filter filter, size_t index);
	void filterAll(Filter filter);
	const Picture& operator[](size_t index) const;
	void print() const;
};

