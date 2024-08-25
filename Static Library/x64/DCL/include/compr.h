#pragma once
#include <dcl_defines.h>
#include <tydefuint_t.h>
#include "except.h"

DCL_BEGIN

class compr
{
public:
	compr() = default;
	compr(char number);

	bool is_greater() const;
	bool is_equal() const;
	bool is_less() const;

	void set_res(char number);
	char get_res() const;

private:
	char m_Result = NULL;

};

DCL_END