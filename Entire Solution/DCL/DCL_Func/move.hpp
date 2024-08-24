#pragma once
#include <dcl_defines.h>

DCL_BEGIN

template<class T>
inline T&& move(T& arg) 
{
	return static_cast<T&&>(arg);
}

template<class T>
inline T&& move(T&& arg) 
{
	return static_cast<T&&>(arg);
}

DCL_END