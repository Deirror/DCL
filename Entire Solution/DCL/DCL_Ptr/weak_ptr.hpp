#pragma once
#include "shared_ptr.hpp"
#include <except.h>
#include <move.hpp>

DCL_BEGIN

template <typename T>
class weak_ptr
{
public:
	weak_ptr();

	weak_ptr(shared_ptr<T>& ptr);
	weak_ptr(const weak_ptr<T>& other);
	weak_ptr& operator=(const weak_ptr<T>& other);

	weak_ptr(weak_ptr<T>&& other);
	weak_ptr& operator=(weak_ptr<T>&& other);
	~weak_ptr();

	shared_ptr<T> lock() const;

	bool expired() const;
private:	
	template<class V> friend class shared_ptr;

	T* data;
	Counter* counter;

	void copyFrom(const weak_ptr<T>& other);
	void free();
	void moveFrom(weak_ptr<T>&& other);
};

template <typename T>
weak_ptr<T>::weak_ptr()
{
	data = nullptr;
	counter = nullptr;
}

template <typename T>
void weak_ptr<T>::moveFrom(weak_ptr<T>&& other)
{
	data = other.data;
	other.data = nullptr;

	counter = other.counter;
	other.counter = nullptr;
}


template <typename T>
weak_ptr<T>::weak_ptr(weak_ptr<T>&& other)
{
	moveFrom(dcl::move(other));
}

template <typename T>
weak_ptr<T>& weak_ptr<T>::operator=(weak_ptr<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(dcl::move(other));
	}
	return *this;
}

template <typename T>
weak_ptr<T>::weak_ptr(shared_ptr<T>& ptr)
{
	data = ptr.data;
	counter = ptr.counter;

	if (counter)
		counter->addWeakPtr();
}

template <typename T>
void weak_ptr<T>::copyFrom(const weak_ptr<T>& other)
{
	data = other.data;
	counter = other.counter;
	if (counter)
		counter->addWeakPtr();
}

template <typename T>
void weak_ptr<T>::free()
{
	if (data == nullptr && counter == nullptr)
		return;

	counter->removeWeakPtr();
	if (counter->weakCount == 0)
		delete counter;

}

template <typename T>
weak_ptr<T>::weak_ptr(const weak_ptr<T>& other)
{
	copyFrom(other);
}

template <typename T>
weak_ptr<T>& weak_ptr<T>::operator=(const weak_ptr<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
weak_ptr<T>::~weak_ptr()
{
	free();
}

template <typename T>
bool weak_ptr<T>::expired() const
{
	return counter && counter->useCount == 0;
}

template <typename T>
shared_ptr<T> weak_ptr<T>::lock() const
{
	if (expired())
		return shared_ptr<T>();
	else
		return shared_ptr<T>(*this);
}

DCL_END