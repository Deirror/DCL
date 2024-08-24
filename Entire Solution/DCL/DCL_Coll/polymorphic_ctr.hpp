#pragma once
#include "vec.hpp"
#include <dcl_defines.h>

DCL_BEGIN

template<typename T>
class polymorphic_ctr {
private:
	Vector<polymorphic_ptr<T>> ptrs;

public:
	void add(T* ptr);
	void execute(size_t index, void(*func)(T*));
	void execute(size_t index, void(*func)(const T*)) const;
};

template<typename T>
void polymorphic_ctr<T>::add(T* ptr) {
	ptrs.push_back(ptr);
}

template<typename T>
void polymorphic_ctr<T>::execute(size_t index, void(*func)(T*)) {
	func(ptrs[index].get());
}


template<typename T>
void polymorphic_ctr<T>::execute(size_t index, void(*func)(const T*)) const {
	func(ptrs[index].get());
}

DCL_END
