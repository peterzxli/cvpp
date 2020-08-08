#include "../matrix.h"

namespace cvpp
{

// Smaller IDX (NEW)
TPL_T inline Matrix<int>
Matrix<T>::smallerIDX( const T& v ) const
{
    Matrix<int> idx( r() );

    unsigned cnt = 0;
    for( unsigned i = 0 ; i < r() ; i++ )
        if( at(i) < v ) idx[cnt++] = i;
    idx.KeepU( cnt );

    return idx;
}

// Smaller Equal IDX (NEW)
TPL_T inline Matrix<int>
Matrix<T>::eqsmallerIDX( const T& v ) const
{
    Matrix<int> idx( r() );

    unsigned cnt = 0;
    for( unsigned i = 0 ; i < r() ; i++ )
        if( at(i) <= v ) idx[cnt++] = i;
    idx.KeepU( cnt );

    return idx;
}

// Bigger IDX (NEW)
TPL_T inline Matrix<int>
Matrix<T>::biggerIDX( const T& v ) const
{
    Matrix<int> idx( r() );

    unsigned cnt = 0;
    for( unsigned i = 0 ; i < r() ; i++ )
        if( at(i) > v ) idx[cnt++] = i;
    idx.KeepU( cnt );

    return idx;
}

// Bigger Equal IDX (NEW)
TPL_T inline Matrix<int>
Matrix<T>::eqbiggerIDX( const T& v ) const
{
    Matrix<int> idx( r() );

    unsigned cnt = 0;
    for( unsigned i = 0 ; i < r() ; i++ )
        if( at(i) >= v ) idx[cnt++] = i;
    idx.KeepU( cnt );

    return idx;
}

// Equal IDX (NEW)
TPL_T inline Matrix<int>
Matrix<T>::equalIDX( const T& v ) const
{
    Matrix<int> idx( r() );

    unsigned cnt = 0;
    for( unsigned i = 0 ; i < r() ; i++ )
        if( at(i) == v ) idx[cnt++] = i;
    idx.KeepU( cnt );

    return idx;
}

// Equal IDX (NEW)
TPL_T inline Matrix<int>
Matrix<T>::equalIDX( const T& v , const T& e ) const
{
    Matrix<int> idx( r() );

    unsigned cnt = 0;
    for( unsigned i = 0 ; i < r() ; i++ )
        if( fabs( at(i) - v ) < e ) idx[cnt++] = i;
    idx.KeepU( cnt );

    return idx;
}

// Find Equal (NEW)
TPL_T TPL_U inline Matrix<int>
Matrix<T>::findEqual( const Matrix<U>& mat ) const
{
    Matrix<int> tmp( s() , 2 );

    unsigned cnt = 0;
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            if( at(i,j) == mat(i,j) )
                tmp.row(cnt++) << i , j ;
    tmp.KeepU( cnt );

    return tmp;
}

// Find Diff (NEW)
TPL_T TPL_U inline Matrix<int>
Matrix<T>::findDiff( const Matrix<U>& mat ) const
{
    Matrix<int> tmp( s() , 2 );

    unsigned cnt = 0;
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            if( at(i,j) != mat(i,j) )
                tmp.row(cnt++) << i , j ;
    tmp.KeepU( cnt );

    return tmp;
}

// Closest Grid
TPL_T inline Matrix<int>
Matrix<T>::gridClosest( const Matrix<T>& mat , const Matrix<T>& min ,
                        const Matrix<T>& res , const Matrix<int>& siz ) const
{
    Matrix<T> tmp = ( ( mat - min ) / res ).round();

    if( mat.c() == 2 )
        return ( tmp.c(0) * siz(1) + tmp.c(1) ).toInt();
    if( mat.c() == 3 )
        return ( tmp.c(0) * siz(2) * siz(1) + tmp.c(1) * siz(2) + tmp.c(2) ).toInt();
}

}
