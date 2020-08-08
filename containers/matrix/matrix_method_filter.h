#include "../matrix.h"

namespace cvpp
{

// Filter Rows IDX (NEW)
TPL_T inline Matrix<int>
Matrix<T>::filterRowsIDX( const Matrix<T>& lim ) const
{
    Matrix<int> mat( r() );

    unsigned cnt = 0;
    for( unsigned i = 0 ; i < r() ; i++ )
    {
        bool flag = true;
        for( unsigned j = 0 ; j < c() && flag ; j++ )
            if( at(i,j) < lim(0,j) || at(i,j) > lim(1,j) )
                flag = false;
        if( flag ) mat(cnt++) = i;
    }

    mat.KeepU( cnt );
    return mat;
}

// Filter Cols IDX (NEW)
TPL_T inline Matrix<int>
Matrix<T>::filterColsIDX( const Matrix<T>& lim ) const
{
    Matrix<int> mat( c() );

    unsigned cnt = 0;
    for( unsigned i = 0 ; i < c() ; i++ )
    {
        bool flag = true;
        for( unsigned j = 0 ; j < r() && flag ; j++ )
            if( at(j,i) < lim(j,0) || at(j,i) > lim(j,1) )
                flag = false;
        if( flag ) mat(cnt++) = i;
    }

    mat.KeepU( cnt );
    return mat;
}

}
