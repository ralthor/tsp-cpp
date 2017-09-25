#include "solution.h"

template <class T>Solution<T>::Solution(T value)
{
    this->value = value;
}

template <class T>Solution<T>::Solution()
{
    //ctor
}

//template <class T>Solution<T>::~Solution()
//{
//    //dtor
//}

template <class T> void Solution<T>::set(T value)
{
    this->value = value;
}

template <class T> T Solution<T>::get()
{
    return value;
}

