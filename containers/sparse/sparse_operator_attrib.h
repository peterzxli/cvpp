#include "../sparse.h"

namespace cvpp
{

// Sparse >> Sparse
TPL_T Sparse<T>&
Sparse<T>::operator>>( const Sparse<T>& spr )
{
    this->eig_ptr = spr.eig_ptr;

    return *this;
}

// Sparse = Sparse
TPL_T Sparse<T>&
Sparse<T>::operator=( const Sparse<T>& spr )
{
    if( fits( spr ) )
        this->eig() = spr.eig();
    else *this << spr;

    return *this;
}

// Sparse << Sparse
TPL_T inline Sparse<T>&
Sparse<T>::operator<<( const Sparse<T>& spr )
{
    this->initialise( spr.dims() );
    this->eig() = spr.eig();

    return *this;
}

// Sparse = Matrix
TPL_T inline Sparse<T>&
Sparse<T>::operator=( const Matrix<T>& mat )
{
    if( fits( mat ) )
        this->eig() = mat.eig().sparseView();
    else *this << mat;

    return *this;
}

// Sparse << Matrix
TPL_T inline Sparse<T>&
Sparse<T>::operator<<( const Matrix<T>& mat )
{
    this->initialise( mat.dims() );
    this->eig() = mat.eig().sparseView();

    return *this;
}

// Sparse = SEigen
TPL_T Sparse<T>&
Sparse<T>::operator=( const SEigen& seig )
{
    if( fits( seig ) )
        this->eig() = seig;
    else *this << seig;

    return *this;
}

// Sparse << SEigen
TPL_T inline Sparse<T>&
Sparse<T>::operator<<( const SEigen& seig )
{
    this->initialise( seig.rows() , seig.cols() );
    this->eig() = seig;

    return *this;
}

// Sparse = FEigen
TPL_T TPL_F Sparse<T>&
Sparse<T>::operator=( const FEigen& feig )
{
    if( fits( feig ) )
        this->eig() = feig.sparseView();
    else *this << feig;

    return *this;
}

// Sparse << FEIGen
TPL_T TPL_F inline Sparse<T>&
Sparse<T>::operator<<( const FEigen& feig )
{
    this->initialise( feig.rows() , feig.cols() );
    this->eig() = feig.sparseView();

    return *this;
}

// Sparse = BEigen
TPL_T TPL_B Sparse<T>&
Sparse<T>::operator=( const BEigen beig )
{
    if( fits( beig ) )
        this->eig() = beig.sparseView();
    else *this << beig;

    return *this;
}

// Sparse << BEIGen
TPL_T TPL_B inline Sparse<T>&
Sparse<T>::operator<<( const BEigen beig )
{
    this->initialise( beig.rows() , beig.cols() );
    this->eig() = beig.sparseView();

    return *this;
}

}
