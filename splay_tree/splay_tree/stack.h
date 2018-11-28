#pragma once
#include <cstring>

template<typename T>
class stack
{
private:
	size_t capacity;
	T * elements;
	size_t size_;
	void check_capacity();
public:
	stack() : capacity(8), elements(new T[capacity]), size_(0) {}
	~stack();
	void push_back(const T & element);
	T pop_back();
	T & back();
	size_t size();
	void clear();
	T& operator [](size_t index);
};

template<typename T>
void stack<T>::check_capacity()
{
	if (size_ >= capacity)
	{
		capacity *= 2;
		T * temp = new T[capacity];
		memcpy(temp, elements, size_ * sizeof(T));
		delete[] elements;
		elements = temp;
	}
}

template<typename T>
stack<T>::~stack()
{
	delete[] elements;
}

template<typename T>
void stack<T>::push_back(const T & element)
{
	check_capacity();
	elements[size_] = element;
	++size_;
}

template<typename T>
T stack<T>::pop_back()
{
	if (size_ > 0)
		return elements[--size_];
}

template<typename T>
T & stack<T>::back()
{
	if (size_ > 0)
		return elements[size_ - 1];

}

template<typename T>
size_t stack<T>::size()
{
	return size_;
}

template<typename T>
void stack<T>::clear()
{
	size_ = 0;
}

template<typename T>
T & stack<T>::operator[](size_t index)
{
	if (index < size_ && index >= 0)
	{
		return elements[index];
	}
}
