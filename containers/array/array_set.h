#include "../array.h"

namespace cvpp
{

// Print
TPL_TC Array<T,C>&
Array<T,C>::setVal( const T& val )
{
    for( unsigned i = 0 ; i < C ; i++ )
        data[i] = val;
    return *this;
}

// Info
TPL_TC Array<T,C>&
Array<T,C>::setIncrease( const T& start , const T& step )
{
    for( unsigned i = 0 ; i < C ; i++ )
        data[i] = start + (T)i * step;
    return *this;
}

}
