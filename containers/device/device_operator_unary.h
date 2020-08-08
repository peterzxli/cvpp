#include "../device.h"

namespace cvpp
{

// ********************************************************** VALUE

// Device += Value
TPL_T TPL_U Device<T>&
Device<T>::operator+=( const U& val )
{
    arr() = arr().copy() + val;
    return *this;
}

// Device -= Value
TPL_T TPL_U Device<T>&
Device<T>::operator-=( const U& val )
{
    arr() = arr().copy() - val;
    return *this;
}

// Device *= Value
TPL_T TPL_U Device<T>&
Device<T>::operator*=( const U& val )
{
    arr() = arr().copy() * val;
    return *this;
}

// Device /= Value
TPL_T TPL_U Device<T>&
Device<T>::operator/=( const U& val )
{
    arr() = arr().copy() / val;
    return *this;
}

// ********************************************************** DEVICE

// Device += Device
TPL_T Device<T>&
Device<T>::operator+=( const Device<T>& dev )
{
    arr() = arr().copy() + dev.arr();
    return *this;
}

// Device -= Device
TPL_T Device<T>&
Device<T>::operator-=( const Device<T>& dev )
{
    arr() = arr().copy() - dev.arr();
    return *this;
}

// Device *= Device
TPL_T Device<T>&
Device<T>::operator*=( const Device<T>& dev )
{
    arr() = af::matmul( arr().copy() , dev.arr().copy() );
    return *this;
}

// Device %= Device
TPL_T Device<T>&
Device<T>::operator%=( const Device<T>& dev )
{
    arr() = arr().copy() * dev.arr();
    return *this;
}

// Device /= Device
TPL_T Device<T>&
Device<T>::operator/=( const Device<T>& dev )
{
    arr() = arr().copy() / dev.arr();
    return *this;
}

}
