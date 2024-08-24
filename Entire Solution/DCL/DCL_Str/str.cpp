#include "str.h"
#include <strfunc.h>
#include <capcal.h>
#include <colloper.hpp>
#include <move.hpp>

DCL_BEGIN

str::str() : m_Capacity(DEFAULT_CAPACITY)
{
	ALLOCATE_NEW_ARRAY(m_Data, char, m_Capacity + ONE);

	*(m_Data) = TERM_NULL;
}

str::str(const char* data)
{
	m_Length = str_len(data);
	m_Capacity = upper_power_of_two(m_Length);

	ALLOCATE_NEW_ARRAY(m_Data, char, m_Capacity + ONE);

	str_copy(m_Data, data);
}

str::str(const str& other)
{
	copy_from(other);
}

str& str::operator=(const str& other)
{

	if (this != &other)
	{
		free();
		copy_from(other);
	}
	return *this;
}

str::str(str&& other) noexcept
{
	move_from(dcl::move(other));
}

str& str::operator=(str&& other) noexcept
{
	if (this != &other)
	{
		free();
		move_from(dcl::move(other));
	}
	return *this;
}

str::~str() noexcept
{
	free();
}


size_t str::length() const
{
	return m_Length;
}

size_t str::capacity() const
{
	return m_Capacity;
}

const char* str::data() const
{
	return m_Data;
}

const char* str::c_str() const
{
	return m_Data;
}

size_t str::max_size() const
{
	return SIZE_MAX / sizeof(char);
}


void str::push_back(const char ch)
{
	if (m_Length == m_Capacity)
	{
		resize(m_Capacity * FACTOR);
	}
	m_Data[m_Length++] = ch;
}

void str::pop_back()
{
	if (m_Length * DOWN_FACTOR == m_Capacity)
	{
		resize(m_Capacity / FACTOR);
	}
	m_Data[--m_Length] = TERM_NULL;
}

char& str::back()
{
	return m_Data[m_Length - ONE];
}

const char& str::back() const
{
	return m_Data[m_Length - ONE];
}


str& str::operator+=(const str& other)
{
	size_t length = m_Length + other.m_Length;

	if (length > m_Capacity)
	{
		resize(upper_power_of_two(length));
	}

	str_concat(m_Data, other.m_Data);
	m_Length = length;

	return *this;
}

str& str::operator+=(char ch)
{
	push_back(ch);
	return *this;
}

str operator+(const str& lhs, const str& rhs)
{
	str res(lhs.m_Length + rhs.m_Length);

	res += lhs;
	res += rhs;

	return res;
}

str& str::append(const str& other)
{
	return this->operator+=(other);
}


dcl::ostream& operator<<(dcl::ostream& os, const str& other)
{
	return os << other.m_Data;
}

dcl::istream& operator>>(dcl::istream& is, str& other)
{
	char buff[1024];

	dcl::cin >> buff;
	size_t m_Length = str_len(buff);

	if (m_Length > other.m_Capacity)
	{
		other.resize(upper_power_of_two(m_Length));
	}

	other.m_Length = m_Length;
	str_copy(other.m_Data, buff);

	return is;
}

bool operator==(const str& lhs, const str& rhs)
{
	return str_cmpr(lhs. c_str(), rhs. c_str()) == NULL;
}

bool operator!=(const str& lhs, const str& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const str& lhs, const str& rhs)
{
	return str_cmpr(lhs. c_str(), rhs. c_str()) < NULL;
}

bool operator<=(const str& lhs, const str& rhs)
{
	return str_cmpr(lhs. c_str(), rhs. c_str()) <= NULL;
}

bool operator>(const str& lhs, const str& rhs) {
	return str_cmpr(lhs. c_str(), rhs. c_str()) > NULL;
}

bool operator>=(const str& lhs, const str& rhs)
{
	return str_cmpr(lhs. c_str(), rhs. c_str()) >= NULL;
}


char& str::operator[](size_t idx)
{

	return m_Data[idx];

}

const char& str::operator[](size_t idx) const
{
	return m_Data[idx];
}

char& str::at(size_t idx)
{
	if (idx >= m_Length)
	{
		throw dcl::out_of_bound();
	}
	return m_Data[idx];
}

const char& str::at(size_t idx) const
{
	if (idx >= m_Length)
	{
		throw dcl::out_of_bound();
	}
	return m_Data[idx];
}

char& str::front()
{
	if (m_Length == NULL)
	{
		throw dcl::empty_except();
	}

	return m_Data[NULL];
}

const char& str::front() const
{
	if (m_Length == NULL)
	{
		throw dcl::empty_except();
	}

	return m_Data[NULL];
}


void str::assign(const str& other)
{
	assign(other.m_Data);
}

void str::assign(const char* ptr)
{
	if (!ptr)
	{
		throw dcl::nullptr_except();
	}

	size_t _ptr_length = str_len(ptr);

	m_Length = _ptr_length;
	m_Capacity = upper_power_of_two(m_Length);

	DELETE_ARRAY(m_Data);
	ALLOCATE_NEW_ARRAY(m_Data, char, m_Capacity + ONE);

	str_copy(m_Data, ptr);
}


compr str::compare(const str& other) const
{
	return str_cmpr(m_Data, other.m_Data);
}

void str::copy_to(char*& ptr, size_t start_idx, size_t count) const
{
	if (start_idx + count > m_Length)
	{
		throw dcl::out_of_bound();
	}

	DELETE_ARRAY(ptr);
	//Please delete the allocated memory!!!
	ALLOCATE_NEW_ARRAY(ptr, char, count + ONE);

	str_copy(ptr, m_Data, count, start_idx);
}

str& str::erase(size_t from)
{
	if (from >= m_Length)
	{
		throw dcl::out_of_bound();
	}

	size_t erase_count = (m_Length - from);

	set_defvals(*this, m_Length, TERM_NULL, static_cast<size_t>(m_Length - erase_count));
	down_size(erase_count);

	return *this;
}

str& str::erase(size_t from, size_t count)
{
	if (from + count > m_Length)
	{
		throw dcl::out_of_bound();
	}

	dcl::erase(*this, m_Length, count, from);
	set_defvals(*this, m_Length, TERM_NULL, static_cast<size_t>(m_Length - count));
	down_size(count);

	return *this;

}

str& str::trim(const str& exclude)
{
	return trim(exclude.m_Data);
}

str& str::trim(const char* exclude)
{
	if (!exclude)
	{
		throw dcl::nullptr_except();
	}

	size_t exclude_length = str_len(exclude);

	for (size_t iter = NULL; iter < exclude_length; iter++)
	{
		for (size_t idx = NULL; idx < m_Length; idx++)
		{
			if (exclude[iter] == m_Data[idx])
			{
				erase(idx, ONE);
			}
		}
	}

	return *this;
}

str& str::trim(char exclude)
{
	char _arr_exclude_ch[BIN]{};
	_arr_exclude_ch[NULL] = exclude;

	return trim(_arr_exclude_ch);
}

str str::to_upper() const
{
	str result = *this;

	for (size_t iter = NULL; iter < result.m_Length; iter++)
	{
		if (result.m_Data[iter] >= START_LOWER && result.m_Data[iter] <= END_LOWER)
		{
			result.m_Data[iter] -= LOW_UP_DIFF;
		}
	}

	return result;
}

str str::to_lower() const
{
	str result = *this;

	for (size_t iter = NULL; iter < result.m_Length; iter++)
	{
		if (result.m_Data[iter] >= START_UPPER && result.m_Data[iter] <= END_UPPER)
		{
			result.m_Data[iter] += LOW_UP_DIFF;
		}
	}

	return result;
}


size_t str::find(const str& searched, size_t from) const
{
	return find(searched.m_Data, from);
}

size_t str::find(const char* ptr, size_t from) const
{
	if (from >= m_Length)
	{
		return NOT_FOUND;
	}

	const char* result = str_str(m_Data + from, ptr);

	return result ? static_cast<size_t>(result - m_Data) : NOT_FOUND;

}

size_t str::find(char ch, size_t from) const
{
	if (from >= m_Length)
	{
		return NOT_FOUND;
	}

	const char* result = str_ch(m_Data + from, ch);

	return result ? static_cast<size_t>(result - m_Data) : NOT_FOUND;
}


size_t str::rfind(const str& searched, size_t from) const
{
	return rfind(searched.m_Data, from);
}

size_t str::rfind(const char* ptr, size_t from) const
{
	if (from >= m_Length)
	{
		return NOT_FOUND;
	}

	for (size_t iter = static_cast<size_t>(m_Length - ONE); iter >= from; iter--)
	{
		if (str_str(m_Data + iter, ptr))
		{
			return iter;
		}
	}

	return NOT_FOUND;
}

size_t str::rfind(char ch, size_t from) const
{
	if (from >= m_Length)
	{
		return NOT_FOUND;
	}

	char _arr_ch[BIN]{};
	_arr_ch[NULL] = ch;

	return rfind(_arr_ch, from);
}

size_t str::find_first_of(const str& searched, size_t from) const
{
	return find_first_of(searched.m_Data, from);
}

size_t str::find_first_of(const char* ptr, size_t from) const
{
	if (from >= m_Length)
	{
		return NOT_FOUND;
	}

	size_t _ptr_length = str_len(ptr);

	for (size_t iter = NULL; iter < _ptr_length; iter++)
	{
		const char* result = str_ch(m_Data + from, *(ptr + iter));

		if (result)
		{
			return static_cast<size_t>(result - m_Data);
		}
	}

	return NOT_FOUND;
}

size_t str::find_first_of(char ch, size_t from) const
{
	return find(ch, from);
}


size_t str::find_first_not_of(const str& searched, size_t from) const
{
	return find_first_not_of(searched.m_Data, from);
}

size_t str::find_first_not_of(const char* ptr, size_t from) const
{
	if (from >= m_Length)
	{
		return NOT_FOUND;
	}

	for (size_t iter = NULL; iter < m_Length; iter++)
	{
		if (!str_ch(ptr, m_Data[iter]))
		{
			return iter;
		}
	}

	return NOT_FOUND;
}

size_t str::find_first_not_of(char ch, size_t from) const
{
	if (from >= m_Length)
	{
		return NOT_FOUND;
	}

	char _arr_ch[BIN]{};
	_arr_ch[NULL] = ch;

	return find_first_not_of(_arr_ch, from);
}


size_t str::find_last_of(const str& searched, size_t from) const
{
	return find_last_of(searched.m_Data, from);
}

size_t str::find_last_of(const char* ptr, size_t from) const
{
	if (from >= m_Length)
	{
		return NOT_FOUND;
	}

	size_t _ptr_length = str_len(ptr);

	for (size_t iter = static_cast<size_t>(_ptr_length - ONE); iter >= from; iter--)
	{
		const char* result = str_ch(m_Data + from, *(ptr + iter));

		if (result)
		{
			return static_cast<size_t>(result - m_Data);
		}
	}

	return NOT_FOUND;
}

size_t str::find_last_of(char ch, size_t from) const
{
	if (from >= m_Length)
	{
		return NOT_FOUND;
	}

	char _arr_ch[BIN]{};
	_arr_ch[NULL] = ch;

	return find_last_of(_arr_ch, from);
}


size_t str::find_last_not_of(const str& searched, size_t from) const
{

	return find_last_not_of(searched.m_Data, from);

}

size_t str::find_last_not_of(const char* ptr, size_t from) const
{
	if (from >= m_Length)
	{
		return NOT_FOUND;
	}

	for (size_t iter = static_cast<size_t>(m_Length - ONE); iter >= from; iter--)
	{
		if (!str_ch(ptr, m_Data[iter]))
		{
			return iter;
		}
	}

	return NOT_FOUND;
}

size_t str::find_last_not_of(char ch, size_t from) const
{
	if (from >= m_Length)
	{
		return NOT_FOUND;
	}

	char _arr_ch[BIN]{};
	_arr_ch[NULL] = ch;

	return find_last_not_of(_arr_ch, from);
}

bool str::contains(const char* ptr) const
{
	return (find(ptr,0) != NOT_FOUND);
}

bool str::contains(char ch) const
{
	return (find(ch,0) != NOT_FOUND);
}

iter<char> str::begin() const
{
	return iter<char>(m_Data);
}

iter<char> str::end() const
{
	return iter<char>(m_Data + m_Length);
}

const_iter<char> str::cbegin() const
{
	return const_iter<char>(m_Data);
}

const_iter<char> str::cend() const
{
	return const_iter<char>(m_Data + m_Length);
}

rev_iter<char> str::rbegin() const
{
	return rev_iter<char>(m_Data + m_Length - ONE);
}

rev_iter<char> str::rend() const
{
	return rev_iter<char>(m_Data - ONE);
}

const_rev_iter<char> str::crbegin() const
{
	return const_rev_iter<char>(m_Data + m_Length - ONE);
}

const_rev_iter<char> str::crend() const
{
	return const_rev_iter<char>(m_Data - ONE);
}

void str::reserve(size_t length)
{
	if (upper_power_of_two(length) > m_Capacity)
	{
		resize(upper_power_of_two(length));
	}
}

void str::shrink_to_fit()
{
	if (upper_power_of_two(m_Length) < m_Capacity)
	{
		resize(upper_power_of_two(m_Length));
	}
}


str& str::insert(const str& other, size_t from)
{
	return insert(other.m_Data, from);;
}

str& str::insert(const char* ptr, size_t from)
{
	if (from > m_Length)
	{
		throw dcl::out_of_bound();
	}

	size_t _ptr_length = str_len(ptr);

	if (_ptr_length + m_Length > m_Capacity)
	{
		resize(upper_power_of_two(_ptr_length + m_Length));
	}

	dcl::insert(*this, m_Length, ptr, _ptr_length, from);
	m_Length += _ptr_length;

	return *this;
}

str& str::replace(const str& searched, const str& replace_with, size_t from)
{
	return replace(searched.m_Data, replace_with.m_Data, from);
}

str& str::replace(const char* searched, const char* replace_with, size_t from)
{
	if (from > m_Length)
	{
		throw dcl::out_of_bound();
	}

	size_t idx = from;
	size_t searched_length = str_len(searched);

	while (idx <= m_Length)
	{
		idx = find(searched, idx);

		if (idx == NOT_FOUND)
		{
			break;
		}

		erase(idx, searched_length);
		insert(replace_with, idx);
	}

	return *this;

}

str& str::replace(char searched, char replace_with, size_t from)
{
	char arr_searched_ch[BIN]{};
	arr_searched_ch[NULL] = searched;

	char arr_replace_with_ch[BIN]{};
	arr_replace_with_ch[NULL] = replace_with;

	return replace(arr_searched_ch, arr_replace_with_ch, from);
}


str str::subdstr(size_t from, size_t count) const
{
	if (from + count > m_Length)
	{
		throw dcl::out_of_bound();
	}

	str result;
	size_t m_Length = from + count;

	for (size_t iter = from; iter < m_Length; iter++)
	{
		result += m_Data[iter];
	}

	return result;
}

void str::swap(str& other)
{
	dcl::swap(*this, other);
}

bool str::empty() const
{
	return m_Length == NULL;
}

void str::clear()
{
	m_Length = NULL;
	m_Capacity = DEFAULT_CAPACITY;

	DELETE_ARRAY(m_Data);
	ALLOCATE_NEW_ARRAY(m_Data, char, m_Capacity + ONE);

	*(m_Data) = TERM_NULL;
}

str::str(size_t length)
{
	m_Capacity = upper_power_of_two(length);
	ALLOCATE_NEW_ARRAY(m_Data, char, m_Capacity + ONE);
}

void str::down_size(size_t count)
{
	for (size_t iter = NULL; iter <= count; iter++)
	{
		if (m_Length * DOWN_FACTOR == m_Capacity)
		{
			resize(upper_power_of_two(m_Capacity / FACTOR));
		}
		m_Length--;
	}
	m_Length++;
}

void str::free()
{
	DELETE_ARRAY(m_Data);
	m_Data = NULLPTR;
	m_Length = m_Capacity = NULL;

}

void str::copy_from(const str& other)
{
	m_Length = other.m_Length;
	m_Capacity = other.m_Capacity;

	ALLOCATE_NEW_ARRAY(m_Data, char, m_Capacity + ONE);
	str_copy(m_Data, other.m_Data);
}

void str::move_from(str&& other)
{
	m_Length = other.m_Length;
	m_Capacity = other.m_Capacity;
	other.m_Length = other.m_Capacity = NULL;

	m_Data = other.m_Data;
	other.m_Data = NULLPTR;
}

void str::resize(size_t capacity)
{
	if (m_Capacity == capacity)
	{
		return;
	}

	char* _resized_data = NULLPTR;
	ALLOCATE_NEW_ARRAY(_resized_data, char, capacity + ONE);

	str_copy(_resized_data, m_Data);

	DELETE_ARRAY(m_Data);

	m_Data = _resized_data;
	m_Capacity = capacity;
}

DCL_END