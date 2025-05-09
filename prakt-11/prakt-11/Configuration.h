#pragma once
#include <iostream>
#include "Component.h"

class Configuration // computer components configuration - immutable objects
{
protected:
	Component** components;
	size_t size = 0;
	size_t capacity = 0;

	void moveFrom(Configuration&& other) noexcept;
	void copyFrom(const Configuration& other);
	void free();
	void resize();
public:
	Configuration();
	Configuration(const Configuration& other);
	Configuration(Configuration&& other);
	Configuration& operator=(const Configuration& other);
	Configuration& operator=(Configuration&& other) noexcept;
	~Configuration();

	void insert(Component* component);
	size_t getSize() const;
	double price() const;

	const Component& operator[] (size_t index) const;
	friend std::ostream& operator<<(std::ostream& os, const Configuration& conf);
};

