#pragma once
#include <dcl_defines.h>
#include <tydefuint_t.h>

DCL_BEGIN

class except
{
	static constexpr ushort MAX_MESSAGE_LEN = UCHAR_MAX + 1;

public:
	except();
	except(const char* message);

	const char* what() const;

protected:
	char m_Message[MAX_MESSAGE_LEN]{};
};

class nullptr_except : public except
{
public:
	nullptr_except();
	nullptr_except(const char* message);
};

class empty_except : public except
{
public:
	empty_except();
	empty_except(const char* message);
};

class invalid_args : public except
{
public:
	invalid_args();
	invalid_args(const char* message);
};

class out_of_bound : public except
{
public:
	out_of_bound();
	out_of_bound(const char* message);
};

class file_error : public except
{
public:
	file_error();
	file_error(const char* message);
};

class not_found : public except
{
public:
	not_found();
	not_found(const char* message);
};

DCL_END