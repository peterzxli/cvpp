#ifndef HM_REAL_FEATURE_SQEXP_H
#define HM_REAL_FEATURE_SQEXP_H

#include "./hm_real_feat_base.h"

#define LN12 1.442695041

namespace cvpp
{

class HMfeatSqExp : public HMfeatBase
{

protected:

public:

    HMfeatSqExp() : HMfeatBase() {}

    inline double kernel( const EIG<double>& d , const Matd& S ) const
    {
        return std::exp( - ( d * S.eig() * d.transpose() )(0) );
//        return std::pow( 2.0 , - ( d * S.eig() * d.transpose() )(0) * LN12 );
    }

};

}

#endif
