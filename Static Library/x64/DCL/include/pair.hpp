#pragma once
#include <dcl_defines.h>

DCL_BEGIN

template <class T, class D>
class pair
{
public:
	pair() = default;
	pair(const T& lhs, const D& rhs);

	const T& getLhs() const;
	const D& getRhs() const;

	void setLhs(const T& lhs);
	void setRhs(const D& rhs);

private:
	T m_Lhs;
	D m_Rhs;
};

template<class T, class D>
inline pair<T, D>::pair<T, D>(const T& lhs, const D& rhs) : m_Lhs(lhs), m_Rhs(rhs) {}

template<class T, class D>
inline const T& pair<T, D>::getLhs() const
{
	return m_Lhs;
}

template<class T, class D>
inline const D& pair<T, D>::getRhs() const
{
	return m_Rhs;
}

template<class T, class D>
inline void pair<T, D>::setLhs(const T& lhs)
{
	m_Lhs = lhs;
}

template<class T, class D>
inline void pair<T, D>::setRhs(const D& rhs)
{
	m_Rhs = rhs;
}

DCL_END