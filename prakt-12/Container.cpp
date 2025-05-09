#include "Container.h"

void Container::free()
{
	delete[] nums;
	size = 0;
	nums = nullptr;
}

void Container::copyFrom(const Container& other)
{
	size = other.size;
	nums = new double[size] {0.0};
	for (size_t i = 0; i < size; i++)
	{
		nums[i] = other.nums[i];
	}
}

void Container::moveFrom(Container&& other) noexcept
{
	size = other.size;
	nums = other.nums;
	other.nums = nullptr;
}

Container::Container()
{
	size = start_size;
	nums = new double[size] {0.0};
}

Container::Container(size_t size, const double* nums)
{
	this->size = size;
	this->nums = new double[size];
	for (size_t i = 0; i < size; i++)
		this->nums[i] = nums[i];
}

Container::Container(const Container& other)
{
	copyFrom(other);
}

Container::Container(Container&& other) noexcept
{
	moveFrom(std::move(other));
}

Container& Container::operator=(const Container& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Container& Container::operator=(Container&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Container::~Container()
{
	delete[] nums;
}

bool Container::member(double x) const
{
	for (size_t i = 0; i < size; i++)
		if (nums[i] == x)
			return true;

	return false;
}

double Container::operator[](size_t i) const
{
	return nums[i];
}

int Container::count() const
{
	return size;
}

