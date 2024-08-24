#include "strview.h"

DCL_BEGIN

strview::strview(const char* begin, const char* end) : m_Begin(begin), m_End(end){}

strview::strview(const char* str) : strview(str, str + strlen(str)) {}

strview::strview(const str& str) : strview(str.c_str()) {}

size_t strview::length() const
{
	return m_End - m_Begin;
}
char strview::operator[](size_t index) const
{
	return m_Begin[index];
}

strview strview::substr(size_t from, size_t length) const
{
	if (m_Begin + from + length > m_End)
		throw dcl::out_of_bound();

	return strview(m_Begin + from, m_Begin + from + length);
}

dcl::ostream& operator<<(dcl::ostream& os, const strview& strView)
{
	const char* iter = strView.m_Begin;

	while (iter != strView.m_End)
	{
		os << *iter;
		iter++;
	}
	return os;
}

DCL_END