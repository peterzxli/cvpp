#include "../device.h"

namespace cvpp
{

// ********************************************************** VALUE

// Device + Value
TPL_TU Device<T>
operator+( const Device<T>& dev , const U& val )
{
    return Device<T>( dev.arr() + val );
}

// Device - Value
TPL_TU Device<T>
operator-( const Device<T>& dev , const U& val )
{
    return Device<T>( dev.arr() - val );
}

// Device * Value
TPL_TU Device<T>
operator*( const Device<T>& dev , const U& val )
{
    return Device<T>( dev.arr() * val );
}

// Device / Value
TPL_TU Device<T>
operator/( const Device<T>& dev , const U& val )
{
    return Device<T>( dev.arr() / val );
}

// ********************************************************** DEVICE

// Device + Device
TPL_T Device<T>
operator+( const Device<T>& dev1 , const Device<T>& dev2 )
{
    return Device<T>( dev1.arr() + dev2.arr() );
}

// Device - Device
TPL_T Device<T>
operator-( const Device<T>& dev1 , const Device<T>& dev2 )
{
    return Device<T>( dev1.arr() - dev2.arr() );
}

// Device * Device
TPL_T Device<T>
operator*( const Device<T>& dev1 , const Device<T>& dev2 )
{
    return Device<T>( af::matmul( dev1.arr() , dev2.arr() ) );
}

// Device % Device
TPL_T Device<T>
operator%( const Device<T>& dev1 , const Device<T>& dev2 )
{
    return Device<T>( dev1.arr() * dev2.arr() );
}

// Device / Device
TPL_T Device<T>
operator/( const Device<T>& dev1 , const Device<T>& dev2 )
{
    return Device<T>( dev1.arr() / dev2.arr() );
}

}
