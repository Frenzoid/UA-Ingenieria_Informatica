#ifndef VECTORDEQUE_T_H
#define VECTORDEQUE_T_H

#include <algorithm>
#include <vector>


// Implement a deque in a vector, so that it can be accessed
// as one or two (when circular) old-style arrays.
template <class T>
class VectorDeque {
public:
	typedef typename std::vector<T>::size_type size_type;
private:
	std::vector<T> vec_;
	size_type first_, size_;
public:
	VectorDeque()
		: first_(0), size_(0) {}
	explicit VectorDeque(size_type capacity)
		: vec_(capacity), first_(0), size_(0) {}
	size_type Capacity() const
		{ return vec_.size(); }
	size_type Size() const
		{ return size_; }
	T & operator[](size_type i)
		{ return vec_[(first_ + i) % Capacity()]; }
	const T & operator[](size_type i) const
		{ return vec_[(first_ + i) % Capacity()]; }
	T * Vector1()
		{ return &vec_[first_]; }
	const T * Vector1() const
		{ return &vec_[first_]; }
	size_type Vector1Size() const
		{ return std::min(Capacity() - first_, size_); }
	T * Vector2()
		{ return &vec_[0]; }
	const T * Vector2() const
		{ return &vec_[0]; }
	size_type Vector2Size() const
		{ return size_ - Vector1Size(); }
	void Push(T);
	void Pop();
private:
	void Grow(size_type add_capacity);
};


template <class T>
void VectorDeque<T>::Push(T t)
{
	if (size_ == Capacity()) Grow(Capacity() / 4 + 1);
	vec_[(first_ + size_) % Capacity()] = t;
	++size_;
}

template <class T>
inline void VectorDeque<T>::Pop()
{
	first_ = (first_ + 1) % Capacity();
	--size_;
}

template <class T>
void VectorDeque<T>::Grow(size_type add_capacity)
{
	vec_.resize(vec_.size() + add_capacity);
	if (first_ + size_ > vec_.size() - add_capacity) {
		std::copy(vec_.rbegin() + add_capacity,
		          vec_.rbegin() + (vec_.size() - first_),
			  vec_.rbegin());
		first_ += add_capacity;
	}
}


#endif
