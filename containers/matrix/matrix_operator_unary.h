#include "../matrix.h"

namespace cvpp
{

// ********************************************************** SELF

// + Matrix
TPL_T Matrix<T>
Matrix<T>::operator+() const
{
    return clone();
}

// - Matrix
TPL_T Matrix<T>
Matrix<T>::operator-() const
{
    return clone().mlt( -1.0 );
}

// ********************************************************** SEIGEN

// Matrix += SEigen
TPL_T inline Matrix<T>&
Matrix<T>::operator+=( const SEigen& seig )
{
    eig() += seig;
    return *this;
}

// Matrix -= SEigen
TPL_T inline Matrix<T>&
Matrix<T>::operator-=( const SEigen& seig )
{
    eig() -= seig;
    return *this;
}

// Matrix *= SEigen
TPL_T inline Matrix<T>&
Matrix<T>::operator*=( const SEigen& seig )
{
    eig() *= seig;
    return *this;
}

// Matrix %= SEigen
TPL_T inline Matrix<T>&
Matrix<T>::operator%=( const SEigen& seig )
{
    Matrix<T> tmp( dims() );
    tmp.setVal(0);

    #pragma omp parallel for
    forLOOPseig( seig ) tmp( it.row() , it.col() ) = at( it.row() , it.col() ) * it.valueRef();

    eig() = tmp.eig();
    return *this;
}

// Matrix /= SEigen
TPL_T inline Matrix<T>&
Matrix<T>::operator/=( const SEigen& seig )
{
    Matrix<T> tmp( dims() );
    tmp.setVal(0);

    #pragma omp parallel for
    forLOOPseig( seig ) tmp( it.row() , it.col() ) = at( it.row() , it.col() ) / it.valueRef();

    eig() = tmp.eig();
    return *this;
}

// ********************************************************** FEIGEN

// Matrix += FEigen
TPL_T TPL_F inline Matrix<T>&
Matrix<T>::operator+=( const FEigen& feig )
{
    if( fits( feig ) )
         eig() += feig;
    else eig() += feig.replicate( r() / feig.rows() ,
                                  c() / feig.cols() );
    return *this;
}

// Matrix -= FEigen
TPL_T TPL_F inline Matrix<T>&
Matrix<T>::operator-=( const FEigen& feig )
{
    if( fits( feig ) )
         eig() -= feig;
    else eig() -= feig.replicate( r() / feig.rows() ,
                                  c() / feig.cols() );
    return *this;
}

// Matrix *= FEigen
TPL_T TPL_F inline Matrix<T>&
Matrix<T>::operator*=( const FEigen& feig )
{
    if( fits( feig ) )
         eig() *= feig;
    else *this = *this * feig;

    return *this;
}

// Matrix %= FEigen
TPL_T TPL_F inline Matrix<T>&
Matrix<T>::operator%=( const FEigen& feig )
{
    if( fits( feig ) )
         eig().array() *= feig.array();
    else eig().array() *= feig.replicate( r() / feig.rows() ,
                                          c() / feig.cols() ).array();
    return *this;
}

// Matrix /= FEigen
TPL_T TPL_F inline Matrix<T>&
Matrix<T>::operator/=( const FEigen& feig )
{
    if( fits( feig ) )
         eig().array() /= feig.array();
    else eig().array() /= feig.replicate( r() / feig.rows() ,
                                          c() / feig.cols() ).array();
    return *this;
}

// ********************************************************** BEIGEN

// Matrix += BEigen
TPL_T TPL_B inline Matrix<T>&
Matrix<T>::operator+=( const BEigen beig )
{
    if( fits( beig ) )
         eig() += beig;
    else eig() += beig.replicate( r() / beig.rows() ,
                                  c() / beig.cols() );
    return *this;
}

// Matrix -= BEigen
TPL_T TPL_B inline Matrix<T>&
Matrix<T>::operator-=( const BEigen beig )
{
    if( fits( beig ) )
         eig() -= beig;
    else eig() -= beig.replicate( r() / beig.rows() ,
                                  c() / beig.cols() );
    return *this;
}

// Matrix *= BEigen
TPL_T TPL_B inline Matrix<T>&
Matrix<T>::operator*=( const BEigen beig )
{
    if( fits( beig ) )
         eig() *= beig;
    else *this = *this * beig;

    return *this;
}

// Matrix %= BEigen
TPL_T TPL_B inline Matrix<T>&
Matrix<T>::operator%=( const BEigen beig )
{
    if( fits( beig ) )
         eig().array() *= beig.array();
    else eig().array() *= beig.replicate( r() / beig.rows() ,
                                          c() / beig.cols() ).array();
    return *this;
}

// Matrix /= BEigen
TPL_T TPL_B inline Matrix<T>&
Matrix<T>::operator/=( const BEigen beig )
{
    if( fits( beig ) )
         eig().array() /= beig.array();
    else eig().array() /= beig.replicate( r() / beig.rows() ,
                                          c() / beig.cols() ).array();
    return *this;
}

// ********************************************************** MATRIX

// Matrix += Matrix
TPL_T inline Matrix<T>&
Matrix<T>::operator+=( const Matrix<T>& mat )
{
    if( fits( mat ) )
         eig() += mat.eig();
    else eig() += mat.eig().replicate( r() / mat.r() ,
                                       c() / mat.c() );
    return *this;
}

// Matrix -= Matrix
TPL_T inline Matrix<T>&
Matrix<T>::operator-=( const Matrix<T>& mat )
{
    if( fits( mat ) )
         eig() -= mat.eig();
    else eig() -= mat.eig().replicate( r() / mat.r() ,
                                       c() / mat.c() );
    return *this;
}

// Matrix *= Matrix
TPL_T inline Matrix<T>&
Matrix<T>::operator*=( const Matrix<T>& mat )
{
    if( fits( mat ) )
         eig() *= mat.eig();
    else *this = *this * mat;

    return *this;
}

// Matrix %= Matrix
TPL_T inline Matrix<T>&
Matrix<T>::operator%=( const Matrix<T>& mat )
{
    if( fits( mat ) )
         eig().array() *= mat.eig().array();
    else eig().array() *= mat.eig().replicate( r() / mat.r() ,
                                               c() / mat.c() ).array();
    return *this;
}

// Matrix /= Matrix
TPL_T inline Matrix<T>&
Matrix<T>::operator/=( const Matrix<T>& mat )
{
    if( fits( mat ) )
         eig().array() /= mat.eig().array();
    else eig().array() /= mat.eig().replicate( r() / mat.r() ,
                                               c() / mat.c() ).array();
    return *this;
}

// ********************************************************** SPARSE

// Matrix += Sparse
TPL_T inline Matrix<T>&
Matrix<T>::operator+=( const Sparse<T>& spr )
{
    eig() += spr.eig();
    return *this;
}

// Matrix -= Sparse
TPL_T inline Matrix<T>&
Matrix<T>::operator-=( const Sparse<T>& spr )
{
    eig() -= spr.eig();
    return *this;
}

// Matrix *= Sparse
TPL_T inline Matrix<T>&
Matrix<T>::operator*=( const Sparse<T>& spr )
{
    if( fits( spr ) )
         eig() *= spr.eig();
    else *this = *this * spr;

    return *this;
}

// Matrix %= Sparse
TPL_T inline Matrix<T>&
Matrix<T>::operator%=( const Sparse<T>& spr )
{
    Matrix<T> tmp( dims() );
    tmp.setVal(0);

    #pragma omp parallel for
    forLOOPspr( spr ) tmp( it.row() , it.col() ) = at( it.row() , it.col() ) * it.valueRef();

    eig() = tmp.eig();
    return *this;
}

// Matrix /= Sparse
TPL_T inline Matrix<T>&
Matrix<T>::operator/=( const Sparse<T>& spr )
{
    Matrix<T> tmp( dims() );
    tmp.setVal(0);

    #pragma omp parallel for
    forLOOPspr( spr ) tmp( it.row() , it.col() ) = at( it.row() , it.col() ) / it.valueRef();

    eig() = tmp.eig();
    return *this;
}


}
