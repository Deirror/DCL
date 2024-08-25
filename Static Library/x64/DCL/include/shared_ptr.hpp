#pragma once
#include <except.h>
#include <dcl_defines.h>

DCL_BEGIN

struct Counter
{
	unsigned useCount = 0;
	unsigned weakCount = 0;

	inline void removeSharedPtr()
	{
		useCount--;
		if (useCount == 0)
			weakCount--;
	}

	inline void removeWeakPtr()
	{
		weakCount--;
	}

	inline void addSharedPtr()
	{
		useCount++;
		if (useCount == 1)
			weakCount++;
	}

	inline void addWeakPtr()
	{
		weakCount++;
	}
};

template <class V>
class weak_ptr;

template <typename T>
class shared_ptr
{
public:
	shared_ptr();
	shared_ptr(T* data);

	shared_ptr(const shared_ptr<T>& other);
	shared_ptr& operator=(const shared_ptr<T>& other);

	shared_ptr(shared_ptr<T>&& other);
	shared_ptr& operator=(shared_ptr<T>&& other);

	const T& operator*() const;
	T& operator*();
	const T* operator->() const;
	T* operator->();

	bool isInitlized() const;

	~shared_ptr();
private:
	template <typename V> friend class weak_ptr;

	T* data;
	Counter* counter;

	void free();
	void copyFrom(const shared_ptr<T>& other);
	void moveFrom(shared_ptr<T>&& other);

	shared_ptr(weak_ptr<T>& ptr);
};

template<class T>
inline shared_ptr<T>::shared_ptr(weak_ptr<T>& ptr)
{
	data = ptr.data;
	counter = ptr.counter;
	if (counter)
	{
		counter->addSharedPtr();
	}
}

template <typename T>
inline void shared_ptr<T>::free()
{
	if (data == nullptr && counter == nullptr)
		return;

	counter->removeSharedPtr();

	if (counter->useCount == 0)
		delete data;

	if (counter->weakCount == 0)
		delete counter;
}

template <typename T>
inline void shared_ptr<T>::copyFrom(const shared_ptr<T>& other)
{
	data = other.data;
	counter = other.counter;
	if (counter)
		counter->addSharedPtr();
}

template <typename T>
inline shared_ptr<T>::shared_ptr()
{
	data = nullptr;
	counter = nullptr;
}

template <typename T>
inline shared_ptr<T>::shared_ptr(T* data)
{
	this->data = data;
	if (this->data)
	{
		counter = new Counter();
		counter->addSharedPtr();
	}
}

template <typename T>
inline shared_ptr<T>::shared_ptr(const shared_ptr<T>& other)
{
	copyFrom(other);
}

template <typename T>
inline void shared_ptr<T>::moveFrom(shared_ptr<T>&& other)
{
	data = other.data;
	other.data = nullptr;

	counter = other.counter;
	other.counter = nullptr;
}

template <typename T>
inline shared_ptr<T>::shared_ptr(shared_ptr<T>&& other)
{
	moveFrom(std::move(other));
}

template <typename T>
inline shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
inline shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
inline const T& shared_ptr<T>::operator*() const
{
	if (data == nullptr)
	{
		throw dcl::nullptr_except();
	}
	return *data;
}

template <typename T>
inline T& shared_ptr<T>::operator*()
{
	if (data == nullptr)
	{
		throw dcl::nullptr_except();
	}
	return *data;
}

template <typename T>
inline shared_ptr<T>::~shared_ptr()
{
	free();
}

template<typename T>
inline T* shared_ptr<T>::operator->() {
	return data;
}

template<typename T>
inline const T* shared_ptr<T>::operator->() const {
	return data;
}

template<typename T>
inline bool shared_ptr<T>::isInitlized() const
{
	return data != nullptr;
}

DCL_END