#include "../matrix.h"

namespace cvpp
{

// Separate Rows (NEW)
TPL_T inline Seq<Matrix<T>>
Matrix<T>::separateRows( const Matrix<int>& lbl ) const
{
    Seq<Matrix<T>>& pts( lbl.max() - lbl.min() + 1 );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < pts.size() ; i++ )
        pts[i] = sampleRows( lbl , i );
    return pts;
}

// Separate Rows (NEW)
TPL_T inline Seq<Matrix<T>>
Matrix<T>::separateCols( const Matrix<int>& lbl ) const
{
    Seq<Matrix<T>>& pts( lbl.max() - lbl.min() + 1 );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < pts.size() ; i++ )
        pts[i] = sampleCols( lbl , i );
    return pts;
}

// Split Rows (New)
TPL_T inline Seq<Matrix<T>>
Matrix<T>::splitRows( const Matrix<int>& idx , const int& n ) const
{
    Seq<Matrix<T>> tmp( splitSize( r() , n ) , c() );

    #pragma omp parallel for
    forLOOPi( r() / n ) tmp[i] = sampleRows( idx.r( n * i , n ) );

    return tmp;
}

// Split Cols (New)
TPL_T inline Seq<Matrix<T>>
Matrix<T>::splitCols( const Matrix<int>& idx , const int& n ) const
{
    Seq<Matrix<T>> tmp( r() , splitSize( c() , n ) );

    #pragma omp parallel for
    forLOOPi( c() / n ) tmp[i] = sampleCols( idx.r( n * i , n ) );

    return tmp;
}

}
