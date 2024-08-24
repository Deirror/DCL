#pragma once
#include "str.h"
#include <dcl_defines.h>

DCL_BEGIN

class strview
{
public:
	strview(const char* begin, const char* end);

	strview(const char* str);
	strview(const str& str);

	size_t length() const;
	char operator[](size_t ind) const;

	strview substr(size_t from, size_t length) const;

	friend dcl::ostream& operator<<(dcl::ostream&, const strview& strView);

private:
	const char* m_Begin;
	const char* m_End;
};

DCL_END