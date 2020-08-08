#include "../device.h"

namespace cvpp
{

// Backslash
TPL_T Device<T>
Device<T>::bslash( const Device<T>& dev ) const
{
    return af::solve( arr() , dev.arr() );
}

// Backslash Cholesky
TPL_T Device<T>
Device<T>::cbslash( const Device<T>& dev ) const
{
    return af::solve( arr() , dev.arr() , AF_MAT_LOWER );
}


}
