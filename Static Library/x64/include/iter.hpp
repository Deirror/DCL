#pragma once
#include <dcl_defines.h>

DCL_BEGIN

template<class T>
class iter
{
public:
    inline iter(T* container) : m_Container(container) {}

    inline iter<T>& operator++() 
    {
        ++m_Container;
        return *this;
    }

    inline iter<T> operator++(int) 
    {
        iter temp = *this;
        ++m_Container;
        return temp;
    }

    inline iter<T>& operator--()
    {
        --m_Container;
        return *this;
    }

    inline iter<T> operator--(int) 
    {
        iter temp = *this;
        --m_Container;

        return temp;
    }

    inline bool operator==(const iter<T>& other) const
    {
        return m_Container == other.m_Container;
    }

    inline bool operator!=(const iter<T>& other) const
    {
        return m_Container != other.m_Container;
    }

    inline T& operator*() const 
    {
        return *m_Container;
    }

    inline T* operator->() const 
    {
        return &(*m_Container);
    }

private:
	T* m_Container;
};

template<class T>
class const_iter 
{
public:
    inline const_iter(const T* container) : m_Container(container) {}

    inline const_iter& operator++()
    {
        ++m_Container;
        return *this;
    }

    inline const_iter operator++(int)
    {
        const_iter temp = *this;
        ++m_Container;
        return temp;

    }

    inline const_iter& operator--()
    {
        --m_Container;
        return *this;
    }

    inline const_iter operator--(int)
    {
        const_iter temp = *this;
        --m_Container;
        return temp;
    }

    inline bool operator==(const const_iter& other) const
    {
        return m_Container == other.m_Container;
    }

    inline bool operator!=(const const_iter& other) const
    {
        return m_Container != other.m_Container;
    }

    inline const T& operator*() const
    {
        return *m_Container;
    }

    inline const T* operator->() const
    {
        return &(*m_Container);
    }

private:
    const T* m_Container;
};

template<class T>
class rev_iter 
{
public:
    inline rev_iter(T* container) : m_Container(container) {}

    inline rev_iter& operator++()
    {
        --m_Container;
        return *this;
    }

    inline rev_iter operator++(int)
    {
        rev_iter temp = *this;
        --m_Container;
        return temp;
    }

    inline rev_iter& operator--()
    {
        ++m_Container;
        return *this;
    }

    inline rev_iter operator--(int)
    {
        rev_iter temp = *this;
        ++m_Container;
        return temp;
    }

    inline bool operator==(const rev_iter& other) const
    {
        return m_Container == other.m_Container;
    }

    inline bool operator!=(const rev_iter& other) const
    {
        return m_Container != other.m_Container;
    }

    inline T& operator*() const
    {
        return *m_Container;
    }

    inline T* operator->() const
    {
        return &(*m_Container);
    }

private:
    T* m_Container;
};

template<class T>
class const_rev_iter 
{
public:
    inline const_rev_iter(const T* container) : m_Container(container) {}

    inline const_rev_iter& operator++()
    {
        --m_Container;
        return *this;
    }

    inline const_rev_iter operator++(int)
    {
        const_rev_iter temp = *this;
        --m_Container;
        return temp;
    }

    inline const_rev_iter& operator--()
    {
        ++m_Container;
        return *this;
    }

    inline const_rev_iter operator--(int)
    {
        const_rev_iter temp = *this;
        ++m_Container;
        return temp;
    }

    inline bool operator==(const const_rev_iter& other) const
    {
        return m_Container == other.m_Container;
    }

    inline bool operator!=(const const_rev_iter& other) const
    {
        return m_Container != other.m_Container;
    }

    inline const T& operator*() const
    {
        return *m_Container;
    }

    inline const T* operator->() const
    {
        return &(*m_Container);
    }

private:
    const T* m_Container;
};

DCL_END