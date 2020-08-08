#include "../matrix.h"

namespace cvpp
{

// Backslash (NEW)
TPL_T Matrix<T>
Matrix<T>::bslash() const
{
    Matrix<T> I( dims() );
    I.setIdentity(); return bslash( I );
}

// Backslash (NEW)
TPL_T Matrix<T>
Matrix<T>::bslash( const Matrix<T>& mat ) const
{
    Matrix<T> tmp( mat.dims() );
    tmp.eig() = eig().lu().solve( mat.eig() );
    return tmp;
}

// Backslash (SELF)
TPL_T Matrix<T>&
Matrix<T>::bslash( Matrix<T>* mat )
{
    mat->eig() = eig().lu().solve( mat->eig() );
    return *this;
}

// Double Backslash (NEW)
TPL_T Matrix<T>
Matrix<T>::dbslash() const
{
    Matrix<T> I( dims() );
    I.setIdentity(); return dbslash( I );
}

// Double Backslash (NEW)
TPL_T Matrix<T>
Matrix<T>::dbslash( const Matrix<T>& mat ) const
{
    Matrix<T> tmp = bslash( mat );
    t().bslash( &tmp ); return tmp;
}

// Double Backslash (SELF)
TPL_T Matrix<T>&
Matrix<T>::dbslash( Matrix<T>* mat )
{
    *mat = dbslash( *mat );
    return *this;
}

}
