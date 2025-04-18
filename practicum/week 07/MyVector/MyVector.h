#pragma once
class MyVector
{
public:
	MyVector();
	MyVector(size_t size);
	MyVector(const MyVector& other);
	MyVector& operator=(const MyVector& other);
	~MyVector();

	void push_back(int element);
	void pop_back();
	void insertAt(size_t index, int element);
	void removeAt(size_t index);
	void shrink_to_fit();
	void clear();
	bool isEmpty() const;
	size_t getSize() const;
	size_t getCapacity() const;
	int& operator[](size_t index);
	const int& operator[](size_t index) const;

private:

	static constexpr size_t INITIAL_CAPACITY = 8;

	size_t size = 0;
	size_t capacity = 0;
	int* data = nullptr;

	void free();
	void copyFrom(const MyVector& other);

	void resize(size_t newCapacity);
	static size_t getNextPowerOfTwo(size_t number);
};
