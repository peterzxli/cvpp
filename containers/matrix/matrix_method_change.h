#include "../matrix.h"

namespace cvpp
{

// Diagonal (New)
TPL_T Matrix<T>
Matrix<T>::diagonal() const
{
    Matrix<T> tmp;

    if( r() == 1 || c() == 1 )
    {
        tmp.reset( r() * c() , r() * c() ); tmp.setVal(0);
        tmp.eig() = eig().asDiagonal();
    }
    else
    {
        tmp.reset( r() , 1 );
        tmp.eig() = eig().diagonal();
    }

    return tmp;
}

// Add Jitter (NEW)
TPL_T inline Matrix<T>
Matrix<T>::addJitter( const T& jit ) const
{
    Matrix<T> tmp = clone();

    if( r() == 1 || c() == 1 )
        tmp += jit;
    else
    {
        #pragma omp parallel for
        for( unsigned i = 0 ; i < r() ; i++ )
            tmp(i,i) += jit;
    }

    return tmp;
}

// Add Jitter (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::AddJitter( const T& jit )
{
    if( r() == 1 || c() == 1 )
        *this += jit;
    else
    {
        #pragma omp parallel for
        for( unsigned i = 0 ; i < r() ; i++ )
            at(i,i) += jit;
    }

    return *this;
}

// Replace (NEW)
TPL_T inline Matrix<T>
Matrix<T>::replace( const T& v1 , const T& v2 ) const
{
    Matrix<T> tmp( dims() );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            tmp(i,j) = ( at(i,j) == v1 ? v2 : at(i,j) );
    return tmp;
}

// Replace (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::Replace( const T& v1 , const T& v2 )
{
    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            if( at(i,j) == v1 ) at(i,j) = v2;
    return *this;
}

// Flip Rows (NEW)
TPL_T inline Matrix<T>
Matrix<T>::flipRows() const
{
    Matrix<T> tmp( dims() );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        tmp.row(i) = row( r() - i - 1 );

    return tmp;
}

// Flip Rows (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::FlipRows()
{
    Matrix<T> tmp = clone();

    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        row(i) = tmp.row( r() - i - 1 );

    return *this;
}

// Flip Cols (NEW)
TPL_T inline Matrix<T>
Matrix<T>::flipCols() const
{
    Matrix<T> tmp( dims() );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < c() ; i++ )
        tmp.col(i) = col( c() - i - 1 );

    return tmp;
}

// Flip Cols (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::FlipCols()
{
    Matrix<T> tmp = clone();

    #pragma omp parallel for
    for( unsigned i = 0 ; i < c() ; i++ )
        col(i) = tmp.col( c() - i - 1 );

    return *this;
}

// Reverse Bit Order Rows (NEW)
TPL_T inline Matrix<T>
Matrix<T>::rboRows() const
{
    Matrix<T> tmp( dims() );

    #pragma omp parallel for
    forLOOPi( r() )
        tmp.row(i) = row( rbo( r() , i ) );

    return tmp;
}

// Reverse Bit Order Rows (NEW)
TPL_T inline Matrix<T>
Matrix<T>::rboCols() const
{
    Matrix<T> tmp( dims() );

    #pragma omp parallel for
    forLOOPi( c() )
        tmp.col(i) = col( rbo( c() , i ) );

    return tmp;
}

// Floor (NEW)
TPL_T Matrix<T>
Matrix<T>::floor() const
{
    Matrix<T> tmp( dims() );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            tmp(i,j) = std::floor( at(i,j) );
    return tmp;
}

// Round (NEW)
TPL_T Matrix<T>
Matrix<T>::round() const
{
    Matrix<T> tmp( dims() );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            tmp(i,j) = std::round( at(i,j) );
    return tmp;
}

// Ceil (NEW)
TPL_T Matrix<T>
Matrix<T>::ceil() const
{
    Matrix<T> tmp( dims() );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            tmp(i,j) = std::ceil( at(i,j) );
    return tmp;
}

// Floor (SELF)
TPL_T Matrix<T>&
Matrix<T>::Floor()
{
    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            at(i,j) = std::floor( at(i,j) );
    return *this;
}

// Round (SELF)
TPL_T Matrix<T>&
Matrix<T>::Round()
{
    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            at(i,j) = std::round( at(i,j) );
    return *this;
}

// Ceil (SELF)
TPL_T Matrix<T>&
Matrix<T>::Ceil()
{
    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            at(i,j) = std::ceil( at(i,j) );
    return *this;
}

// Floor (NEW)
TPL_T Matrix<T>
Matrix<T>::floor( const T& val ) const
{
    Matrix<T> tmp( dims() );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            tmp(i,j) = ( at(i,j) < val ? val : at(i,j) );
    return tmp;
}

// Ceil (NEW)
TPL_T Matrix<T>
Matrix<T>::ceil( const T& val ) const
{
    Matrix<T> tmp( dims() );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            tmp(i,j) = ( at(i,j) > val ? val : at(i,j) );
    return tmp;
}

// Floor (SELF)
TPL_T Matrix<T>&
Matrix<T>::Floor( const T& val )
{
    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            if( at(i,j) < val ) at(i,j) = val;
    return *this;
}

// Ceil (SELF)
TPL_T Matrix<T>&
Matrix<T>::Ceil( const T& val )
{
    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            if( at(i,j) > val ) at(i,j) = val;
    return *this;
}

// Limits (NEW)
TPL_T Matrix<T>
Matrix<T>::limits( const T& min , const T& max ) const
{
    Matrix<T> tmp( dims() );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            tmp(i,j) = ( at(i,j) < min ? min : ( at(i,j) > max ? max : at(i,j) ) );
    return tmp;
}

// Limits (SELF)
TPL_T Matrix<T>&
Matrix<T>::Limits( const T& min , const T& max )
{
    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
                 if( at(i,j) < min ) at(i,j) = min;
            else if( at(i,j) > max ) at(i,j) = max;
    return *this;
}

// Min (NEW)
TPL_T inline Matrix<T>
Matrix<T>::min( const Matrix<T>& mat ) const
{
    Matrix<T> tmp( dims() );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            tmp(i,j) = std::min( at(i,j) , mat(i,j) );

    return tmp;
}

// Max (NEW)
TPL_T inline Matrix<T>
Matrix<T>::max( const Matrix<T>& mat ) const
{
    Matrix<T> tmp( dims() );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            tmp(i,j) = std::max( at(i,j) , mat(i,j) );

    return tmp;
}

// Lim (NEW)
TPL_T inline Matrix<T>
Matrix<T>::lim( const Matrix<T>& mat ) const
{
    Matrix<T> tmp( dims() );

    tmp.r(0) = r(0).min( mat.r(0) );
    tmp.r(1) = r(1).max( mat.r(1) );

    return tmp;
}

// Min (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::Min( const Matrix<T>& mat )
{
    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            if( at(i,j) > mat(i,j) ) at(i,j) = mat(i,j);

    return *this;
}

// Max (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::Max( const Matrix<T>& mat )
{
    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            if( at(i,j) < mat(i,j) ) at(i,j) = mat(i,j);

    return *this;
}

// Lim (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::Lim( const Matrix<T>& mat )
{
    r(0).Min( mat.r(0) );
    r(1).Max( mat.r(1) );

    return *this;
}

// Mod (NEW)
TPL_T inline Matrix<T>
Matrix<T>::mod( const T& val ) const
{
    Matrix<T> tmp( dims() );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            tmp(i,j) = at(i,j) % val;

    return tmp;
}

// Mod (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::Mod( const T& val )
{
    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = 0 ; j < c() ; j++ )
            at(i,j) = at(i,j) % val;

    return *this;
}

TPL_T Matrix<T>
Matrix<T>::gridDouble2D() const
{
    if( c() == 1 )
    {
        return gridDoubleCol2D();
    }
    if( c() == 2 )
    {
        Matrix<T> c0 = c(0).gridDoubleCol2D();
        Matrix<T> c1 = c(1).gridDoubleCol2D();
        return c0 & c1;
    }
}

TPL_T Matrix<T>
Matrix<T>::gridDoubleCol2D() const
{
    int s = std::sqrt( r() );
    Matd mat = reshape( s , s );

    Matrix<T> nmat( 2 * s - 1 , 2 * s - 1 );
    forLOOPij( mat.r() , mat.c() )
        nmat( 2 * i , 2 * j ) = mat(i,j);

    forLOOPi( mat.r() - 1 )
        nmat.row( 2 * i + 1 ) = ( nmat.row( 2 * i ) + nmat.row( 2 * i + 2 ) ) / 2.0;
    forLOOPi( mat.r() - 1 )
        nmat.col( 2 * i + 1 ) = ( nmat.col( 2 * i ) + nmat.col( 2 * i + 2 ) ) / 2.0;

    forLOOPij( mat.r() - 1 , mat.c() - 1 )
    {
        int u = 2 * i + 1 , v = 2 * j + 1 ;
        nmat( u , v ) = ( nmat( u + 1 , v ) + nmat( u - 1 , v ) +
                          nmat( u , v + 1 ) + nmat( u , v - 1 ) ) / 4.0;
    }

    return nmat.toCol();
}

}
