#pragma once
#include <move.hpp>
#include <except.h>
#include <dcl_defines.h>

DCL_BEGIN

template <typename T>
class queue
{
public:
	queue();

	queue(const queue<T>& other);
	queue<T>& operator=(const queue<T>& other);

	queue(queue<T>&& other);
	queue<T>& operator=(queue<T>&& other);

	void push(const T& obj);
	void push(T&& obj);
	void pop();

	const T& peek() const;
	bool isEmpty() const;

	~queue();

private:
	T* data;
	size_t capacity;
	size_t size;

	size_t get;
	size_t put;

	void resize();

	void moveFrom(queue<T>&& other);
	void copyFrom(const queue<T>& other);
	void free();
};

template <typename T>
queue<T>::queue()
{
	capacity = 4;
	data = new T[capacity];
	size = 0;
	get = put = 0;
}

template <typename T>
void queue<T>::push(const T& obj)
{
	if (size == capacity)
		resize();

	data[put] = obj;
	(++put) %= capacity;
	size++;
}

template <typename T>
void queue<T>::push(T&& obj)
{
	if (size == capacity)
		resize();

	data[put] = dcl::move(obj);
	(++put) %= capacity;
	size++;
}

template <typename T>
bool queue<T>::isEmpty() const
{
	return size == 0;
}


template <typename T>
const T& queue<T>::peek() const
{
	if (isEmpty())
		throw dcl::empty_except();

	return data[get];
}

template <typename T>
void queue<T>::pop()
{
	if (isEmpty())
		throw dcl::empty_except();

	(++get) %= capacity;
	size--;
}

template <typename T>
void queue<T>::resize()
{
	T* resizedData = new T[capacity * 2];
	for (size_t i = 0; i < size; i++)
	{
		resizedData[i] = data[get];
		(++get) %= capacity;
	}
	capacity *= 2;
	delete[] data;
	data = resizedData;
	get = 0;
	put = size;
}


template <typename T>
void queue<T>::copyFrom(const queue<T>& other)
{
	data = new T[other.capacity];
	for (int i = 0; i < other.capacity; i++)
		data[i] = other.data[i];

	get = other.get;
	put = other.put;

	size = other.size;
	capacity = other.capacity;

}

template <typename T>
void queue<T>::moveFrom(queue<T>&& other)
{
	get = other.get;
	put = other.put;

	size = other.size;
	capacity = other.capacity;

	data = other.data;
	other.data = nullptr;

	other.size = other.capacity = 0;
}

template <typename T>
void queue<T>::free()
{
	delete[] data;
}

template <typename T>
queue<T>::queue(const queue<T>& other)
{
	copyFrom(other);

}

template <typename T>
queue<T>& queue<T>::operator=(const queue<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
queue<T>::queue(queue<T>&& other)
{
	moveFrom(dcl::move(other));
}

template <typename T>
queue<T>& queue<T>::operator=(queue<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
queue<T>::~queue()
{
	free();
}

DCL_END