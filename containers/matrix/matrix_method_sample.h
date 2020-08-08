#include "../matrix.h"

namespace cvpp
{

// Sample Rows (NEW)
TPL_T inline Matrix<T>
Matrix<T>::sampleRows( int st , const int& jmp ) const
{
    Matrix<T> tmp;
    if( st < 0 ) st += r();

    if( jmp > 0 )
         tmp.reset( std::ceil(   (double)( r() - st ) / (double)jmp ) , c() );
    else tmp.reset( std::ceil( - (double)(  st + 1  ) / (double)jmp ) , c() );

    int cnt = 0;
    for( int i = st ; i >= 0 && i < r() ; i += jmp )
        tmp.row( cnt++ ) = row( i );
    return tmp;
}

// Sample Rows (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::SampleRows( int st , const int& jmp )
{
    return *this = sampleRows( st , jmp );
}

// Sample Cols (NEW)
TPL_T inline Matrix<T>
Matrix<T>::sampleCols( int st , const int& jmp ) const
{
    Matrix<T> tmp;
    if( st < 0 ) st += c();

    if( jmp > 0 )
         tmp.reset( r() , std::ceil(   (double)( c() - st ) / (double)jmp ) );
    else tmp.reset( r() , std::ceil( - (double)(  st + 1  ) / (double)jmp ) );

    int cnt = 0;
    for( int i = st ; i >= 0 && i < c() ; i += jmp )
        tmp.col( cnt++ ) = col( i );
    return tmp;
}

// Sample Cols (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::SampleCols( int st , const int& jmp )
{
    return *this = sampleCols( st , jmp );
}

// Sample Rows (NEW)
TPL_T inline Matrix<T>
Matrix<T>::sampleRows( const int& st , const int& ntv , const int& jmp ) const
{
    Matrix<T> tmp( std::ceil( (double)( jmp * ( r() - st ) ) / (double)ntv ) , c() );

    int cnt = 0;
    for( int i = st ; i < r() ; i += ntv )
        for( int j = 0 ; j < jmp && i + j < r() ; j++ )
            tmp.row( cnt++ ) = row( i + j );
    return tmp;
}

// Sample Rows (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::SampleRows( const int& st , const int& ntv , const int& jmp )
{
    int cnt = 0;
    for( int i = st ; i < r() ; i += ntv )
        for( int j = 0 ; j < jmp && i + j < r() ; j++ )
            row( cnt++ ) = row( i + j );
    KeepU( cnt ); return *this;
}

// Sample Cols (NEW)
TPL_T inline Matrix<T>
Matrix<T>::sampleCols( const int& st , const int& ntv , const int& jmp ) const
{
    Matrix<T> tmp( r() , std::ceil( (double)( jmp * ( c() - st ) ) / (double)ntv ) );

    int cnt = 0;
    for( int i = st ; i < c() ; i += ntv )
        for( int j = 0 ; j < jmp && i + j < c() ; j++ )
            tmp.col( cnt++ ) = col( i + j );
    return tmp;
}

// Sample Cols (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::SampleCols( const int& st , const int& ntv , const int& jmp )
{
    int cnt = 0;
    for( int i = st ; i < c() ; i += ntv )
        for( int j = 0 ; j < jmp && i + j < c() ; j++ )
            col( cnt++ ) = col( i + j );
    KeepL( cnt ); return *this;
}

// Sample Rows (NEW)
TPL_T inline Matrix<T>
Matrix<T>::sampleRows( const Matrix<int>& idx ) const
{
    Matrix<T> tmp( idx.r() , c() );

    #pragma omp parallel for
    forLOOPi( tmp.r() ) tmp.row( i ) = row( idx[i] );
    return tmp;
}

// Sample Cols (NEW)
TPL_T inline Matrix<T>
Matrix<T>::sampleCols( const Matrix<int>& idx ) const
{
    Matrix<T> tmp( r() , idx.r() );

    #pragma omp parallel for
    forLOOPi( tmp.c() ) tmp.col( i ) = col( idx[i] );
    return tmp;
}

// Sample Rows (NEW)
TPL_T inline Matrix<T>
Matrix<T>::sampleRows( const Matrix<int>& lbl , const int& n ) const
{
    Matrix<T> tmp( lbl.r() , c() );

    int cnt = 0;
    forLOOPi( lbl.r() )
        if( lbl[i] == n ) tmp.row( cnt++ ) = row( i );
    tmp.KeepU( cnt );
    return tmp;
}

// Sample Cols (NEW)
TPL_T inline Matrix<T>
Matrix<T>::sampleCols( const Matrix<int>& lbl , const int& n ) const
{
    Matrix<T> tmp( r() , lbl.r() );

    int cnt = 0;
    forLOOPi( lbl.r() )
        if( lbl[i] == n ) tmp.col( cnt++ ) = col( i );
    tmp.KeepL( cnt );
    return tmp;
}

// Sample Rand Rows (NEW)
TPL_T inline Matrix<T>
Matrix<T>::sampleRandRows( const int& n ) const
{
    Matrix<int> idx( r() );
    idx.setIncrease().ShuffleRows();
    return sampleRows( idx.r( 0 , n ) );
}

// Sample Rand Cols (NEW)
TPL_T inline Matrix<T>
Matrix<T>::sampleRandCols( const int& n ) const
{
    Matrix<int> idx( c() );
    idx.setIncrease().ShuffleRows();
    return sampleCols( idx.r( 0 , n ) );
}

// Sample Rand Rows (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::SampleRandRows( const int& n )
{
    Matrix<int> idx( r() );
    idx.setIncrease().ShuffleRows();
    return SampleRows( idx.r( 0 , n ) );
}

// Sample Rand Cols (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::SampleRandCols( const int& n )
{
    Matrix<int> idx( c() );
    idx.setIncrease().ShuffleRows();
    return SampleCols( idx.r( 0 , n ) );
}

// Unique Rows (NEW)
TPL_T inline Matrix<T>
Matrix<T>::uniqueRows() const
{
    Matrix<T> tmp( dims() );
    tmp.row(0) = row(0);

    int n = 1;
    forLOOPii( 1 , r() )
    {
        bool flag = true;
        forLOOPk( n )
        {
            int m = 0;
            forLOOPj( c() )
                m += ( at(i,j) == tmp.at(k,j) );

            if( m == c() )
            {
                flag = false;
                break;
            }
        }

        if( flag )
            tmp.row(n++) = row(i);
    }
    tmp.KeepU(n);

    return tmp;
}

// Unique Cols (NEW)
TPL_T inline Matrix<T>
Matrix<T>::uniqueCols() const
{
    Matrix<T> tmp( dims() );
    tmp.c(0) = c(0);

    int n = 1;
    for( int i = 1 ; i < c() ; i++ )
    {
        bool flag = true;
        forLOOPk( n )
        {
            int m = 0;
            forLOOPj( r() )
                m += ( at(j,i) == tmp.at(j,k) );

            if( m == r() )
            {
                flag = false;
                break;
            }
        }

        if( flag )
            tmp.c(n++) = c(i);
    }
    tmp.KeepL(n);

    return tmp;
}

}
