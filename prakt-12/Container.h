#pragma once
#include <iostream>

static constexpr size_t start_size = 16;
class Container
{
protected:
	double* nums;
	size_t size;

private:
	void free();
	void copyFrom(const Container& other);
	void moveFrom(Container&& other) noexcept;

public:
	Container();
	Container(size_t size, const double* nums);
	Container(const Container& other);
	Container(Container&& other) noexcept;
	Container& operator=(const Container& other);
	Container& operator=(Container&& other) noexcept;
	virtual ~Container();

	bool member(double x) const;
	double operator[](size_t i) const;
	int count() const;

	virtual void write() const = 0;
	virtual Container* clone() const = 0;
};

