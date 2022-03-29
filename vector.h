#pragma once
#include<new>
#include "vec_iterator.h"
constexpr size_t initial_capacity = 10;

template <class T>
class vector
{
private:
	T* p = nullptr;
	size_t len = 0, cap;

	void swap(vector&); //copy-swap idiom
	void allocate(size_t const, T*); //allocate new memory, copy from the old location

public:
	vector();
	vector(size_t const);
	vector(vector const&); //copy ctor
	vector(vector&&); //move ctor
	vector(size_t const, T const&); //fill ctor
	~vector();
	vector& operator=(vector);
	vector& operator=(vector&&); //move assignment

	void push_back(T const&);
	void push_back(T&&); //move pushback
	void pop_back();

	T& operator[] (size_t const);
	T const& operator[](size_t const) const;

	vec_iterator<T> begin() const;
	vec_iterator<T> end() const;

	size_t size() const;
	size_t capacity() const;

	void reserve(size_t const);
};

template<class T>
inline void vector<T>::swap(vector& rhs)
{
	std::swap(len, rhs.len);
	std::swap(cap, rhs.cap);
	std::swap(p, rhs.p);
}

template<class T>
inline vector<T>::vector(): len(0), cap(initial_capacity)
{
	allocate(cap, nullptr);
}

template<class T>
inline vector<T>::vector(size_t const size): len(size), cap(size)
{
	p = new T[len];
}

template<class T>
inline vector<T>::vector(vector const& rhs) : len(rhs.len), cap(rhs.cap) //copy ctor
{
	allocate(cap, rhs.p);
}

template<class T>
inline vector<T>::vector(vector&& rhs): len(rhs.len), cap(rhs.cap), p(rhs.p) //move ctor
{
	rhs.p = nullptr;
	rhs.len = rhs.cap = 0;
}

template<class T>
inline vector<T>::vector(size_t const size, T const& filler) : len(size), cap(len) //fill ctor
{
	allocate(cap, p);
	for (size_t i = 0; i < len; ++i)
	{
		new(&p[i]) T(filler);
	}

}

template<class T>
inline vector<T>::~vector()
{
	for (size_t i = 0; i < len; ++i)
		p[i].~T();
	::operator delete(p);
}

template<class T>
inline vector<T>& vector<T>::operator=(vector<T> rhs)
{
	swap(rhs);
	return *this;
}

template<class T>
inline vector<T>& vector<T>::operator=(vector&& rhs) //move assignment
{
	swap(rhs);
	return *this;
}

template<class T>
inline void vector<T>::push_back(T const& val)
{
	if (len == cap)
		allocate(2 * cap, p);
	new(&p[len++]) T(val);
}

template<class T>
inline void vector<T>::push_back(T&& val) //move a temporary object into the end of the vector
{
	if (len == cap)
		allocate(2 * cap, p);
	new(&p[len++]) T(val);
}

template<class T>
inline void vector<T>::pop_back()
{
	if(len)
		p[len--].~T();
}

template<class T>
inline void vector<T>::reserve(size_t const size)
{
	if (size > cap)
		allocate(size, p);
}

template<class T>
inline T& vector<T>::operator[](size_t const index)
{
	if (index >= len)
		throw("Index is too high.");
	if (index < 0)
		throw("Negative index not allowed");
	return p[index];
}
template<class T>
inline const T& vector<T>::operator[](size_t const index) const
{
	if (index >= len)
		throw("Index is too high.");
	if (index < 0)
		throw("Negative index not allowed");
	return p[index];
}

template<class T>
inline vec_iterator<T> vector<T>::begin() const
{
	return vec_iterator<T>(p);
}

template<class T>
inline vec_iterator<T> vector<T>::end() const
{
	return vec_iterator<T>(p+len);
}

template<class T>
inline size_t vector<T>::size() const
{
	return len;
}

template<class T>
inline size_t vector<T>::capacity() const
{
	return cap;
}

template<class T>
inline void vector<T>::allocate(size_t const size, T* ptr) //copy data from ptr; this will typically be p
{
	T* temp = reinterpret_cast<T*>(::operator new(size * sizeof(T)));
	if (ptr)
	{
		for (size_t i = 0; i < len; ++i)
		{
			new(&temp[i]) T(ptr[i]);
			p[i].~T();
		}
		::operator delete(ptr);
	}
	p = temp;
	cap = size;
}
