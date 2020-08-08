#include "../image.h"

namespace cvpp
{

// Gradient Rows (NEW)
TPL_TC inline Image<float,1>
Image<T,C>::gradRow() const
{
    Image<float,1> grad( dims() ); grad = 0;
    for( int i = 1 ; i < grad.r() - 1 ; ++i )
        for( int j = 1 ; j < grad.c() - 1 ; ++j )
            grad(i,j) = ( at(i+1,j) - at(i-1,j) ) / 2.0;
    return grad;
}

// Gradient Cols (NEW)
TPL_TC inline Image<float,1>
Image<T,C>::gradCol() const
{
    Image<float,1> grad( dims() ); grad = 0;
    for( int i = 1 ; i < grad.r() - 1 ; ++i )
        for( int j = 1 ; j < grad.c() - 1 ; ++j )
            grad(i,j) = ( at(i,j+1) - at(i,j-1) ) / 2.0;
    return grad;
}

// Gradient Diagonal Up (NEW)
TPL_TC inline Image<float,1>
Image<T,C>::gradDiagU() const
{
    Image<float,1> grad( dims() ); grad = 0;
    for( int i = 1 ; i < grad.r() - 1 ; ++i )
        for( int j = 1 ; j < grad.c() - 1 ; ++j )
            grad(i,j) = ( at(i+1,j-1) - at(i-1,j+1) ) / 2.0;
    return grad;
}

// Gradient Diagonal Down (NEW)
TPL_TC inline Image<float,1>
Image<T,C>::gradDiagD() const
{
    Image<float,1> grad( dims() ); grad = 0;
    for( int i = 1 ; i < grad.r() - 1 ; ++i )
        for( int j = 1 ; j < grad.c() - 1 ; ++j )
            grad(i,j) = ( at(i+1,j+1) - at(i-1,j-1) ) / 2.0;
    return grad;
}

}
