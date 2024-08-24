#pragma once
#include <move.hpp>
#include <except.h>
#include <dcl_defines.h>

DCL_BEGIN

template <typename T, const unsigned S>
class stack
{
public:

	void push(const T& obj);
	void push(T&& obj);

	const T& peek() const;
	void pop();

	bool isEmpty() const;

private:
	T arr[S];
	size_t size = 0;
};


template <typename T, const unsigned S>
void stack<T, S>::push(const T& obj)
{
	if (size >= S)
		return;
	arr[size++] = obj;
}

template <typename T, const unsigned S>
void stack<T, S>::push(T&& obj)
{
	if (size >= S)
		return;
	arr[size++] = dcl::move(obj);
}

template <typename T, const unsigned S>
const T& stack<T, S>::peek() const
{
	if (isEmpty())
		throw dcl::out_of_bound();

	return arr[size - 1];
}

template <typename T, const unsigned S>
void stack<T, S>::pop()
{
	if (isEmpty())
		throw dcl::out_of_bound();
	size--;
}

template <typename T, const unsigned S>
bool stack<T, S>::isEmpty() const
{
	return size == 0;
}

DCL_END