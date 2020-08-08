#include "../sparse.h"

namespace cvpp
{

// ********************************************************** SELF

// + Sparse
TPL_T Sparse<T>
Sparse<T>::operator+()
{
    return clone();
}

// - Sparse
TPL_T Sparse<T>
Sparse<T>::operator-()
{
    return clone().mlt( -1.0 );
}

// ********************************************************** VALUE

// Sparse += Value
TPL_T TPL_U inline Sparse<T>&
Sparse<T>::operator+=( const U& val )
{
    #pragma omp parallel for
    forLOOPsprp it.valueRef() += val;
    return *this;
}

// Sparse -= Value
TPL_T TPL_U inline Sparse<T>&
Sparse<T>::operator-=( const U& val )
{
    #pragma omp parallel for
    forLOOPsprp it.valueRef() -= val;
    return *this;
}

// Sparse *= Value
TPL_T TPL_U inline Sparse<T>&
Sparse<T>::operator*=( const U& val )
{
    #pragma omp parallel for
    forLOOPsprp it.valueRef() *= val;
    return *this;
}

// Sparse /= Value
TPL_T TPL_U inline Sparse<T>&
Sparse<T>::operator/=( const U& val )
{
    #pragma omp parallel for
    forLOOPsprp it.valueRef() /= val;
    return *this;
}

// ********************************************************** SEIGEN

// Sparse += SEigen
TPL_T inline Sparse<T>&
Sparse<T>::operator+=( const SEigen& seig )
{
    eig() += seig; return *this;
}

// Sparse -= SEigen
TPL_T inline Sparse<T>&
Sparse<T>::operator-=( const SEigen& seig )
{
    eig() -= seig; eig().prune(0,0); return *this;
}

// Sparse *= SEigen
TPL_T inline Sparse<T>&
Sparse<T>::operator*=( const SEigen& seig )
{
    eig() = eig() * seig;
    return *this;
}

// Sparse %= SEigen
TPL_T inline Sparse<T>&
Sparse<T>::operator%=( const SEigen& seig )
{
    eig() = eig().cwiseProduct( seig );
    return *this;
}

// Sparse /= SEigen
TPL_T inline Sparse<T>&
Sparse<T>::operator/=( const SEigen& seig )
{
    eig() = eig().cwiseQuotient( seig );
    return *this;
}

// ********************************************************** FEIGEN

// Sparse += FEigen
TPL_T TPL_F inline Sparse<T>&
Sparse<T>::operator+=( const FEigen& feig )
{
    eig() += feig.sparseView();
    eig().prune(0,0);
    return *this;
}

// Sparse -= FEigen
TPL_T TPL_F inline Sparse<T>&
Sparse<T>::operator-=( const FEigen& feig )
{
    eig() -= feig.sparseView();
    eig().prune(0,0);
    return *this;
}

// Sparse *= FEigen
TPL_T TPL_F inline Sparse<T>&
Sparse<T>::operator*=( const FEigen& feig )
{
    eig() = ( eig() * feig ).sparseView();
    return *this;
}

// Sparse %= FEigen
TPL_T TPL_F inline Sparse<T>&
Sparse<T>::operator%=( const FEigen& feig )
{
    #pragma omp parallel for
    forLOOPsprp it.valueRef() *= feig( it.row() , it.col() );
    return *this;
}

// Sparse /= FEigen
TPL_T TPL_F inline Sparse<T>&
Sparse<T>::operator/=( const FEigen& feig )
{
    #pragma omp parallel for
    forLOOPsprp it.valueRef() /= feig( it.row() , it.col() );
    return *this;
}

// ********************************************************** BEIGEN

// Sparse += BEigen
TPL_T TPL_B inline Sparse<T>&
Sparse<T>::operator+=( const BEigen beig )
{
    eig() += beig.sparseView();
    eig().prune(0,0);
    return *this;
}

// Sparse -= BEigen
TPL_T TPL_B inline Sparse<T>&
Sparse<T>::operator-=( const BEigen beig )
{
    eig() -= beig.sparseView();
    eig().prune(0,0);
    return *this;
}

// Sparse *= BEigen
TPL_T TPL_B inline Sparse<T>&
Sparse<T>::operator*=( const BEigen beig )
{
    eig() = ( eig() * beig ).sparseView();
    return *this;
}

// Sparse %= BEigen
TPL_T TPL_B inline Sparse<T>&
Sparse<T>::operator%=( const BEigen beig )
{
    #pragma omp parallel for
    forLOOPsprp it.valueRef() *= beig( it.row() , it.col() );
    return *this;
}

// Sparse /= BEigen
TPL_T TPL_B inline Sparse<T>&
Sparse<T>::operator/=( const BEigen beig )
{
    #pragma omp parallel for
    forLOOPsprp it.valueRef() /= beig( it.row() , it.col() );
    return *this;
}

// ********************************************************** SPARSE

// Sparse += Sparse
TPL_T inline Sparse<T>&
Sparse<T>::operator+=( const Sparse<T>& spr )
{
    eig() += spr.eig();
    return *this;
}

// Sparse -= Sparse
TPL_T inline Sparse<T>&
Sparse<T>::operator-=( const Sparse<T>& spr )
{
    eig() -= spr.eig();
    return *this;
}

// Sparse *= Sparse
TPL_T inline Sparse<T>&
Sparse<T>::operator*=( const Sparse<T>& spr )
{
    eig() = eig() * spr.eig();
    return *this;
}

// Sparse %= Sparse
TPL_T inline Sparse<T>&
Sparse<T>::operator%=( const Sparse<T>& spr )
{
    eig() = eig().cwiseProduct( spr.eig() );
    return *this;
}

// Sparse /= Sparse
TPL_T inline Sparse<T>&
Sparse<T>::operator/=( const Sparse<T>& spr )
{
    eig() = eig().cwiseQuotient( spr.eig() );
    return *this;
}

// ********************************************************** MATRIX

// Sparse += Matrix
TPL_T inline Sparse<T>&
Sparse<T>::operator+=( const Matrix<T>& mat )
{
    Sparse<T> tmp = mat.clone();
    eig() += tmp.eig(); return *this;
}

// Sparse -= Matrix
TPL_T inline Sparse<T>&
Sparse<T>::operator-=( const Matrix<T>& mat )
{
    Sparse<T> tmp = mat.clone();
    eig() -= tmp.eig(); return *this;
}

// Sparse *= Matrix
TPL_T inline Sparse<T>&
Sparse<T>::operator*=( const Matrix<T>& mat )
{
    Sparse<T> tmp = mat.clone();
    eig() = eig() * tmp.eig(); return *this;
}

// Sparse %= Matrix
TPL_T inline Sparse<T>&
Sparse<T>::operator%=( const Matrix<T>& mat )
{
    #pragma omp parallel for
    forLOOPsprp it.valueRef() *= mat( it.row() , it.col() );
    return *this;
}

// Sparse /= Matrix
TPL_T inline Sparse<T>&
Sparse<T>::operator/=( const Matrix<T>& mat )
{
    #pragma omp parallel for
    forLOOPsprp it.valueRef() /= mat( it.row() , it.col() );
    return *this;
}

}
