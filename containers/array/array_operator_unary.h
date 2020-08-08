#include "../array.h"

namespace cvpp
{

// Array += Array
TPL_TC TPL_U Array<T,C>&
Array<T,C>::operator+=( const U& val )
{
    #pragma omp parallel for
    for( unsigned i = 0 ; i < C ; i++ )
        data[i] += val;
    return *this;
}

// Array -= Array
TPL_TC TPL_U Array<T,C>&
Array<T,C>::operator-=( const U& val )
{
    #pragma omp parallel for
    for( unsigned i = 0 ; i < C ; i++ )
        data[i] -= val;
    return *this;
}

// Array *= Array
TPL_TC TPL_U Array<T,C>&
Array<T,C>::operator*=( const U& val )
{
    #pragma omp parallel for
    for( unsigned i = 0 ; i < C ; i++ )
        data[i] *= val;
    return *this;
}

// Array /= Array
TPL_TC TPL_U Array<T,C>&
Array<T,C>::operator/=( const U& val )
{
    #pragma omp parallel for
    for( unsigned i = 0 ; i < C ; i++ )
        data[i] /= val;
    return *this;
}

}
