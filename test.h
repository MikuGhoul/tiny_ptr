#include <iostream>
#include <memory>
#include <string>

template <typename T>
class tiny_ptr;

template <typename T>
tiny_ptr<T> &make_ptr(const T &);

template <typename T>
class Point {
	friend class tiny_ptr<T>;
	friend tiny_ptr<T> &make_ptr<T>(const T &);
private:
	Point() = default;
	explicit Point(T *_p) : p(_p), count(0) {}
	~Point() { delete p; }

	T *p;
	size_t count;
};

// just like shared_ptr<>
template <typename T>
class tiny_ptr {
public:
	tiny_ptr() : poi(new Point<T>()){}
	explicit tiny_ptr(T *);
	tiny_ptr(Point<T> *);
	tiny_ptr(tiny_ptr &);

	tiny_ptr& operator=(tiny_ptr&);
	T& operator*();
	T* operator->();

	size_t use_count() { return poi->count; }
	void reset() {
		if (poi->count == 1)
			poi->~Point();
		poi = nullptr;
	}
	void reset(T *);
	void swap(tiny_ptr &);
	T* get() const {
		return poi->p;
	}

	~tiny_ptr()
	{
		if (poi) {
			--poi->count;
			if (!poi->count)
				delete poi;
		}
	}
private:
	Point<T> *poi;
};

template <typename T>
tiny_ptr<T>::tiny_ptr(T *t)
{
	poi = new Point<T>(t);
	++poi->count;
}

template <typename T>
tiny_ptr<T>::tiny_ptr(Point<T> *_p)
{
	poi = _p;
}

template <typename T>
tiny_ptr<T>::tiny_ptr(tiny_ptr<T> & fp)
{
	
	poi = fp.poi;
	++poi->count;
}

template <typename T>
tiny_ptr<T>& tiny_ptr<T>::operator= (tiny_ptr<T> & fp)
{
	poi = fp.poi;
	++poi->count;
	return *this;
}

template <typename T>
T& tiny_ptr<T>::operator*()
{
	return *(poi->p);
}

template <typename T>
T* tiny_ptr<T>::operator->()
{
	return poi->p;
}

template <typename T>
void tiny_ptr<T>::reset(T *arg)
{
	reset();
	poi = new Point<T>(arg);
}

template <typename T>
void tiny_ptr<T>::swap(tiny_ptr<T> &arg)
{
	auto temp = arg.poi;
	arg.poi = poi;
	poi = temp;
}

// just like make_shared<>
template <typename T>
tiny_ptr<T> &make_ptr(const T &arg)
{
 	return *(new tiny_ptr<T>(new Point<T>(new T(arg))));
}
