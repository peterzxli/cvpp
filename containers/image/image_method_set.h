#include "../image.h"

namespace cvpp
{

// Set Val
TPL_TC inline Image<T,C>&
Image<T,C>::setVal( const T& val )
{
    eig().fill( val );
    return *this;
}

// Set Increase
TPL_TC inline Image<T,C>&
Image<T,C>::setIncrease( const T& start ,
                         const T& step )
{
    T cnt = 0;
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            for( unsigned k = 0 ; k < d() ; k++ )
                at(i,j,k) = start + (double)cnt++ * step;
    return *this;
}

}
