#include "../vector.h"

namespace cvpp
{

// Vector >> Vector
TPL_DTM Vector<D,T,M>&
Vector<D,T,M>::operator>>( const Vector<D,T,M>& vec )
{
    off = vec.off;

    std_ptr = vec.std_ptr;
    mat_ptr = vec.mat_ptr;

    return *this;
}

// Vector = Vector
TPL_DTM Vector<D,T,M>&
Vector<D,T,M>::operator=( const Vector<D,T,M>& vec )
{
    if( fits( vec ) )
        eig() = vec.eig();
    else *this << vec;

    return *this;
}

// Vector << Vector
TPL_DTM inline Vector<D,T,M>&
Vector<D,T,M>::operator<<( const Vector<D,T,M>& vec )
{
    initialise( vec.n() );
    eig() = vec.eig();

    return *this;
}

// Vector = Matrix
TPL_DTM Vector<D,T,M>&
Vector<D,T,M>::operator=( const Matrix<T>& mat )
{
    if( fits( mat ) )
        eig() = mat.eig();
    else *this << mat;

    return *this;
}

// Vector << Matrix
TPL_DTM inline Vector<D,T,M>&
Vector<D,T,M>::operator<<( const Matrix<T>& mat )
{
    initialise( mat.r() );
    eig() = mat.eig();

    return *this;
}

// Vector = STD
TPL_DTM Vector<D,T,M>&
Vector<D,T,M>::operator=( const Seq<D>& seq )
{
    if( fits( seq ) )
    {
        #pragma omp parallel for
        forLOOPi( n() ) at(i) = seq[i];
    }
    else *this << seq;

    return *this;
}

// Vector << STD
TPL_DTM Vector<D,T,M>&
Vector<D,T,M>::operator<<( const Seq<D>& seq )
{
    initialise( seq.size() );

    #pragma omp parallel for
    forLOOPi( n() ) at(i) = seq[i];

    return *this = seq;
}

#ifdef OPENCV_FOUND

// Vector = KPts
TPL_DTM Vector<D,T,M>&
Vector<D,T,M>::operator=( const KPts& kpt )
{
    if( fits( kpt ) )
    {
        #pragma omp parallel for
        forLOOPi( n() ) at(i) = kpt[i].pt;
    }
    else *this << kpt;

    return *this;
}

// Vector << KPts
TPL_DTM Vector<D,T,M>&
Vector<D,T,M>::operator<<( const KPts& kpt )
{
    initialise( kpt.size() );

    #pragma omp parallel for
    forLOOPi( n() ) at(i) = kpt[i].pt;

    return *this = kpt;
}

#endif

// Vector = Element
TPL_DTM Vector<D,T,M>&
Vector<D,T,M>::operator=( const D& elm )
{
    return setVal( elm );
}

}
