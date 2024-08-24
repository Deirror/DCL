#pragma once
#include <dcl_defines.h>
#include <iter.hpp>
#include <except.h>
#include <tydefios.h>
#include <compr.h>

DCL_BEGIN

#define DEFAULT_CAPACITY OCT
#define FACTOR BIN
#define DOWN_FACTOR QUAT

#define NOT_FOUND M_ONE

class str 
{
public:
	str();

	str(const char* data);

	str(const str& other);
	str& operator=(const str& other);

	str(str&& other) noexcept;
	str& operator=(str&& other) noexcept;

	~str() noexcept;

	size_t length() const;
	size_t capacity() const;

	const char* data() const;
	const char* c_str() const;

	size_t max_size() const;

	void push_back(const char ch);

	void pop_back();

	char& back();
	const char& back() const;

	str& operator+=(const str& other);
	str& operator+=(char ch);

	friend str operator+(const str& lhs, const str& rhs);

	str& append(const str& other);

	friend dcl::ostream& operator<<(dcl::ostream& os, const str& other);
	friend dcl::istream& operator>>(dcl::istream& is, str& other);

	char& operator[](size_t idx);
	const char& operator[](size_t idx) const;

	char& at(size_t idx);
	const char& at(size_t idx) const;

	char& front();
	const char& front() const;

	void assign(const str& other);
	void assign(const char* ptr);

	compr compare(const str& other) const;

	void copy_to(char*& ptr, size_t start_idx, size_t count) const;

	str& erase(size_t from);
	str& erase(size_t from, size_t count);

	str& trim(const str& exclude);
	str& trim(const char* exclude);
	str& trim(char exclude);

	str to_upper() const;
	str to_lower() const;

	size_t find(const str& searched, size_t from) const;
	size_t find(const char* ptr, size_t from) const;
	size_t find(char ch, size_t from) const;

	size_t rfind(const str& searched, size_t from) const;
	size_t rfind(const char* ptr, size_t from) const;
    size_t rfind(char ch, size_t from) const;

	size_t find_first_of(const str& searched, size_t from) const;
	size_t find_first_of(const char* ptr, size_t from) const;
	size_t find_first_of(char ch, size_t from) const;

	size_t find_first_not_of(const str& searched, size_t from) const;
	size_t find_first_not_of(const char* ptr, size_t from) const;
	size_t find_first_not_of(char ch, size_t from) const;

	size_t find_last_of(const str& searched, size_t from) const;
	size_t find_last_of(const char* ptr, size_t from) const;
	size_t find_last_of(char ch, size_t from) const;

	size_t find_last_not_of(const str& searched, size_t from) const;
	size_t find_last_not_of(const char* ptr, size_t from) const;
	size_t find_last_not_of(char ch, size_t from) const;

	bool contains(const char* ptr) const;
	bool contains(char ch) const;

	iter<char> begin() const;
	iter<char> end() const;

	const_iter<char> cbegin() const;
	const_iter<char> cend() const;

	rev_iter<char> rbegin() const;
	rev_iter<char> rend() const;

	const_rev_iter<char> crbegin() const;
	const_rev_iter<char> crend() const;

	void reserve(size_t length);
	void shrink_to_fit();

	str& insert(const str& other, size_t from);
	str& insert(const char* ptr, size_t from);

	str& replace(const str& searched, const str& replace_with, size_t from);
	str& replace(const char* searched, const char* replace_with, size_t from);
	str& replace(char searched, char replace_with, size_t from);

	str subdstr(size_t from, size_t count) const;

	void swap(str& other);

	bool empty() const;
	void clear();

private:
	explicit str(size_t length);

	void down_size(size_t count);

	void free();
	void copy_from(const str& other);
	void move_from(str&& other);

	void resize(size_t capacity);

private:
	char* m_Data = NULLPTR;

	size_t m_Length = NULL;
	size_t m_Capacity = NULL;
};

bool operator==(const str& lhs, const str& rhs);
bool operator!=(const str& lhs, const str& rhs);
bool operator<(const str& lhs, const str& rhs);
bool operator<=(const str& lhs, const str& rhs);
bool operator>(const str& lhs, const str& rhs);
bool operator>=(const str& lhs, const str& rhs);

DCL_END