#ifndef HM_ORGN_FEATURE_TRIANGLE_H
#define HM_ORGN_FEATURE_TRIANGLE_H

#include "./hm_orgn_feat_base.h"

namespace cvpp
{

class HMfeatTriangle : public HMfeatBase
{

protected:

public:

    double gamma;

public:

    HMfeatTriangle( const Matd& lim ,
                    const double& gam = 1.0 ,
                    const double& rad = 2.0 ,
                    const double& res = 0.5 )
    {
        limits = lim , gamma = gam , radius = rad , resolution = res ;

        dims = ( ( limits.r(1) - limits.r(0) ) / resolution ).floor();
        ndims = ( dims + 1.0 ).prod();
    }

    double kernel( const Matd& mat1 , const Matd& mat2 ) const
    {
        return std::max( 0.0 , gamma - ( mat1.eig() - mat2.eig() ).norm() ) / gamma ;
    }

};

}

#endif
