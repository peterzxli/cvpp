#ifndef HM_SHAPE_FEATURE_SQEXP_H
#define HM_SHAPE_FEATURE_SQEXP_H

#include "./hm_shape_feat_base.h"

namespace cvpp
{

class HMfeatSqExp : public HMfeatBase
{

protected:

public:

    HMfeatSqExp( const double& rad ) : HMfeatBase( rad ) {}

    double kernel( const REIG<double>& x1 , const REIG<double>& x2 ,
                   const Matd& S ) const
    {
        Eigd d = x1 - x2;
        return std::exp( - ( d * S.eig() * d.transpose() )(0) );
    }

};

}

#endif
