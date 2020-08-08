#include "../matrix.h"

namespace cvpp
{

// PDist Vec Rows (NEW)
TPL_T inline Matrix<T>
Matrix<T>::vecDistRows() const
{
    Matrix<T> tmp( r() * ( r() - 1 ) / 2 );

    unsigned cnt = 0;
    for( unsigned i = 0 ; i < r() ; i++ )
        for( unsigned j = i + 1 ; j < r() ; j++ )
            tmp(cnt++) = ( row(i) - row(j) ).squaredNorm();

    return tmp;
}

// PDist Vec Rows (NEW)
TPL_T inline Matrix<T>
Matrix<T>::matDistRows() const
{
    Matrix<T> tmp( r() , r() );
    tmp.setVal(0);

    for( unsigned i = 0 ; i < c() ; i++ )
        tmp += ( c(i).repCols( r() )
               - c(i).t().repRows( r() ) ).Square();

    return tmp;
}

}
