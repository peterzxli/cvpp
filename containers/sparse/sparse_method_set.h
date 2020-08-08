#include "../sparse.h"

namespace cvpp
{

// Set from Triplets
TPL_T inline Sparse<T>&
Sparse<T>::set( const TripletList<T>& list )
{
    eig().setFromTriplets( list.begin() , list.end() );
    return *this;
}

// Set Value
TPL_T inline Sparse<T>&
Sparse<T>::setVal( double n , const T& val )
{
    if( n < 1 ) n *= s();

    Matrix<int> idx( s() );
    idx.setIncrease().ShuffleRows().KeepU( n );

    TripletList<T> list;
    list.reserve( n );

    forLOOPk( n )
        list.push_back( Triplet<T>( idx[k] / c() , idx[k] % c() , val ) );

    return set( list );
}

// Set Increase
TPL_T inline Sparse<T>&
Sparse<T>::setIncrease( double n , const T& start , const T& step )
{
    if( n < 1 ) n *= s();

    Matrix<int> idx( s() );
    idx.setIncrease().ShuffleRows().KeepU( n );

    TripletList<T> list;
    list.reserve( n );

    forLOOPk( n )
        list.push_back( Triplet<T>( idx[k] / c() , idx[k] % c() , start + (T)k * step ) );

    return set( list );
}

// Set Random
TPL_T inline Sparse<T>&
Sparse<T>::setRand( double n , const T& min , const T& max )
{
    if( n < 1 ) n *= s();

    Matrix<int> idx( s() );
    idx.setIncrease().ShuffleRows().KeepU( n );

    TripletList<T> list;
    list.reserve( n );

    forLOOPk( n )
        list.push_back( Triplet<T>( idx[k] / c() , idx[k] % c() , randd( min , max ) ) );

    return set( list );
}

// Set Random
TPL_T inline Sparse<T>&
Sparse<T>::setRandRows( double n , const T& min , const T& max )
{
    if( n < 1 ) n *= r();

    TripletList<T> list;
    list.reserve( n * c() );

    forLOOPi( r() )
    {
        Matrix<int> idx( c() );
        idx.setIncrease().ShuffleRows().KeepU( n );

        forLOOPk( n )
            list.push_back( Triplet<T>( i , idx[k] , randd( min , max ) ) );
    }

    return set( list );
}

// Set Random
TPL_T inline Sparse<T>&
Sparse<T>::setRandCols( double n , const T& min , const T& max )
{
    if( n < 1 ) n *= c();

    TripletList<T> list;
    list.reserve( n * r() );

    forLOOPi( c() )
    {
        Matrix<int> idx( r() );
        idx.setIncrease().ShuffleRows().KeepU( n );

        forLOOPk( n )
            list.push_back( Triplet<T>( idx[k] , i , randd( min , max ) ) );
    }

    return set( list );
}

}
