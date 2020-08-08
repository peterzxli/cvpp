#ifndef CVPP_QUICK_MEANS_H
#define CVPP_QUICK_MEANS_H

#include <cvpp/containers/matrix.h>
#include <cvpp/algorithms/kdtree/kdtree.h>

namespace cvpp
{

TPL_T void
quick_means( const Matrix<T>& pts ,
             SeqMatrix<T>& clds , SeqMatrix<T>& means , SeqMatrix<T>& covs ,
             const double& ro , const double& ri , const int& thr )
{
    KDtree<T> kd( pts );
    Matrix<T> cloud , tmp( 1 , pts.c() );

    int ii , jj , t = pts.r();
    Mati I = MatINCRi( t ) , J = MatINCRi( t );
    Mati N = MatZEROSi( t );

    clds.reserve( t / 10 );

    SSeqi idxs; SSeq<T> dsts;
    while( t > 0 )
    {
        tmp.eig() = pts.row( I( randi( 0 , t ) ) );
        kd.radSearch( tmp , ro , idxs , dsts );

        if( idxs[0].size() > thr )
        {
            cloud.reset( idxs[0].size() , pts.c() );

            #pragma omp parallel for
            forLOOPi( cloud.r() ) cloud.row(i) = pts.row( idxs[0][i] );
            clds.push_back( cloud );
        }

        forLOOPi( idxs[0].size() )
        {
            ii = idxs[0][i];
            if( dsts[0][i] < ri )
            {
                jj = J( ii );
                if( !N( ii ) )
                {
                    N( ii ) = 1;
                    I( jj ) = I( --t );
                    J( t ) = J( I( jj ) ) = jj;
                }
            }
        }
    }

    means.resize( clds.size() );
    covs.resize( clds.size() );

    #pragma omp parallel for
    forLOOPi( clds.size() ) clds[i].mcovRows( means[i] , covs[i] );
}

TPL_T void
quick_means( const Matrix<T>& pts ,
             SeqMatrix<T>& clds , SeqMatrix<T>& means , SeqMatrix<T>& covs ,
             const double& ro , const double& ri , const int& out , const int& thr )
{
    KDtree<T> kd( pts );
    Matrix<T> cloud , tmp( 1 , pts.c() );

    int ii , jj , t = pts.r();
    Mati I = MatINCRi( t ) , J = MatINCRi( t );
    Mati N = MatZEROSi( t );

    double rm = double( out ) * ro;
    clds.reserve( t / 10 );

    SSeqi idxs( 1 ); SSeq<T> dsts( 1 );
    while( t > 0 )
    {
        tmp.eig() = pts.row( I( randi( 0 , t ) ) );

        double r = 0; idxs[0].clear();
        while( idxs[0].size() < thr && r < rm )
            kd.radSearch( tmp , r += ro , idxs , dsts );

        if( idxs[0].size() > thr )
        {
            cloud.reset( idxs[0].size() , pts.c() );

            #pragma omp parallel for
            forLOOPi( cloud.r() ) cloud.row(i) = pts.row( idxs[0][i] );
            clds.push_back( cloud );
        }

        forLOOPi( idxs[0].size() )
        {
            ii = idxs[0][i];
            if( dsts[0][i] < ri )
            {
                jj = J( ii );
                if( !N( ii ) )
                {
                    N( ii ) = 1;
                    I( jj ) = I( --t );
                    J( t ) = J( I( jj ) ) = jj;
                }
            }
        }
    }

    means.resize( clds.size() );
    covs.resize( clds.size() );

    #pragma omp parallel for
    forLOOPi( clds.size() ) clds[i].mcovRows( means[i] , covs[i] );
}

}

#endif
