#pragma once
#include <dcl_defines.h>

DCL_BEGIN
template<class T, class D>
inline void insert(T& coll, size_t coll_size, const D& elements, size_t elements_size = ONE, size_t from = NULL) 
{

	for (size_t iter = static_cast<size_t>(coll_size - ONE); iter >= from; iter--)
	{
		coll[iter + static_cast<size_t>(elements_size)] = coll[iter];
	}

	for (size_t iter = from; iter < from + elements_size; iter++) 
	{
		coll[iter] = elements[iter - from];
	}

}

template<class T>
inline void erase(T& coll, size_t coll_size, size_t erase_count, size_t from)
{
	for (size_t iter = from; iter < coll_size; iter++) 
	{
		coll[iter] = coll[iter + static_cast<size_t>(erase_count)];	
	}

}

template<class T, class D>
inline void set_defvals(T& coll, size_t coll_size, const D& def_val, size_t from = NULL)
{
	for (size_t iter = from; iter < coll_size; iter++) 
	{
		coll[iter] = def_val;
	}
}

template<class T>
inline void swap(T& lhs, T& rhs) {

	T buff = lhs;

	lhs = rhs;

	rhs = buff;

}

DCL_END