#pragma once
#include <dcl_defines.h>

DCL_BEGIN

template<typename T>
class scoped_ptr 
{
public:
    inline explicit scoped_ptr(T* ptr = nullptr) noexcept : m_ptr(ptr) {}

    inline ~scoped_ptr() 
    {
        delete m_ptr;
    }

    inline scoped_ptr(const scoped_ptr&) = delete;
    inline scoped_ptr& operator=(const scoped_ptr&) = delete;

    inline scoped_ptr(scoped_ptr&& other) noexcept : m_ptr(other.release()) {}

    inline scoped_ptr& operator=(scoped_ptr&& other) noexcept
    {
        if (this != &other) 
        {
            reset(other.release());
        }
        return *this;
    }

    inline T& operator*() const
    {
        return *m_ptr;
    }

    inline T* operator->() const noexcept
    {
        return m_ptr;
    }

    inline explicit operator bool() const noexcept
    {
        return m_ptr != nullptr;
    }

    inline T* get() const noexcept
    {
        return m_ptr;
    }

    inline T* release() noexcept
    {
        T* old_ptr = m_ptr;
        m_ptr = nullptr;
        return old_ptr;
    }

    inline void reset(T* ptr = nullptr) noexcept
    {
        T* old_ptr = m_ptr;
        m_ptr = ptr;
        delete old_ptr;
    }

    inline void swap(scoped_ptr& other) noexcept
    {
        T* tmp = m_ptr;
        m_ptr = other.m_ptr;
        other.m_ptr = tmp;
    }

private:
    T* m_ptr;
};

DCL_END