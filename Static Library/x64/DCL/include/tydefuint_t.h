#pragma once

//unsigned integers
typedef unsigned long long  ularge;
typedef unsigned long        ulong;
typedef unsigned int          uint;
typedef unsigned short      ushort;
typedef unsigned char  uchar, byte;

#pragma warning(push)          
#pragma warning(disable : 4005) 

#define UINT_MIN       0x0ui8
#define UCHAR_MAX      0xffui8
#define USHORT_MAX     0xffffui16
#define UINT_MAX       0xffffffffui32
#define ULONG_MAX      0xffffffffui32
#define ULARGE_MAX     0xffffffffffffffffui64

#pragma warning(pop)