#include "../matrix.h"

namespace cvpp
{

// Cholesky (NEW)
TPL_T Matrix<T>
Matrix<T>::chol() const
{
    Matrix<T> tmp( dims() );
    tmp.eig() = eig().llt().matrixL();
    return tmp;
}

// Rank 1 Update (SELF)
TPL_T Matrix<T>&
Matrix<T>::Rank1update( const Matrix<T>& x )
{
    int n = x.r();
    forLOOPk( n )
    {
        double r = std::sqrt( std::pow( at(k,k) , 2.0 )
                            + std::pow(  x(k)   , 2.0 ) );

        double c =  r   / at(k,k);
        double s = x(k) / at(k,k);

        at(k,k) = r;

        if( k < n - 1 )
        {
            int i = k + 1 , j = n - i;

            Matd A =   b(i,k,j,1);
            Matd B = x.rd(j);

            A = ( A + s * B ) / c;
            B = c * B - s * A;
        }
    }

    return *this;
}

// Chol Delete Cross (SELF)
TPL_T Matrix<T>&
Matrix<T>::DelCrossChol( const int& k )
{
    int i = k + 1 , j = r() - i;
    brd(j).Rank1update( b(i,k,j,1) );
    return DelCross( k );
}

}
