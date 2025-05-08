#pragma once
#include "Container.h"

class DynamicContainer : public Container
{
protected:
	double* data = nullptr;
	size_t N = 0;

	explicit DynamicContainer(size_t N);

private:
	void copyFrom(const DynamicContainer& other);
	void moveFrom(DynamicContainer&& other);
	void free();

public:
	DynamicContainer(const double* data, size_t N);
	DynamicContainer(const DynamicContainer& other);
	DynamicContainer& operator=(const DynamicContainer& other);
	DynamicContainer(DynamicContainer&& other) noexcept;
	DynamicContainer& operator=(DynamicContainer&& other) noexcept;
	~DynamicContainer();

	bool member(double num) const override;
	double operator[](size_t i) const override;
	size_t count() const override;
};

