#include "except.h"
//---------------------------------
#include <strfunc.h>

DCL_BEGIN

except::except() : m_Message("Exception") {}

except::except(const char* message)
{
	if (!message)
	{
		return;
	}

	str_copy(m_Message, message);
}

const char* except::what() const
{
	return m_Message;
}

nullptr_except::nullptr_except() : except("Nullptr") {}

nullptr_except::nullptr_except(const char* message) : except(message) {}

empty_except::empty_except() : except("Empty") {}

empty_except::empty_except(const char* message) : except("Empty") {}

invalid_args::invalid_args() : except("Invalid arguments") {}

invalid_args::invalid_args(const char* message) : except(message) {}

out_of_bound::out_of_bound() : except("Out of bound") {}

out_of_bound::out_of_bound(const char* message) : except(message) {}

file_error::file_error() : except("File error") {}

file_error::file_error(const char* message) : except(message) {}

not_found::not_found() : except("Not found") {}

not_found::not_found(const char* message) : except(message) {}

DCL_END