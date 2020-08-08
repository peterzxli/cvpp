#include "../vector.h"

namespace cvpp
{

// Vector + Element
TPL_DTM inline Vector<D,T,M>
operator+( const Vector<D,T,M> vec , const D& elm )
{
    return vec.clone() += elm;
}

// Vector - Element
TPL_DTM inline Vector<D,T,M>
operator-( const Vector<D,T,M> vec , const D& elm )
{
    return vec.clone() -= elm;
}

// Element + Vector
TPL_DTM inline Vector<D,T,M>
operator+( const D& elm , const Vector<D,T,M> vec )
{
    return vec.clone() += elm;
}

// Element - Vector
TPL_DTM inline Vector<D,T,M>
operator-( const D& elm , const Vector<D,T,M> vec )
{
    return vec.clone().mlt( -1.0 ) += elm;
}

// Vector * Value
TPL_DTM inline Vector<D,T,M>
operator*( const Vector<D,T,M> vec , const T& val )
{
    return vec.clone() *= val;
}

// Vector / Value
TPL_DTM inline Vector<D,T,M>
operator/( const Vector<D,T,M> vec , const T& val )
{
    return vec.clone() /= val;
}

// Value * Vector
TPL_DTM inline Vector<D,T,M>
operator*( const T& val , const Vector<D,T,M> vec )
{
    return vec.clone() *= val;
}

// Value / Vector
TPL_DTM inline Vector<D,T,M>
operator/( const T& val , const Vector<D,T,M> vec )
{
    Vector<D,T,M> tmp = vec.clone();
    tmp.mat().Denominator(); return tmp *= val;
}

// Vector + Vector
TPL_DTM inline Vector<D,T,M>
operator+( const Vector<D,T,M>& vec1 , const Vector<D,T,M> vec2 )
{
    Vector<D,T,M> tmp = vec1.clone();
    return tmp += vec2;
}

// Vector - Vector
TPL_DTM inline Vector<D,T,M>
operator-( const Vector<D,T,M>& vec1 , const Vector<D,T,M> vec2 )
{
    Vector<D,T,M> tmp = vec1.clone();
    return tmp -= vec2;
}

// Vector % Vector
TPL_DTM inline Vector<D,T,M>
operator%( const Vector<D,T,M>& vec1 , const Vector<D,T,M> vec2 )
{
    Vector<D,T,M> tmp = vec1.clone();
    return tmp %= vec2;
}

// Vector * Matrix
TPL_DTM inline Vector<D,T,M>
operator*( const Vector<D,T,M>& vec , const Matrix<T>& mat )
{
    return vec.clone() *= mat;
}

}
