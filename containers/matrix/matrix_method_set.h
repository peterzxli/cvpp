#include "../matrix.h"

namespace cvpp
{

// Set Value
TPL_T Matrix<T>&
Matrix<T>::setVal( const T& val )
{
    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            at(i,j) = val;

    return *this;
}

// Set Increase
TPL_T Matrix<T>&
Matrix<T>::setIncrease( const T& start ,
                        const T& step )
{
    T cnt = 0;
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            at(i,j) = start + step * (T)cnt++;

    return *this;
}

// Set Random
TPL_T inline Matrix<T>&
Matrix<T>::setRand( const T& min , const T& max )
{
    Matrix<float> tmp( dims() );
    tmp.eig() = Eigen::Matrix<float,-1,-1>::Random( r() , c() );
    tmp.eig() = min + ( tmp.eig().array() + 1 ) / 2 * ( max - min );

    eig() = tmp.eig().cast<T>();
    return *this;
}

// Set Random Normal
TPL_T inline Matrix<T>&
Matrix<T>::setRandn( const T& m , const T& v )
{
    Matrix<float> tmp( dims() );

    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            tmp(i,j) = randnf( m , v );

    eig() = tmp.eig().cast<T>();
    return *this;
}

// Add Random (NEW)
TPL_T inline Matrix<T>
Matrix<T>::addRand( const T& min , const T& max ) const
{
    return clone().AddRand( min , max );
}

// Add Random (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::AddRand( const T& min , const T& max )
{
    Matrix<T> rnd( r() , c() );
    rnd.setRand( min , max );
    return *this += rnd;
}

// Add Random Normal (NEW)
TPL_T inline Matrix<T>
Matrix<T>::addRandn( const T& m , const T& v ) const
{
    return clone().AddRandn( m , v );
}

// Add Random Normal (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::AddRandn( const T& m , const T& v )
{
    Matrix<T> rnd( r() , c() );
    rnd.setRandn( m , v );
    return *this += rnd;
}

// Set Identity
TPL_T Matrix<T>&
Matrix<T>::setIdentity()
{
    eig().setIdentity();
    return *this;
}

}
