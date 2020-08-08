#include "../matrix.h"

namespace cvpp
{

// Reshape
TPL_T Matrix<T>
Matrix<T>::reshape( const int& r , const int& c ) const
{
    Matrix<T> tmp( r , c );

    unsigned a = 0 , b = 0 ;
    for( unsigned i = 0 ; i < r ; i++ )
    {   for( unsigned j = 0 ; j < c ; j++ )
        {
            tmp(i,j) = at(a,b++);
            if( b == this->c() )
                b = 0 , a++;
        }
    }

    return tmp;
}

// Label Matrix
TPL_T Matrix<T>
Matrix<T>::lblMat() const
{
    Matrix<T> tmp( r() , uniqueRows().r() );
    tmp.setVal(0);

    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
        tmp( i , at(i) ) = 1;

    return tmp;
}

// Coord Matrix
TPL_T Matrix<int>
Matrix<T>::coord() const
{
    Matrix<int> tmp( s() , 2 );

    int cnt = 0;
    forLOOPij( r() , c() )
        tmp.row(cnt++) << i , j ;

    return tmp;
}


}
