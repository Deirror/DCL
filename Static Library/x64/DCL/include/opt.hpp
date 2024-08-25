#pragma once
#include <except.h>
#include <dcl_defines.h>
#include <move.hpp>

DCL_BEGIN

template <typename T>
class opt
{
public:
	opt();
	opt(const T& obj);

	opt(const opt<T>& other);
	opt<T>& operator=(const opt<T>& other);

	opt(opt<T>&& other) noexcept;
	opt<T>& operator=(opt<T>&& other) noexcept;

	bool containsData() const;
	const T& getData() const;
	void setData(const T& el);
	void clear();

	~opt();
private:
	T* data;

	void moveFrom(opt<T>&& other);
	void copyFrom(const opt<T>& other);
	void free();
};

template <typename T>
opt<T>::opt() : data(nullptr)
{}

template <typename T>
opt<T>::opt(const T& obj) : data(nullptr)
{
	setData(obj);
}

template <typename T>
bool opt<T>::containsData() const
{
	return data != nullptr;
}

template <typename T>
const T& opt<T>::getData() const
{
	if (!containsData())
		throw dcl::empty_except();
	return *data;
}

template <typename T>
void opt<T>::setData(const T& el)
{
	delete data;
	data = new T(el);
}

template<typename T>
void opt<T>::moveFrom(opt<T>&& other)
{
	data = other.data;
	other.data = nullptr;
}

template <typename T>
void opt<T>::copyFrom(const opt<T>& other)
{
	if (other.containsData())
		data = new T(*other.data);
	else
		data = nullptr;
}

template <typename T>
void opt<T>::free()
{
	delete data;
}

template <typename T>
void opt<T>::clear()
{
	free();
	data = nullptr;
}

template<typename T>
opt<T>::~opt()
{
	free();
}

template <typename T>
opt<T>::opt(const opt<T>& other)
{
	copyFrom(other);
}

template <typename T>
opt<T>& opt<T>::operator=(const opt<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
opt<T>::opt(opt<T>&& other) noexcept
{
	moveFrom(dcl::move(other));
}

template<typename T>
inline opt<T>& opt<T>::operator=(opt<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(dcl::move(other));
	}
	return *this;
}

DCL_END