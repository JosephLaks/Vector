//#include "vector.h"
#pragma once
template<class T>
class vec_iterator
{
private:
	T* p = nullptr;
public:
	vec_iterator(T* const);
	T& operator*();
	T const& operator*()const;
	T* operator->();

	vec_iterator<T>& operator++(); //prefix
	vec_iterator<T> operator++(int); //postfix
	vec_iterator<T>& operator--(); //prefix
	vec_iterator<T> operator--(int); //postfix

	vec_iterator<T>& operator+=(size_t const);
	vec_iterator<T>& operator-=(size_t const);

	vec_iterator<T> operator+ (size_t const) const;
	vec_iterator<T> operator- (size_t const) const;
	size_t operator- (vec_iterator<T>& const) const;

	bool operator== (vec_iterator<T>& const);
	bool operator!= (vec_iterator<T>& const);
	bool operator> (vec_iterator<T>& const);
	bool operator< (vec_iterator<T>& const);
	bool operator>= (vec_iterator<T>& const);
	bool operator<= (vec_iterator<T>& const);
};

template<class T>
inline vec_iterator<T>::vec_iterator(T* const ptr):p(ptr){}

template<class T>
inline T& vec_iterator<T>::operator*()
{
	return *p;
}

template<class T>
inline T const& vec_iterator<T>::operator*() const
{
	return *p;
}

template<class T>
inline T* vec_iterator<T>::operator->()
{
	return p;
}

template<class T>
inline vec_iterator<T>& vec_iterator<T>::operator++() //prefix
{
	++p;
	return *this;
}

template<class T>
inline vec_iterator<T> vec_iterator<T>::operator++(int) //postfix
{
	return p++;
}

template<class T>
inline vec_iterator<T>& vec_iterator<T>::operator--() //prefix
{
	--p;
	return *this;
}

template<class T>
inline vec_iterator<T> vec_iterator<T>::operator--(int) //postfix
{
	return p--;
}

template<class T>
inline vec_iterator<T>& vec_iterator<T>::operator+=(size_t const n)
{
	p += n;
	return *this;
}

template<class T>
inline vec_iterator<T>& vec_iterator<T>::operator-=(size_t const n)
{
	p -= n;
	return *this;
}

template<class T>
inline vec_iterator<T> vec_iterator<T>::operator+(size_t const n) const
{
	return vec_iterator<T>(p+n);
}

template<class T>
inline vec_iterator<T> vec_iterator<T>::operator-(size_t const n) const
{
	return vec_iterator<T>(p - n);
}

template<class T>
inline size_t vec_iterator<T>::operator-(vec_iterator<T>& const rhs) const
{
	return p - rhs.p;
}

template<class T>
inline bool vec_iterator<T>::operator==(vec_iterator<T>& const rhs)
{
	return p == rhs.p;
}

template<class T>
inline bool vec_iterator<T>::operator!=(vec_iterator<T>& const rhs)
{
	return p != rhs.p;
}

template<class T>
inline bool vec_iterator<T>::operator>(vec_iterator<T>& const rhs)
{
	return p > rhs.p;
}

template<class T>
inline bool vec_iterator<T>::operator<(vec_iterator<T>& const rhs)
{
	return p < rhs.p;
}

template<class T>
inline bool vec_iterator<T>::operator>=(vec_iterator<T>& const rhs)
{
	return p >= rhs.p;
}

template<class T>
inline bool vec_iterator<T>::operator<=(vec_iterator<T>& const rhs)
{
	return p <= rhs.p;
}
