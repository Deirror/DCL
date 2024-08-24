#include "immutable_str.h"
#include <strfunc.h>
#include <except.h>

DCL_BEGIN
strpool immutable_str::pool;

immutable_str::immutable_str() : immutable_str("") {}

immutable_str::immutable_str(const char* text)
{
	data = pool.getString(text);
	size = str_len(data);
}

immutable_str::immutable_str(const immutable_str& other)
{
	data = pool.getString(other.c_str());
	size = other.size;
}

void immutable_str::debug()
{
	immutable_str::pool.debug();
}


char immutable_str::operator[](size_t index) const
{
	if (index >= size)
		throw dcl::out_of_bound();

	return data[index];
}

immutable_str& immutable_str::operator=(const immutable_str& other)
{
	if (this != &other)
	{
		pool.removeString(data);
		data = pool.getString(other.c_str());
		size = other.size;
	}

	return *this;
}

const char* immutable_str::c_str() const
{
	return data;
}

size_t immutable_str::length() const
{
	return size;
}

bool immutable_str::empty() const
{
	return (size == 0);
}

immutable_str::~immutable_str()
{
	pool.removeString(c_str());
}

bool operator==(const immutable_str& lhs, const immutable_str& rhs)
{
	return str_cmpr(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const immutable_str& lhs, const immutable_str& rhs)
{
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const immutable_str& str)
{
	return os << str.c_str();
}

DCL_END
