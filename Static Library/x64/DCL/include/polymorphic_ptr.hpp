#pragma once 
#include <move.hpp>
#include <except.h>
#include <dcl_defines.h>

DCL_BEGIN

template <class T>
class polymorphic_ptr 
{
public:
	polymorphic_ptr() = default;
	polymorphic_ptr(T* data);
	polymorphic_ptr(const polymorphic_ptr<T>& other);
	polymorphic_ptr(polymorphic_ptr<T>&& other) noexcept;

	polymorphic_ptr<T>& operator=(const polymorphic_ptr<T>& other);
	polymorphic_ptr<T>& operator=(polymorphic_ptr<T>&& other) noexcept;

	~polymorphic_ptr();

	T* operator->();
	const T* operator->() const;

	T& operator*();
	const T& operator*() const;

	operator bool() const;
	void reset(T* data);

	T* get();
	const T* get() const;

private:
	T* data = nullptr;

	void copyFrom(const polymorphic_ptr<T>& other);
	void moveFrom(polymorphic_ptr<T>&& other);
	void free();
};


template<class T>
void polymorphic_ptr<T>::copyFrom(const polymorphic_ptr<T>& other)
{
	data = other.data->clone();
}

template<class T>
void polymorphic_ptr<T>::moveFrom(polymorphic_ptr<T>&& other)
{
	data = other.data;
	other.data = nullptr;
}

template<class T>
void polymorphic_ptr<T>::free()
{
	delete data;
}

template<class T>
polymorphic_ptr<T>::polymorphic_ptr(T* data) : data(data)
{
}

template<class T>
inline polymorphic_ptr<T>::polymorphic_ptr(const polymorphic_ptr<T>& other)
{
	copyFrom(other);
}

template<class T>
polymorphic_ptr<T>::polymorphic_ptr(polymorphic_ptr<T>&& other) noexcept
{
	moveFrom(dcl::move(other));
}

template<class T>
polymorphic_ptr<T>& polymorphic_ptr<T>::operator=(const polymorphic_ptr<T>& other)
{
	if (this != &other) 
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<class T>
polymorphic_ptr<T>& polymorphic_ptr<T>::operator=(polymorphic_ptr<T>&& other) noexcept
{
	if (this != &other) 
	{
		free();
		moveFrom(dcl::move(other));
	}
	return *this;
}

template<class T>
polymorphic_ptr<T>::~polymorphic_ptr()
{
	free();
}

template<class T>
T* polymorphic_ptr<T>::operator->()
{
	return data;
}

template<class T>
const T* polymorphic_ptr<T>::operator->() const
{
	return data;
}

template<class T>
T& polymorphic_ptr<T>::operator*()
{
	if (data == nullptr) 
	{
		throw dcl::nullptr_except();
	}
	return *data;
}

template<class T>
const T& polymorphic_ptr<T>::operator*() const
{
	if (data == nullptr) 
	{
		throw dcl::nullptr_except();
	}
	return *data;
}

template<class T>
polymorphic_ptr<T>::operator bool() const
{
	return data != nullptr;
}

template<class T>
void polymorphic_ptr<T>::reset(T* data)
{
	if (this->data != data) 
	{
		free();
		this->data = data;
	}
}

template<class T>
T* polymorphic_ptr<T>::get()
{
	return data;
}

template<class T>
const T* polymorphic_ptr<T>::get() const
{
	return data;
}

DCL_END