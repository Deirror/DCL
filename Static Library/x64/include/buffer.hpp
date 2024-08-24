#pragma once
#include <except.h>
#include <dcl_defines.h>

DCL_BEGIN

template <class T, size_t size>
class buffer
{
public:
	buffer() = default;
	buffer(const T* data, size_t dataSize);

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	const T* data() const;

private:
	T m_Data[size]{};
};

template<class T, size_t size>
inline buffer<T, size>::buffer(const T* data, size_t dataSize)
{
	if (!data)
	{
		throw dcl::nullptr_except();
	}

	if (dataSize > size)
	{
		throw dcl::out_of_bound();
	}

	for (size_t iter = 0; iter < dataSize; iter++)
	{
		m_Data[iter] = data[iter];
	}
}

template<class T, size_t size>
inline T& buffer<T, size>::operator[](size_t index)
{
	return m_Data[index];
}

template<class T, size_t size>
inline const T& buffer<T, size>::operator[](size_t index) const
{
	return m_Data[index];
}

template<class T, size_t size>
inline const T* buffer<T, size>::data() const
{
	return m_Data;
}

DCL_END