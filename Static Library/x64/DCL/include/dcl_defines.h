#pragma once

/*
DEIRROR'S STANDART LIBRARY -> DSL
*/

#define DCL_BEGIN \
namespace dcl {

#define DCL_END }

#define DCL ::dcl::

#define NULLPTR nullptr 
#define EMPTY "\0"
#define TERM_NULL '\0'
#define START_LOWER 'a'
#define END_LOWER 'z'

#define START_UPPER 'A'
#define END_UPPER 'Z'

#define LOW_UP_DIFF 'a' - 'A'

#pragma warning(push)
#pragma warning(disable : 4005)

#define NULL 0x0
#define ONE 0x1
#define BIN 0x2
#define QUAT 0x4
#define OCT 0x8
#define HEX 0x10

#pragma warning(pop)

#define M_ONE -ONE

#define MAX_ASCII_CODE 0xFF
#define SIZE_MAX 0xffffffffffffffffui64

#define DELETE_ARRAY(_array) \
delete[] _array

#define DELETE(_array) \
delete _array

#define ALLOCATE_NEW_ARRAY(_array, _type, _size) \
_array = new _type[_size]{}

#define CSTYLE_CAST(_type, _value) (_type)_value