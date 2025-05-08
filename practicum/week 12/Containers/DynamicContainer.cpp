#include "DynamicContainer.h"
#include <utility>

DynamicContainer::DynamicContainer(size_t N) : N(N)
{
	data = new double[N] {};
}

void DynamicContainer::copyFrom(const DynamicContainer& other)
{
	N = other.N;
	data = new double[N] {};

	for (size_t i = 0; i < N; i++)
	{
		data[i] = other.data[i];
	}
}

void DynamicContainer::moveFrom(DynamicContainer&& other)
{
	N = other.N;
	other.N = 0;

	data = other.data;
	other.data = nullptr;
}

void DynamicContainer::free()
{
	delete[] data;
	data = nullptr;
	N = 0;
}

DynamicContainer::DynamicContainer(const double* data, size_t N)
{
	this->N = N;
	this->data = new double[N];

	for (size_t i = 0; i < N; i++)
	{
		this->data[i] = data[i];
	}
}

DynamicContainer::DynamicContainer(const DynamicContainer& other) : Container(other)
{
	copyFrom(other);
}

DynamicContainer& DynamicContainer::operator=(const DynamicContainer& other)
{
	if (this != &other)
	{
		Container::operator=(other);
		free();
		copyFrom(other);
	}
	return *this;
}

DynamicContainer::DynamicContainer(DynamicContainer&& other) noexcept : Container(std::move(other))
{
	moveFrom(std::move(other));
}

DynamicContainer& DynamicContainer::operator=(DynamicContainer&& other) noexcept
{
	if (this != &other)
	{
		Container::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

DynamicContainer::~DynamicContainer()
{
	free();
}

bool DynamicContainer::member(double num) const
{
	for (size_t i = 0; i < N; i++)
	{
		if (std::abs(data[i] - num) <= 0.000001)
		{
			return true;
		}
	}
	return false;
}

double DynamicContainer::operator[](size_t i) const
{
	return data[i];
}

size_t DynamicContainer::count() const
{
	return N;
}
