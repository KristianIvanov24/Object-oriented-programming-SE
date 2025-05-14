#include <iostream>

constexpr int INITIAL_CAPACITY = 8;
template < typename T>
class MyVector
{
private:
	T* data;
	size_t size;
	size_t capacity;

	void free();
	void copyFrom(const MyVector<T>& other);
	void moveFrom(MyVector<T>&& other);
	void resize(size_t newCapacity);
public:
	MyVector();
	MyVector(size_t n);
	MyVector(size_t n, const T& elem);

	MyVector(const MyVector<T>& other);
	MyVector(MyVector<T>&& other);
	MyVector<T>& operator=(const MyVector<T>& other);
	MyVector<T>& operator=(MyVector<T>&& other);
	~MyVector();

	void push_back(const T& elem);
	void push_back(T&& elem);
	void pop_back();
	void insert(size_t idx, const T& elem);
	void insert(size_t idx, T&& elem);
	void erase(size_t idx);

	const T& operator[](size_t idx) const;
	T& operator[](size_t idx);
	void shrink_to_fit();
	void clear();
	const T& front() const;
	T& front();
	const T& back() const;
	T& back();
	bool empty() const;

	size_t size() const;
	size_t capacity() const;
};

template<typename T>
inline void MyVector<T>::free()
{
	delete[] data;
}

template<typename T>
inline void MyVector<T>::copyFrom(const MyVector& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new T[capacity];
	for (size_t i = 0; i < size; i++)
		data[i] = other.data[i];
}

template<typename T>
inline void MyVector<T>::moveFrom(MyVector&& other)
{
	size = other.size;
	capacity = other.capacity;
	data = other.data;
	other.data = nullptr;
}

template<typename T>
inline void MyVector<T>::resize(size_t newCapacity)
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
inline MyVector<T>::MyVector()
{
	size = 0;
	capacity = INITIAL_CAPACITY;
	data = new T[capacity];
}

template<typename T>
inline MyVector<T>::MyVector(size_t n)
{
	size = n;
	capacity = n;
	data = new T[capacity];
}

template<typename T>
inline MyVector<T>::MyVector(size_t n, const T& elem)
{
	size = n;
	capacity = n;
	data = new T[capacity];
	for (size_t i = 0; i < size; i++)
	{
		data[i] = elem;
	}
}

template<typename T>
inline MyVector<T>::MyVector(const MyVector<T>& other)
{
	copyFrom(other);
}

template<typename T>
inline MyVector<T>::MyVector(MyVector<T>&& other)
{
	moveFrom(std::move(other));
}

template<typename T>
inline MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other)
{
	if (this != *other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
inline MyVector<T>& MyVector<T>::operator=(MyVector<T>&& other)
{
	if (this != *other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<typename T>
inline MyVector<T>::~MyVector()
{
	free();
}

template<typename T>
inline void MyVector<T>::push_back(const T& elem)
{
	if (size == capacity)
		resize(capacity*2);

	data[size++] = elem;
}

template<typename T>
inline void MyVector<T>::push_back(T&& elem)
{
	if (size == capacity)
		resize(capacity*2);

	data[size++] = std::move(elem);
}

template<typename T>
inline void MyVector<T>::pop_back()
{
	size--;
}

template<typename T>
inline void MyVector<T>::insert(size_t idx, const T& elem)
{
	size++;
	for (size_t i = idx + 1; i <= size; i++)
		data[i] = data[i - 1];

	data[idx] = elem;
}

template<typename T>
inline void MyVector<T>::insert(size_t idx, T&& elem)
{
	size++;
	for (size_t i = idx + 1; i <= size; i++)
		data[i] = data[i - 1];

	data[idx] = std::move(elem);
}

template<typename T>
inline void MyVector<T>::erase(size_t idx)
{
	for (size_t i = idx; i <= size; i++)
		data[i] = data[i + 1];

	size--;
}

template<typename T>
inline const T& MyVector<T>::operator[](size_t idx) const
{
	return data[idx];
}

template<typename T>
inline T& MyVector<T>::operator[](size_t idx)
{
	return data[idx];
}

template<typename T>
inline void MyVector<T>::shrink_to_fit()
{
	capacity = size;
	resize(size);
}

template<typename T>
inline void MyVector<T>::clear()
{
	free();
	size = 0;
}

template<typename T>
inline const T& MyVector<T>::front() const
{
	return data[0];
}

template<typename T>
inline T& MyVector<T>::front()
{
	return data[0];
}

template<typename T>
inline const T& MyVector<T>::back() const
{
	return data[size - 1];
}

template<typename T>
inline T& MyVector<T>::back()
{
	return data[size - 1];
}

template<typename T>
inline bool MyVector<T>::empty() const
{
	return size == 0;
}

template<typename T>
inline size_t MyVector<T>::size() const
{
	return size;
}

template<typename T>
inline size_t MyVector<T>::capacity() const
{
	return capacity;
}
