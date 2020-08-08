#include "../matrix.h"

namespace cvpp
{

// Value & Matrix
TPL_TU inline Matrix<T>
operator&( const U& val , const Matrix<T>& mat )
{
    Matrix<T> tmp = mat.appL( 1 );
    tmp.cl(1).setVal(val);
    return tmp;
}

// Matrix & Value
TPL_TU inline Matrix<T>
operator&( const Matrix<T>& mat , const U& val )
{
    Matrix<T> tmp = mat.appR( 1 );
    tmp.cr(1).setVal(val);
    return tmp;
}

// Value | Matrix
TPL_TU inline Matrix<T>
operator|( const U& val , const Matrix<T>& mat )
{
    Matrix<T> tmp = mat.appU( 1 );
    tmp.ru(1).setVal(val);
    return tmp;
}

// Matrix | Value
TPL_TU inline Matrix<T>
operator|( const Matrix<T>& mat , const U& val )
{
    Matrix<T> tmp = mat.appD( 1 );
    tmp.rd(1).setVal(val);
    return tmp;
}

// Matrix & Matrix
TPL_T inline Matrix<T>
operator&( const Matrix<T>& mat1 , const Matrix<T>& mat2 )
{
    if( mat1.r() > mat2.r() )
        return mat1.appR( mat2.repRows( mat1.r() / mat2.r() ) );
    if( mat1.r() < mat2.r() )
        return mat2.appL( mat1.repRows( mat2.r() / mat1.r() ) );
    return mat1.appR( mat2 );
}

// Matrix | Matrix
TPL_T inline Matrix<T>
operator|( const Matrix<T>& mat1 , const Matrix<T>& mat2 )
{
    if( mat1.c() > mat2.c() )
        return mat1.appD( mat2.repCols( mat1.c() / mat2.c() ) );
    if( mat1.c() < mat2.c() )
        return mat2.appU( mat1.repCols( mat2.c() / mat1.c() ) );
    return mat1.appD( mat2 );
}

}
