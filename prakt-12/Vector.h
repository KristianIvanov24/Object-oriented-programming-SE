#pragma once
#include "Container.h"

class Vector : public Container
{
public:
	Vector(const double* nums, size_t size);
	void write() const override;
	Container* clone() const override;
};

