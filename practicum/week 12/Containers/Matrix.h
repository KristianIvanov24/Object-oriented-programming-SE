#pragma once
#include "DynamicContainer.h"

class Matrix : public DynamicContainer
{
	size_t size = 0;
public:
	Matrix(const double* const* data, size_t N);
	virtual void write() const override;
	virtual Container* clone() const override;
};

