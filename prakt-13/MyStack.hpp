#include <iostream>

constexpr int INITIAL_CAPACITY = 8;
template <typename T>
class MyStack
{
private:
	T* data;
	size_t size;
	size_t capacity;

	void free();
	void copyFrom(const MyStack<T>& other);
	void moveFrom(MyStack<T>&& other);
	void resize(size_t newCapacity);
public:
	MyStack();
	MyStack(const MyStack<T>& other);
	MyStack(MyStack<T>&& other);
	MyStack<T>& operator=(const MyStack<T>& other);
	MyStack<T>& operator=(MyStack<T>&& other);
	~MyStack();

	void push(const T& elem);
	void push(T&& elem);
	void pop();
	const T& top() const;
	bool empty() const;
	size_t size() const;
};

template<typename T>
inline void MyStack<T>::free()
{
	delete[] data;
}

template<typename T>
inline void MyStack<T>::copyFrom(const MyStack<T>& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new T[capacity];
	for (size_t i = 0; i < size; i++)
		data[i] = other.data[i];
}

template<typename T>
inline void MyStack<T>::moveFrom(MyStack<T>&& other)
{
	size = other.size;
	capacity = other.capacity;
	data = other.data;
	other.data = nullptr;
}

template<typename T>
inline void MyStack<T>::resize(size_t newCapacity)
{
	T* temp = new T[newCapacity];
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = data[i];
	}
	capacity = newCapacity;
	delete[] data;
	data = temp;
	temp = nullptr;
}

template<typename T>
inline MyStack<T>::MyStack()
{
	size = 0;
	capacity = INITIAL_CAPACITY;
	data = new T[capacity];
}

template<typename T>
inline MyStack<T>::MyStack(const MyStack<T>& other)
{
	copyFrom(other);
}

template<typename T>
inline MyStack<T>::MyStack(MyStack<T>&& other)
{
	moveFrom(std::move(other));
}

template<typename T>
inline MyStack<T>& MyStack<T>::operator=(const MyStack<T>& other)
{
	if (this != *other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
inline MyStack<T>& MyStack<T>::operator=(MyStack<T>&& other)
{
	if (this != *other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<typename T>
inline MyStack<T>::~MyStack()
{
	free();
}

template<typename T>
inline void MyStack<T>::push(const T& elem)
{
	if (size == capacity)
		resize(capacity * 2);

	data[size++] = elem;
}

template<typename T>
inline void MyStack<T>::push(T&& elem)
{
	if (size == capacity)
		resize(capacity * 2);

	data[size++] = std::move(elem);
}

template<typename T>
inline void MyStack<T>::pop()
{
	if(empty())
	{
		throw "Stack is empty.";
	}

	size--;
}

template<typename T>
inline const T& MyStack<T>::top() const
{
	if (empty())
	{
		throw "Stack is empty.";
	}

	return data[size - 1];
}

template<typename T>
inline bool MyStack<T>::empty() const
{
	return size == 0;
}

template<typename T>
inline size_t MyStack<T>::size() const
{
	return size;
}
