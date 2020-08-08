#include "../matrix.h"

namespace cvpp
{

// ********************************************************** VALUE

// Matrix + Value
TPL_TU inline Matrix<T>
operator+( const Matrix<T>& mat , const U& val )
{
    return mat.clone() += val;
}

// Value + Matrix
TPL_TU inline Matrix<T>
operator+( const U& val , const Matrix<T>& mat )
{
    return mat.clone() += val;
}

// Matrix - Value
TPL_TU inline Matrix<T>
operator-( const Matrix<T>& mat , const U& val )
{
    return mat.clone() -= val;
}

// Value - Matrix
TPL_TU inline Matrix<T>
operator-( const U& val , const Matrix<T>& mat )
{
    return mat.clone().mlt( -1.0 ) += val;
}

// Matrix * Value
TPL_TU inline Matrix<T>
operator*( const Matrix<T>& mat , const U& val )
{
    return mat.clone() *= val;
}

// Value * Matrix
TPL_TU inline Matrix<T>
operator*( const U& val , const Matrix<T>& mat )
{
    return mat.clone() *= val;
}

// Matrix / Value
TPL_TU inline Matrix<T>
operator/( const Matrix<T>& mat , const U& val )
{
    return mat.clone() /= val;
}

// Value / Matrix
TPL_TU inline Matrix<T>
operator/( const U& val , const Matrix<T>& mat )
{
    return mat.clone().Denom() *= val;
}

// ********************************************************** SEIGEN

// Matrix + SEigen
TPL_T inline Matrix<T>
operator+( const Matrix<T>& mat , const SEigen& seig )
{
    return mat.clone() += seig;
}

// Matrix - SEigen
TPL_T inline Matrix<T>
operator-( const Matrix<T>& mat , const SEigen& seig )
{
    return mat.clone() -= seig;
}

// Matrix * SEigen
TPL_T inline Matrix<T>
operator*( const Matrix<T>& mat , const SEigen& seig )
{
    Matrix<T> tmp( mat.r() , seig.cols() );
    tmp.eig().noalias() = mat.eig() * seig;
    return tmp;
}

// Matrix % SEigen
TPL_T inline Matrix<T>
operator%( const Matrix<T>& mat , const SEigen& seig )
{
    return mat.clone() %= seig;
}

// Matrix / SEigen
TPL_T inline Matrix<T>
operator/( const Matrix<T>& mat , const SEigen& seig )
{
    return mat.clone() /= seig;
}

// ********************************************************** FEIGEN

// Matrix + FEigen
TPL_TF inline Matrix<T>
operator+( const Matrix<T>& mat , const FEigen& feig )
{
    return mat.clone() += feig;
}

// Matrix - FEigen
TPL_TF inline Matrix<T>
operator-( const Matrix<T>& mat , const FEigen& feig )
{
    return mat.clone() -= feig;
}

// Matrix * FEigen
TPL_TF inline Matrix<T>
operator*( const Matrix<T>& mat , const FEigen& feig )
{
    Matrix<T> tmp( mat.r() , feig.cols() );
    tmp.eig().noalias() = mat.eig() * feig;
    return tmp;
}

// Matrix % FEigen
TPL_TF inline Matrix<T>
operator%( const Matrix<T>& mat , const FEigen& feig )
{
    return mat.clone() %= feig;
}

// Matrix / FEigen
TPL_TF inline Matrix<T>
operator/( const Matrix<T>& mat , const FEigen& feig )
{
    return mat.clone() /= feig;
}

// ********************************************************** MATRIX

// Matrix + Matrix
TPL_T inline Matrix<T>
operator+( const Matrix<T>& mat1 , const Matrix<T>& mat2 )
{
    return mat1.clone() += mat2;
}

// Matrix - Matrix
TPL_T inline Matrix<T>
operator-( const Matrix<T>& mat1 , const Matrix<T>& mat2 )
{
    return mat1.clone() -= mat2;
}

// Matrix * Matrix
TPL_T inline Matrix<T>
operator*( const Matrix<T>& mat1 , const Matrix<T>& mat2 )
{
    Matrix<T> tmp( mat1.r() , mat2.c() );
    tmp.eig().noalias() = mat1.eig() * mat2.eig();
    return tmp;
}

// Matrix % Matrix
TPL_T inline Matrix<T>
operator%( const Matrix<T>& mat1 , const Matrix<T>& mat2 )
{
    return mat1.clone() %= mat2;
}

// Matrix / Matrix
TPL_T inline Matrix<T>
operator/( const Matrix<T>& mat1 , const Matrix<T>& mat2 )
{
    return mat1.clone() /= mat2;
}

// ********************************************************** SPARSE

// Matrix + Sparse
TPL_T inline Matrix<T>
operator+( const Matrix<T>& mat , const Sparse<T>& spr )
{
    return mat.clone() += spr;
}

// Matrix - Sparse
TPL_T inline Matrix<T>
operator-( const Matrix<T>& mat , const Sparse<T>& spr )
{
    return mat.clone() -= spr;
}

// Matrix * Sparse
TPL_T inline Matrix<T>
operator*( const Matrix<T>& mat , const Sparse<T>& spr )
{
    Matrix<T> tmp( mat.r() , spr.c() );
    tmp.eig() = mat.eig() * spr.eig();
    return tmp;
}

// Matrix % Sparse
TPL_T inline Matrix<T>
operator%( const Matrix<T>& mat , const Sparse<T>& spr )
{
    return mat.clone() %= spr;
}

// Matrix / Sparse
TPL_T inline Matrix<T>
operator/( const Matrix<T>& mat , const Sparse<T>& spr )
{
    return mat.clone() /= spr;
}

}

