#include "../matrix.h"

namespace cvpp
{

// Closest Rows LBL
TPL_T Matrix<int>
Matrix<T>::closestRowsLBL( const Matrix<T>& mat ) const
{
    Matrix<int> lbl( r() );

    #pragma omp parallel for
    forLOOPi( r() )
    {
        T dist , min_dist = PINF;
        forLOOPj( mat.r() )
        {
            dist = ( row(i) - mat.row(j) ).squaredNorm();

            if( dist < min_dist )
                min_dist = dist , lbl[i] = j;
        }
    }

    return lbl;
}

// Closest Rows DST
TPL_T Matrix<T>
Matrix<T>::closestRowsDST( const Matrix<T>& mat ) const
{
    Matrix<T> dst( r() );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < r() ; i++ )
    {
        T dist; dst[i] = PINF;
        for( unsigned j = 0 ; j < mat.r() ; j++ )
        {
            dist = 0;
            for( unsigned k = 0 ; k < c() ; k++ )
                dist += std::pow( at(i,k) - mat(j,k) , 2 );

            if( dist < dst[i] )
                dst[i] = dist;
        }
    }

    return dst;
}

// Merge Clusters (NEW)
TPL_T inline unsigned
Matrix<T>::mergeClusters( Matrix<T>& ctr , Matrix<int>& lbl , const int& n ) const
{
    for( unsigned i = 0 ; i < ctr.r() ; i++ )
    {   if( sampleRows( lbl , i ).r() < n )
        {
            for( unsigned j = i ; j < ctr.r() ; j++ )
                ctr.row(j) = ctr.row(j+1);
            ctr.RemRows(1);

            for( unsigned j = 0 ; j < r() ; j++ )
            {
                if( lbl[j] == i ) lbl[j] = r(j).closest( ctr )[0];
                else if( lbl[j] > i ) lbl[j]--;
            }

            i--;
        }
    }

    #pragma omp parallel for
    for( unsigned i = 0 ; i < ctr.r() ; i++ )
        ctr.r(i) = sampleRows( lbl , i ).meanRows();

    return ctr.r();
}

// Remove Clusters (SELF)
TPL_T inline unsigned
Matrix<T>::RemoveClusters( Matrix<T>& ctr , Matrix<int>& lbl , const int& n )
{
    unsigned k = r() - 1;
    forLOOPi( ctr.r() )
    {   if( sampleRows( lbl , i ).r() < n )
        {
            for( unsigned j = i ; j < ctr.r() ; j++ )
                ctr.row(j) = ctr.row(j+1);
            ctr.RemRows(1);

            for( unsigned j = 0 ; j < k + 1 ; j++ )
            {   if( lbl[j] == i )
                {
                    while( lbl[k] == i || lbl[k] == -1 ) k--;
                    lbl[j] = lbl[k]; r(j) = r(k); lbl[k] = -1;
                }
            }

            for( unsigned j = 0 ; j < k ; j++ )
                if( lbl[j] > i ) lbl[j]--;

            i--;
        }
    }

    lbl.KeepU( k );
    this->KeepU( k );

    return ctr.r();
}

// Remove Clusters IDX
TPL_T inline Matrix<int>
Matrix<T>::removeClustersIDX( Matrix<T>& ctr , Matrix<int>& lbl , const int& n ) const
{
    Matrix<int> flag( ctr.r() );
    flag.setVal(1);

    #pragma omp parallel for
    forLOOPi( ctr.r() )
        if( sampleRows( lbl , i ).r() < n )
            flag[i] = 0;

    Matrix<int> idx( r() );

    unsigned ii = 0;
    forLOOPi( r() )
    {   if( flag[ lbl[i] ] == 1 )
        {
            lbl[ii] = lbl[i];
            idx[ii++] = i;
        }
    }
    idx.KeepU( ii );
    lbl.KeepU( ii );

    forLOOPi( ctr.r() )
    {   if( flag[i] == 0 )
        {
            for( unsigned j = i ; j < ctr.r() ; j++ )
            {
                ctr.row(j) = ctr.row(j+1);
                flag.row(j) = flag.row(j+1);
            }

            forLOOPj( lbl.r() )
                if( lbl[j] > i ) lbl[j]--;

            ctr.RemRows(1);
            i--;
        }
    }

    return idx;
}

}
