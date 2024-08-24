#include "compr.h"

DCL_BEGIN

compr::compr(char number)
{
	set_res(number);
}

bool compr::is_greater() const
{
	return m_Result == ONE;
}

bool compr::is_equal() const
{
	return m_Result == NULL;
}

bool compr::is_less() const
{
	return m_Result == M_ONE;
}

void compr::set_res(char number)
{
	if (number >= M_ONE && number <= ONE)
	{
		m_Result = number;
	}
	else
	{
		throw dcl::invalid_args();
	}
}

char compr::get_res() const
{
	return m_Result;
}

DCL_END