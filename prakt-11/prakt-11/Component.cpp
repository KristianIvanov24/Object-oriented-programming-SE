#include "Component.h"

void Component::free()
{
	delete[] lable;
}

void Component::moveFrom(Component&& other) noexcept
{
	lable = other.lable;
	other.lable = nullptr;
}

void Component::copyFrom(const Component& other)
{
	lable = new char[strlen(other.lable) + 1];
	strcpy(lable, other.lable);
}

Component::Component()
{
	lable = nullptr;
}

Component::Component(const char* lable)
{
	if (lable)
	{
		this->lable = new char[strlen(lable) + 1];
		strcpy(this->lable, lable);
	}
	else
		throw std::invalid_argument("invalid lable");
}

Component::Component(const Component& other)
{
	copyFrom(other);
}

Component::Component(Component&& other) noexcept
{
	moveFrom(std::move(other));
}

Component& Component::operator=(const Component& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Component& Component::operator=(Component&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Component::~Component()
{
	free();
}

const char* Component::getLable() const
{
	return lable;
}
