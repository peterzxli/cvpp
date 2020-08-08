#ifndef HM_LARD_FEATURE_SQEXP_H
#define HM_LARD_FEATURE_SQEXP_H

#include "./hm_lard_feat_base.h"

namespace cvpp
{

class HMfeatSqExp : public HMfeatBase
{

protected:

public:

    HMfeatSqExp( const double& rad ) : HMfeatBase( rad ) {}

    double kernel( const Matd& x1 , const Matd& x2 , const Matd& S ) const
    {
        Eigd d = x1.eig() - x2.eig();
        return std::exp( - ( d * S.eig() * d.transpose() )(0) );
    }

    double kernel( const REIG<double>& x1 , const REIG<double>& x2 ,
                   const Matd& S ) const
    {
        Eigd d = x1 - x2;
        return std::exp( - ( d * S.eig() * d.transpose() )(0) );
    }

};

}

#endif
