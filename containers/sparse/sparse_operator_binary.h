#include "../sparse.h"

namespace cvpp
{

// ********************************************************** VALUE

// Sparse + Value
TPL_TU inline Sparse<T>
operator+( const Sparse<T>& spr , const U& val )
{
    return spr.clone() += val;
}

// Value + Sparse
TPL_TU inline Sparse<T>
operator+( const U& val , const Sparse<T>& spr )
{
    return spr.clone() += val;
}

// Sparse - Value
TPL_TU inline Sparse<T>
operator-( const Sparse<T>& spr , const U& val )
{
    return spr.clone() -= val;
}

// Value - Sparse
TPL_TU inline Sparse<T>
operator-( const U& val , const Sparse<T>& spr )
{
    return spr.clone().mlt( -1.0 ) += val;
}

// Sparse * Value
TPL_TU inline Sparse<T>
operator*( const Sparse<T>& spr , const U& val )
{
    return spr.clone() *= val;
}

// Value * Sparse
TPL_TU inline Sparse<T>
operator*( const U& val , const Sparse<T>& spr )
{
    return spr.clone() *= val;
}

// Sparse / Value
TPL_TU inline Sparse<T>
operator/( const Sparse<T>& spr , const U& val )
{
    return spr.clone() /= val;
}

// Value / Sparse
TPL_TU inline Sparse<T>
operator/( const U& val , const Sparse<T>& spr )
{
    Sparse<T> tmp = spr.clone();
    tmp.eig() = tmp.eig().cwiseInverse();
    tmp *= val; return tmp;
}

// ********************************************************** SPARSE

// Sparse + Sparse
TPL_T inline Sparse<T>
operator+( const Sparse<T>& spr1 , const Sparse<T>& spr2 )
{
    return spr1.clone() += spr2;
}

// Sparse - Sparse
TPL_T inline Sparse<T>
operator-( const Sparse<T>& spr1 , const Sparse<T>& spr2 )
{
    return spr1.clone() -= spr2;
}

// Sparse * Sparse
TPL_T inline Sparse<T>
operator*( const Sparse<T>& spr1 , const Sparse<T>& spr2 )
{
    Sparse<T> tmp( spr1.r() , spr2.c() );
    tmp.eig() = spr1.eig() * spr2.eig();
    return tmp;
}

// Sparse % Sparse
TPL_T inline Sparse<T>
operator%( const Sparse<T>& spr1 , const Sparse<T>& spr2 )
{
    return spr1.clone() %= spr2;
}

// Sparse / Sparse
TPL_T inline Sparse<T>
operator/( const Sparse<T>& spr1 , const Sparse<T>& spr2 )
{
    return spr1.clone() /= spr2;
}

// ********************************************************** MATRIX

// Sparse + Matrix
TPL_T inline Sparse<T>
operator+( const Sparse<T>& spr , const Matrix<T>& mat )
{
    return spr.clone() += mat;
}

// Sparse - Matrix
TPL_T inline Sparse<T>
operator-( const Sparse<T>& spr , const Matrix<T>& mat )
{
    return spr.clone() -= mat;
}

// Sparse * Matrix
TPL_T inline Sparse<T>
operator*( const Sparse<T>& spr , const Matrix<T>& mat )
{
    Matrix<T> tmp( spr.r() , mat.c() );
    tmp.eig() = spr.eig() * mat.eig();
    return tmp;
}

// Sparse % Matrix
TPL_T inline Sparse<T>
operator%( const Sparse<T>& spr , const Matrix<T>& mat )
{
    return spr.clone() %= mat;
}

// Sparse / Matrix
TPL_T inline Sparse<T>
operator/( const Sparse<T>& spr , const Matrix<T>& mat )
{
    return spr.clone() /= mat;
}

}
