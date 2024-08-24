#include "strfunc.h"

void str_copy(char* dest, const char* src)
{
	size_t idx = NULL;

	while (src[idx])
	{
		dest[idx] = src[idx];
		idx += ONE;
	}

	dest[idx] = TERM_NULL;
}

void str_copy(char* dest, const char* src, size_t count, size_t idx)
{
	for (size_t iter = NULL; iter < count; iter++)
	{
		dest[iter] = src[idx + iter];
	}

	dest[count] = TERM_NULL;
}

size_t str_len(const char* str)
{
	size_t len = NULL;

	while (str[len++]);

	return --len;
}

void str_concat(char* dest, const char* src)
{
	size_t dest_idx = static_cast<size_t>(str_len(dest));
	size_t src_idx = NULL;

	while (src[src_idx])
	{
		dest[dest_idx] = src[src_idx];

		dest_idx += ONE;
		src_idx += ONE;
	}

	dest[dest_idx] = TERM_NULL;
}

const char* str_str(const char* str, const char* substr)
{
	while (*str)
	{
		const char* copy_str = str;
		const char* copy_substr = substr;

		while (*copy_str == *copy_substr && (*copy_str != TERM_NULL && *copy_substr != TERM_NULL))
		{
			copy_str++;
			copy_substr++;
		}

		if (*(copy_substr) == TERM_NULL)
		{
			break;
		}

		str++;
	}

	if (*str != TERM_NULL)
	{
		return str;
	}

	return nullptr;
}

const char* str_ch(const char* str, char ch)
{
	while (*str != ch && *str != TERM_NULL)
	{
		str++;
	}

	if (*str != TERM_NULL)
	{
		return str;
	}

	return nullptr;
}

size_t str_cmpr(const char* lhs, const char* rhs)
{
	size_t lhs_length = str_len(lhs);
	size_t rhs_length = str_len(rhs);

	size_t shorter_length = (lhs_length < rhs_length) ? lhs_length : rhs_length;

	for (size_t idx = NULL; idx < shorter_length; idx++)
	{
		if (lhs[idx] > rhs[idx])
		{
			return ONE;
		}
		else if (lhs[idx] < rhs[idx])
		{
			return M_ONE;
		}
	}

	if (lhs_length == rhs_length)
	{
		return NULL;
	}

	return (shorter_length == lhs_length) ? M_ONE : ONE;
}
