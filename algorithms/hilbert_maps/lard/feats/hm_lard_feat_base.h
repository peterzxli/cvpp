#ifndef HM_LARD_FEATURE_H
#define HM_LARD_FEATURE_H

#include <cvpp/auxiliar/macros.h>
#include <cvpp/auxiliar/timer.h>

#include <cvpp/containers/matrix.h>
#include <cvpp/containers/sparse.h>

#include <cvpp/algorithms/kdtree/kdtree.h>

namespace cvpp
{

class HMfeatBase
{

public:

    double rad,thr;
    unsigned ndims;

public:

    HMfeatBase()
    {
        ndims = 0;
    }

    HMfeatBase( const double& r ) : HMfeatBase()
    {
        rad = r;
    }

    HMfeatBase( const double& r , const double& t ) : HMfeatBase( r )
    {
        thr = t;
    }

    virtual double kernel( const Matd& , const Matd& , const Matd& ) const {}
    virtual double kernel( const REIG<double>& , const REIG<double>& , const Matd& ) const {}

    Sprd compute( const Matd& X , const KDtreed& kdtree , const SeqMatd& covs ) const
    {
        SSeqi idx ; SSeqd dst ;
        kdtree.knnSearch( X , rad , idx , dst );

        unsigned k , nnz = 0;
        forLOOPi( idx.size() ) nnz += idx[i].size();

        TriListd list;
        list.reserve( nnz );

        forLOOPi( X.r() )
        {
            forLOOPj( idx[i].size() )
            {
                k = idx[i][j];
                list.push_back( Trid( i , k ,
                                kernel( X.row(i) , kdtree.edata(k) , covs[k] ) ) );
            }
        }

        return Sprd( X.r() , ndims , list );
    }

};

}

#endif
