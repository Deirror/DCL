#pragma once
#include <dcl_defines.h>

void str_copy(char* dest, const char* src);

void str_copy(char* dest, const char* src, size_t count, size_t idx);

size_t str_len(const char* str);

void str_concat(char* dest, const char* src);

const char* str_str(const char* str, const char* substr);

const char* str_ch(const char* str, char ch);

size_t str_cmpr(const char* lhs, const char* rhs);
