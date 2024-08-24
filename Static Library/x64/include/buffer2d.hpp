#pragma once
#include "buffer.hpp"

DCL_BEGIN

template<class T, size_t width, size_t height>
class buffer2D
{
public:
	buffer2D() = default;
	buffer2D(const buffer<T, width>* data, size_t dataSize);

	buffer<T, width>& operator[](size_t index);
	const buffer<T, width>& operator[](size_t index) const;

	const buffer<T, width>* data() const;
protected:
	buffer<T, width> m_Matrix[height]{};
};

template<class T, size_t width, size_t height>
inline buffer2D<T, width, height>::buffer2D(const buffer<T, width>* data, size_t dataSize)
{
	if (!data)
	{
		throw dcl::nullptr_except();
	}

	if (dataSize > height)
	{
		throw dcl::out_of_bound();
	}

	for (size_t iter = NULL; iter < dataSize; iter++)
	{
		m_Matrix[iter] = data[iter];
	}
}

template<class T, size_t width, size_t height>
inline buffer<T, width>& buffer2D<T, width, height>::operator[](size_t index)
{
	return m_Matrix[index];
}

template<class T, size_t width, size_t height>
inline const buffer<T, width>& buffer2D<T, width, height>::operator[](size_t index) const
{
	return m_Matrix[index];
}

template<class T, size_t width, size_t height>
inline const buffer<T, width>* buffer2D<T, width, height>::data() const
{
	return m_Matrix;
}

DCL_END