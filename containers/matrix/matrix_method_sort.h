#include "../matrix.h"

namespace cvpp
{

// Sort (NEW)
TPL_T inline Matrix<T>
Matrix<T>::sort() const
{
    return clone().Sort();
}

// Sort (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::Sort()
{
    std::sort( eig_data() , eig_data() + s() );
    return *this;
}

// Sort (NEW)
TPL_T inline Matrix<T>
Matrix<T>::sort( const int& n ) const
{
    return clone().Sort( n );
}

// Sort (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::Sort( const int& n )
{
    std::nth_element( eig_data() , eig_data() + n , eig_data() + s() );
    return *this;
}

// Sort Rows (NEW)
TPL_T inline Matrix<T>
Matrix<T>::sortRows() const
{
    Matrix<T> tmp = clone();

    #pragma omp parallel for
    for( unsigned i = 0 ; i < c() ; i++ )
    {   for( unsigned j = 0 ; j < r() ; j++ )
        {   for( unsigned k = j ; k < r() ; k++ )
            {
                if( tmp(k,i) < tmp(j,i) )
                {
                    double v = tmp(j,i);
                    tmp(j,i) = tmp(k,i);
                    tmp(k,i) = v;
                }
            }
        }
    }

    return tmp;
}

// Sort Cols (NEW)
TPL_T inline Matrix<T>
Matrix<T>::sortCols() const
{
    Matrix<T> tmp = clone();

    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
    {   for( unsigned j = 0 ; j < c() ; j++ )
        {   for( unsigned k = j ; k < c() ; k++ )
            {
                if( tmp(i,k) < tmp(i,j) )
                {
                    double v = tmp(i,j);
                    tmp(i,j) = tmp(i,k);
                    tmp(i,k) = v;
                }
            }
        }
    }

    return tmp;
}

// Sort Rows (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::SortRows()
{
    #pragma omp parallel for
    for( unsigned i = 0 ; i < c() ; i++ )
    {   for( unsigned j = 0 ; j < r() ; j++ )
        {   for( unsigned k = j ; k < r() ; k++ )
            {
                if( at(k,i) < at(j,i) )
                {
                    double v = at(j,i);
                    at(j,i) = at(k,i);
                    at(k,i) = v;
                }
            }
        }
    }

    return *this;
}

// Sort Cols (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::SortCols()
{
    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
    {   for( unsigned j = 0 ; j < c() ; j++ )
        {   for( unsigned k = j ; k < c() ; k++ )
            {
                if( at(i,k) < at(i,j) )
                {
                    double v = at(i,j);
                    at(i,j) = at(i,k);
                    at(i,k) = v;
                }
            }
        }
    }

    return *this;
}

// Sort Rows IDX (NEW)
TPL_T inline Matrix<int>
Matrix<T>::sortRowsIDX() const
{
    Matrix<int> idx( dims() );

    Matrix<T> tmp = clone();
    Matrix<T> max = maxRows() + 1.0;

    #pragma omp parallel for
    for( unsigned i = 0 ; i < c() ; i++ )
    {   for( unsigned j = 0 ; j < r() ; j++ )
        {
            double v = max(i);
            for( unsigned k = 0 ; k < r() ; k++ )
                if( tmp(k,i) < v )
                    v = tmp(k,i) , idx(j,i) = k;
            tmp(idx(j,i),i) = max(i);
        }
    }

    return idx;
}

// Sort Cols IDX (NEW)
TPL_T inline Matrix<int>
Matrix<T>::sortColsIDX() const
{
    Matrix<int> idx( dims() );

    Matrix<T> tmp = clone();
    Matrix<T> max = maxRows() + 1.0;

    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
    {   for( unsigned j = 0 ; j < c() ; j++ )
        {
            double v = max(i);
            for( unsigned k = 0 ; k < c() ; k++ )
                if( tmp(i,k) < v )
                    v = tmp(i,k) , idx(i,j) = k;
            tmp(i,idx(i,j)) = max(i);
        }
    }

    return idx;
}

}
