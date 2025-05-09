#pragma once
#include "Container.h"

class Matrix : public Container
{
private:
	size_t n;
public:
	Matrix(size_t size, const double* const* matrix);
	void write() const override;
	Container* clone() const override;
};

