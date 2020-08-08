#include "../vector.h"

namespace cvpp
{

// - Vector
TPL_DTM inline Vector<D,T,M>
Vector<D,T,M>::operator-() const
{
    return clone().mlt( -1.0 );
}

// Vector += Element
TPL_DTM inline Vector<D,T,M>&
Vector<D,T,M>::operator+=( const D& elm )
{
    #pragma omp parallel for
    forLOOPi( n() )
        at(i) += elm;
    return *this;
}

// Vector -= Element
TPL_DTM inline Vector<D,T,M>&
Vector<D,T,M>::operator-=( const D& elm )
{
    #pragma omp parallel for
    forLOOPi( n() )
        at(i) -= elm;
    return *this;
}

// Vector *= Value
TPL_DTM TPL_U inline Vector<D,T,M>&
Vector<D,T,M>::operator*=( const U& val )
{
    mat() *= val;
    return *this;
}

// Vector /= Value
TPL_DTM TPL_U inline Vector<D,T,M>&
Vector<D,T,M>::operator/=( const U& val )
{
    mat() /= val;
    return *this;
}

// Vector += Vector
TPL_DTM inline Vector<D,T,M>&
Vector<D,T,M>::operator+=( const Vector<D,T,M>& vec )
{
    mat() += vec.mat();
    return *this;
}

// Vector -= Vector
TPL_DTM inline Vector<D,T,M>&
Vector<D,T,M>::operator-=( const Vector<D,T,M>& vec )
{
    mat() -= vec.mat();
    return *this;
}

// Vector %= Vector
TPL_DTM inline Vector<D,T,M>&
Vector<D,T,M>::operator%=( const Vector<D,T,M>& vec )
{
    mat() %= vec.mat();
    return *this;
}

// Vector /= Vector
TPL_DTM inline Vector<D,T,M>&
Vector<D,T,M>::operator/=( const Vector<D,T,M>& vec )
{
    mat() /= vec.mat();
    return *this;
}

// Vector *= Matrix
TPL_DTM inline Vector<D,T,M>&
Vector<D,T,M>::operator*=( const Matrix<T>& mat )
{
    if( d() == mat.c() )
    {
        this->mat() *= mat;
    }
    else
    {
        this->mat() *= mat.b( 0 , 0 , d() , d() );
        this->mat() += mat.b( 0 , d() , d() , 1 ).t();
    }

    return *this;
}

}
