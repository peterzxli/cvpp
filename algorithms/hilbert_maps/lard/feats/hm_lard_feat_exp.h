#ifndef HM_LARD_FEATURE_EXP_H
#define HM_LARD_FEATURE_EXP_H

#include "./hm_lard_feat_base.h"

namespace cvpp
{

TPL_T
class HMfeatExp : public HMfeatBase<T>
{

protected:

public:

    HMfeatExp( const T& rad ) : HMfeatBase<T>( rad ) {}

    T kernel( const Matrix<T>& x1 , const Matrix<T>& x2 , const Matrix<T>& S ) const
    {
        EIG<T> d = x1.eig() - x2.eig();
        return std::exp( - std::sqrt( ( d * S.eig() * d.transpose() )(0) ) );
    }

};

using FeatureExpf = FeatureExp<float>;
using FeatureExpd = FeatureExp<double>;

}

#endif
