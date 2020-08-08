#include "../matrix.h"

namespace cvpp
{

// Remove Rows (NEW)
TPL_T inline Matrix<T>
Matrix<T>::removeRows( int st , const int& jmp ) const
{
    Matrix<T> tmp;
    if( st < 0 ) st += r();

    if( jmp > 0 )
         tmp.reset( r() - st - std::ceil(   (double)( r() - st ) / (double)jmp ) , c() );
    else tmp.reset(  1  + st - std::ceil( - (double)(  st + 1  ) / (double)jmp ) , c() );

    int cnt = 0;
    for( int i = st ; i >= 0 && i < r() ; i += sign( jmp ) )
        if( std::abs( i - st ) % std::abs( jmp ) > 0 )
            tmp.row( cnt++ ) = row( i );
    return tmp;
}

// Remove Rows (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::RemoveRows( int st , const int& jmp )
{
    return *this = removeRows( st , jmp );
}

// Remove Cols (NEW)
TPL_T inline Matrix<T>
Matrix<T>::removeCols( int st , const int& jmp ) const
{
    Matrix<T> tmp;
    if( st < 0 ) st += c();

    if( jmp > 0 )
         tmp.reset( r() , c() - st - std::ceil(   (double)( c() - st ) / (double)jmp ) );
    else tmp.reset( r() ,  1  + st - std::ceil( - (double)(  st + 1  ) / (double)jmp ) );

    int cnt = 0;
    for( int i = st ; i >= 0 && i < c() ; i += sign( jmp ) )
        if( std::abs( i - st ) % std::abs( jmp ) > 0 )
            tmp.col( cnt++ ) = col( i );
    return tmp;
}

// Remove Cols (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::RemoveCols( int st , const int& jmp )
{
    return *this = removeCols( st , jmp );
}

// Remove Rows (NEW)
TPL_T inline Matrix<T>
Matrix<T>::removeRows( const int& st , const int& ntv , int jmp ) const
{
    jmp = ntv - jmp;
    Matrix<T> tmp( std::floor( (double)( jmp * ( r() - st ) ) / (double)ntv ) , c() );

    int cnt = 0;
    for( int i = st ; i < r() ; i += ntv )
        for( int j = ntv - jmp ; j < ntv && i + j < r() ; j++ )
            tmp.row( cnt++ ) = row( i + j );
    return tmp;
}

// Remove Rows (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::RemoveRows( const int& st , const int& ntv , int jmp )
{
    jmp = ntv - jmp;

    int cnt = 0;
    for( int i = st ; i < r() ; i += ntv )
        for( int j = ntv - jmp ; j < ntv && i + j < r() ; j++ )
            row( cnt++ ) = row( i + j );
    return KeepU( cnt );
}

// Remove Cols (NEW)
TPL_T inline Matrix<T>
Matrix<T>::removeCols( const int& st , const int& ntv , int jmp ) const
{
    jmp = ntv - jmp;
    Matrix<T> tmp( r() , std::floor( (double)( jmp * ( c() - st ) ) / (double)ntv ) );

    int cnt = 0;
    for( int i = st ; i < c() ; i += ntv )
        for( int j = ntv - jmp ; j < ntv && i + j < c() ; j++ )
            tmp.col( cnt++ ) = col( i + j );
    return tmp;
}

// Remove Cols (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::RemoveCols( const int& st , const int& ntv , int jmp )
{
    jmp = ntv - jmp;

    int cnt = 0;
    for( int i = st ; i < c() ; i += ntv )
        for( int j = ntv - jmp ; j < ntv && i + j < c() ; j++ )
            col( cnt++ ) = col( i + j );
    return KeepL( cnt );
}

// Remove Rows (NEW)
TPL_T inline Matrix<T>
Matrix<T>::removeRows( const Matrix<int>& idx ) const
{
    Matrix<T> tmp( r() - idx.r() , c() );

    int cnt = 0;
    forLOOPi( r() )
    {
        bool flag = true;
        forLOOPj( idx.r() )
        {   if( idx[j] == i )
            { flag = false; break; }
        }; if( flag ) tmp.row(cnt++) = row(i);
    }
    return tmp;
}

// Remove Cols (NEW)
TPL_T inline Matrix<T>
Matrix<T>::removeCols( const Matrix<int>& idx ) const
{
    Matrix<T> tmp( r() , c() - idx.r() );

    int cnt = 0;
    forLOOPi( c() )
    {
        bool flag = true;
        forLOOPj( idx.c() )
        {   if( idx[j] == i )
            { flag = false; break; }
        }; if( flag ) tmp.col(cnt++) = col(i);
    }
    return tmp;
}

// Remove Rows (NEW)
TPL_T inline Matrix<T>
Matrix<T>::removeRows( const Matrix<int>& lbl , const int& n ) const
{
    Matrix<T> tmp( lbl.r() , c() );

    int cnt = 0;
    forLOOPi( lbl.r() )
        if( lbl[i] != n ) tmp.row( cnt++ ) = row( i );
    tmp.KeepU( cnt );
    return tmp;
}

// Remove Cols (NEW)
TPL_T inline Matrix<T>
Matrix<T>::removeCols( const Matrix<int>& lbl , const int& n ) const
{
    Matrix<T> tmp( r() , lbl.r() );

    int cnt = 0;
    forLOOPi( lbl.r() )
        if( lbl[i] != n ) tmp.col( cnt++ ) = col( i );
    tmp.KeepL( cnt );
    return tmp;
}

}
