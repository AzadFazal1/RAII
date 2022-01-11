/**
 * @file scoped_ptr.tcc
 * @author Chase Geigle
 * @date Summer 2014
 */

#include "scoped_ptr.h"

namespace cs225
{

template <class T>
scoped_ptr<T>::scoped_ptr()
{

}

template <class T>
scoped_ptr<T>::scoped_ptr(T* rawptr)
{

}

template <class T>
scoped_ptr<T>::scoped_ptr(scoped_ptr&& other)
{

}

template <class T>
scoped_ptr<T>& scoped_ptr<T>::operator=(scoped_ptr&& other)
{

}

template <class T>
scoped_ptr<T>::~scoped_ptr()
{

}

template <class T>
void scoped_ptr<T>::clear()
{

}

template <class T>
void scoped_ptr<T>::swap(scoped_ptr<T>& other)
{

}

template <class T>
bool scoped_ptr<T>::empty() const
{

}

template <class T>
const T& scoped_ptr<T>::operator*() const
{

}

template <class T>
T& scoped_ptr<T>::operator*()
{

}

template <class T>
const T* scoped_ptr<T>::operator->() const
{

}

template <class T>
T* scoped_ptr<T>::operator->()
{

}

template <class T>
const T* scoped_ptr<T>::get() const
{

}

template <class T>
T* scoped_ptr<T>::get()
{

}
}
