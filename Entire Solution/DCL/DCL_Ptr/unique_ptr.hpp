#pragma once
#include <dcl_defines.h>

DCL_BEGIN

template <class T>
class unique_ptr
{
public:
	unique_ptr(T* ptr);

	unique_ptr(const unique_ptr&) = delete;
	unique_ptr& operator=(const unique_ptr&) = delete;

	unique_ptr(unique_ptr&&) noexcept;
	unique_ptr& operator=(unique_ptr&&) noexcept;

	T& operator*();
	const T& operator*() const;

	T* operator->();
	const T* operator->() const;

	~unique_ptr();

private:
	T* ptr;
};

template <class T>
inline unique_ptr<T>::unique_ptr(T* ptr) : ptr(ptr) {}

template <class T>
inline unique_ptr<T>::unique_ptr(unique_ptr<T>&& other) noexcept
{
	ptr = other.ptr;
	other.ptr = nullptr;
}
template <class T>
inline unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<T>&& other) noexcept
{
	if (this != &other)
	{
		delete ptr;
		ptr = other.ptr;
		other.ptr = nullptr;
	}
	return *this;
}

template <class T>
inline T& unique_ptr<T>::operator*()
{
	return *ptr;
}

template <class T>
inline const T& unique_ptr<T>::operator*() const
{
	return *ptr;
}

template <class T>
inline T* unique_ptr<T>::operator->()
{
	return *ptr;
}

template <class T>
inline const T* unique_ptr<T>::operator->() const
{
	return *ptr;
}

template <class T>
inline unique_ptr<T>::~unique_ptr()
{
	delete ptr;
}

DCL_END