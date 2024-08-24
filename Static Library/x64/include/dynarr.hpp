#pragma once
#include <move.hpp>
#include <dcl_defines.h>
#include <capcal.h>
#include <except.h>

DCL_BEGIN

template<class A>
class dynarr
{
public:
	dynarr();
	dynarr(size_t capacity);
	dynarr(const dynarr& other);
	dynarr& operator=(const dynarr& other);
	~dynarr();

	dynarr(dynarr&& other) noexcept;
	dynarr& operator=(dynarr&& other) noexcept;

	void pushBack(const A& newElem);
	void pushBack(A&& newElem);

	void popBack();

	void setAtIndex(const A& element, size_t index);
	void setAtIndex(A&& element, size_t index);

	size_t getSize() const;
	bool isEmpty() const;

	const A& operator[](size_t index) const;
	A& operator[](size_t index);

private:
	void copyFrom(const dynarr& other);
	void free();
	void moveFrom(dynarr&& other);
	void resize(size_t newCap);

	A* arr = nullptr;
	size_t size = 0;
	size_t capacity = 0;
};

template<class A>
dynarr<A>::dynarr() : dynarr(8) {}

template<class A>
dynarr<A>::dynarr(size_t capacity) : size(0)
{
	this->capacity = upper_power_of_two(capacity);
	arr = new A[this->capacity];
}

template<class A>
dynarr<A>::dynarr(const dynarr& other)
{
	copyFrom(other);
}

template<class A>
dynarr<A>& dynarr<A>::operator=(const dynarr& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<class A>
dynarr<A>::~dynarr()
{
	free();
}

template<class A>
dynarr<A>::dynarr(dynarr&& other) noexcept
{
	moveFrom(dcl::move(other));
}

template<class A>
dynarr<A>& dynarr<A>::operator=(dynarr&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(dcl::move(other));
	}
	return *this;
}

template<class A>
void dynarr<A>::copyFrom(const dynarr& other)
{

	arr = new A[other.capacity];

	for (size_t i = 0; i < other.size; i++)
		arr[i] = other.arr[i];

	size = other.size;
	capacity = other.capacity;
}

template<class A>
void dynarr<A>::moveFrom(dynarr&& other)
{
	arr = other.arr;
	other.arr = nullptr;
	size = other.size;
	capacity = other.capacity;
}

template<class A>
void dynarr<A>::free()
{
	delete[] arr;
}

template<class A>
void dynarr<A>::resize(size_t newCap)
{

	A* temp = arr;
	arr = new A[newCap];

	for (size_t i = 0; i < size; i++)
		arr[i] = temp[i];

	capacity = newCap;
	delete[] temp;
}

template<class A>
void dynarr<A>::pushBack(const A& newElem)
{
	if (size >= capacity)
		resize(capacity * 2);

	arr[size++] = newElem;
}

template<class A>
void dynarr<A>::pushBack(A&& newElem)
{
	if (size >= capacity)
		resize(capacity * 2);

	arr[size++] = dcl::move(newElem);
}

template<class A>
void dynarr<A>::popBack()
{
	if (size)
		size--;
	else
		throw dcl::out_of_bound();

	if (size * 4 <= capacity && capacity > 1)
		resize(capacity / 2);
}

template<class A>
void dynarr<A>::setAtIndex(const A& element, size_t index)
{
	if (index >= size)
		throw dcl::out_of_bound();

	arr[index] = element;
}

template<class A>
void dynarr<A>::setAtIndex(A&& element, size_t index)
{
	if (index >= size)
		throw dcl::out_of_bound();

	arr[index] = std::move(element);
}

template<class A>
size_t dynarr<A>::getSize() const
{
	return size;
}

template<class A>
bool dynarr<A>::isEmpty() const
{
	return size == 0;
}

template<class A>
const A& dynarr<A>::operator[](size_t index) const
{
	if (index > size)
		throw dcl::out_of_bound();
	return arr[index];
}

template<class A>
A& dynarr<A>::operator[](size_t index)
{
	if (index > size)
		throw dcl::out_of_bound();
	return arr[index];
}


DCL_END