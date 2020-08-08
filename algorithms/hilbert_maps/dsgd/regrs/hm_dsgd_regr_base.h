#ifndef HM_DSGD_REGRESSOR_BASE_H
#define HM_DSGD_REGRESSOR_BASE_H

#include <cvpp/auxiliar/macros.h>
#include <cvpp/auxiliar/timer.h>

#include <cvpp/containers/matrix.h>
#include <cvpp/containers/sparse.h>

#include <cvpp/algorithms/kdtree/kdtree.h>
#include <cvpp/algorithms/random_kitchen_sinks/rks_feat_base.h>

namespace cvpp
{

class HMregrBase
{

protected:

    RKSfeatBase* feat;

    Matd Xtr , Ytr , Xbt , I ;
    Matd trainY , wgt ;

    int k , d , n , b , f , ff , r , t , nf , tb , nwgt , iters ;
    double ls , reg , step0 , step1 ;

public:

    HMregrBase()
    {
    }

    ~HMregrBase()
    {
        delete feat;
    }

    const Matd& weights() const { return wgt; }
    const void setFeature( RKSfeatBase* feat ) { this->feat = feat; }

    const void setData( const Matd& X , const Matd& Y )
    {
        Xtr = X ; Ytr = Y ;

        trainY = Ytr.lblMat() ;
        k = trainY.c() , t = Xtr.r() , d = Xtr.c() ;
    }

    const void setParams( const double& p1 , const double& p2 , const double& p3 , const double& p4 ,
                          const unsigned& p5 , const unsigned& p6 , const unsigned& p7 )
    {
        Matd distmat = Xtr.sr( 10 ).vecDistRows();
        double med = distmat.median();

        r = 1 ; ls = 1.0 / pow( p1 * med , 2.0 ) ;
        reg = p2 , step0 = p3 , step1 = p4 , n = p5 , f = p6 , b = p7 ;
        ff = f / feat->mlt();

        nf = std::floor( n / f ) , tb = std::floor( t / b );
        iters = std::max( nf , tb );

        wgt = MatZEROSd( n , k );
        I = MatIDTYd( f , reg + 1e-7 );
    }

    virtual const void train() {}
    virtual Matd query( const Matd& , int = -1 ) const {}

};

}

#endif



