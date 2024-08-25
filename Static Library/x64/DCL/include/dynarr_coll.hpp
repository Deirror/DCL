#pragma once
#include <move.hpp>
#include <dcl_defines.h>
#include <except.h>

DCL_BEGIN

template <class A>
class dynarr_coll
{
public:
	dynarr_coll();
	dynarr_coll(const dynarr_coll& other);
	dynarr_coll& operator=(const dynarr_coll& other);
	~dynarr_coll();

	dynarr_coll(dynarr_coll&& other) noexcept;
	dynarr_coll& operator=(dynarr_coll&& other) noexcept;

	void addAtFirstFreeIndex(const A& current);
	void addAtFirstFreeIndex(A&& obj);

	bool containsAt(unsigned ind) const;
	void popBack();
	void removeAt(size_t index);

	void setAtIndex(const A& obj, size_t index);
	void setAtIndex(A&& obj, size_t index);


	size_t size() const;
	const A& operator[](size_t index) const;
	A& operator[](size_t index);

private:
	A** _data = nullptr;
	size_t _capacity = 0;
	size_t _count = 0;

	void free();
	void copyFrom(const dynarr_coll& other);
	void resize(size_t newCap);

	void moveFrom(dynarr_coll&& other);

	int getFirstFreeIndex() const;
};

template <class A>
inline void dynarr_coll<A>::free()
{
	for (int i = 0; i < _capacity; i++)
		delete _data[i];
	delete[] _data;
}
template <class A>
inline void dynarr_coll<A>::copyFrom(const dynarr_coll& other)
{
	_count = other._count;
	_capacity = other._capacity;

	_data = new A * [_capacity];
	for (int i = 0; i < _capacity; i++)
	{
		if (other._data[i] == nullptr)
			_data[i] = nullptr;
		else
			_data[i] = new A(*other._data[i]);
	}
}
template <class A>
inline void dynarr_coll<A>::resize(size_t newCap)
{
	A** newDataPtr = new A * [newCap] {nullptr};

	for (int i = 0; i < _capacity; i++)
		newDataPtr[i] = _data[i];

	delete[] _data;
	_data = newDataPtr;

	_capacity = newCap;
}

template <class A>
inline dynarr_coll<A>::dynarr_coll()
{
	_capacity = 8;
	_data = new A * [_capacity] {nullptr};
}
template <class A>
inline dynarr_coll<A>::dynarr_coll(const dynarr_coll& other)
{
	copyFrom(other);
}

template <class A>
inline dynarr_coll<A>& dynarr_coll<A>::operator=(const dynarr_coll& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
template <class A>
inline dynarr_coll<A>::~dynarr_coll()
{
	free();
}
template <class A>
inline void dynarr_coll<A>::moveFrom(dynarr_coll&& other)
{
	_data = other._data;
	other._data = nullptr;

	_capacity = other._capacity;
	_count = other._count;

	other._count = 0;
}
template <class A>
inline dynarr_coll<A>::dynarr_coll(dynarr_coll&& other) noexcept
{
	moveFrom(dcl::move(other));
}
template <class A>
inline dynarr_coll<A>& dynarr_coll<A>::operator=(dynarr_coll&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(dcl::move(other));
	}
	return *this;
}
template <class A>
inline void dynarr_coll<A>::addAtFirstFreeIndex(const A& current)
{
	if (_count >= _capacity)
		resize(_capacity * 2);

	int ind = getFirstFreeIndex();
	if (ind == -1)
		return;

	_data[ind] = new A(current);
	_count++;
}
template <class A>
inline int dynarr_coll<A>::getFirstFreeIndex() const
{
	for (int i = 0; i < _capacity; i++)
		if (_data[i] == nullptr)
			return i;
	return -1;
}

template <class A>
inline void dynarr_coll<A>::addAtFirstFreeIndex(A&& obj)
{
	if (_count >= _capacity)
		resize(_capacity * 2);

	int ind = getFirstFreeIndex();
	if (ind == -1)
		return;

	_data[ind] = new A(dcl::move(obj));
	_count++;
}
template <class A>
inline bool dynarr_coll<A>::containsAt(unsigned ind) const
{
	return ind < _capacity && _data[ind] != nullptr;
}
template <class A>
inline void dynarr_coll<A>::removeAt(size_t index)
{
	if (index >= _capacity)
		return;

	delete _data[index];
	_data[index] = nullptr;
	_count--;
}
template <class A>
inline const A& dynarr_coll<A>::operator[](size_t index) const
{
	return *_data[index];
}
template <class A>
inline A& dynarr_coll<A>::operator[](size_t index)
{
	return *_data[index];
}
template <class A>
inline void dynarr_coll<A>::popBack()
{
	if (size() == 0)
		return;

	delete _data[_count - 1];
	_count--;

}
template <class A>
inline void dynarr_coll<A>::setAtIndex(const A& obj, size_t index)
{
	if (index >= _capacity)
		resize(_capacity * 2);

	if (_data[index] != nullptr)
		_data[index]->operator=(obj);
	else
	{
		_data[index] = new A(obj);
		_count++;
	}
}

template <class A>
inline void dynarr_coll<A>::setAtIndex(A&& obj, size_t index)
{

	if (_data[index] != nullptr)
		*_data[index] = obj;
	else
	{
		_data[index] = new A(dcl::move(obj));
		_count++;
	}
}

template <class A>
inline size_t dynarr_coll<A>::size() const
{
	return _count;
}

DCL_END