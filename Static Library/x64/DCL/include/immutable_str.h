#pragma once
#include "strpool.h"
#include <tydefios.h>

DCL_BEGIN

class immutable_str
{
public:
	immutable_str();
	immutable_str(const char* text);
	immutable_str(const immutable_str& other);

	char operator[](size_t index) const;

	immutable_str& operator=(const immutable_str& other);

	const char* c_str() const;

	size_t length() const;
	bool empty() const;

	static void debug();

	~immutable_str();

private:
	const char* data = nullptr;
	unsigned size = 0;

	static strpool pool;
};

bool operator==(const immutable_str& lhs, const immutable_str& rhs);
bool operator!=(const immutable_str& lhs, const immutable_str& rhs);
dcl::ostream& operator<<(dcl::ostream& os, const immutable_str& str);

DCL_END