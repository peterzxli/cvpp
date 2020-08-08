#include "../sparse.h"

namespace cvpp
{

// Backslash (NEW)
TPL_T Matrix<T>
Sparse<T>::bslash( const Matrix<T>& mat ) const
{
    Eigen::SimplicialLLT< Eigen::SparseMatrix<T> > solver;
    solver.compute( eig() );

    Matrix<T> tmp( mat.dims() );
    tmp.eig() = solver.solve( mat.eig() );

    return tmp;
}

// Backslash (SELF)
TPL_T void
Sparse<T>::bslash( Matrix<T>* mat ) const
{
    Eigen::SimplicialLLT< Eigen::SparseMatrix<T> > solver;
    solver.compute( eig() );

    mat->eig() = solver.solve( mat->eig() );
}

// Chol Backslash (NEW)
TPL_T Matrix<T>
Sparse<T>::cbslash( const Matrix<T>& mat ) const
{
    Matrix<T> tmp( mat.dims() );
    tmp.eig() = eig().template triangularView< Eigen::Lower >().solve( mat.eig() );
    return tmp;
}

// Chol Backslash (SELF)
TPL_T void
Sparse<T>::cbslash( Matrix<T>* mat ) const
{
    mat->eig() = eig().template triangularView< Eigen::Lower >().solve( mat->eig() );
}

}
