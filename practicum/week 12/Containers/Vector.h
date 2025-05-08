#pragma once
#include "DynamicContainer.h"

class Vector : public DynamicContainer
{
public:
	Vector(const double* data, size_t N);
	virtual void write() const override;
	virtual Container* clone() const override;
};

