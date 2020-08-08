#ifndef HM_SHAPE_FEATURE_RECT_H
#define HM_SHAPE_FEATURE_RECT_H

#include "./hm_shape_feat_base.h"

namespace cvpp
{

class HMfeatRect : public HMfeatBase
{

protected:

public:

    HMfeatRect( const double& rad ) : HMfeatBase( rad ) {}

    double kernel( const REIG<double>& x1 , const REIG<double>& x2 ,
                   const Eigd& S , const Eigd& iS , const Eigd& val , const Eigd& vec ,
                   const int& t ) const
    {
        Eigd d = x1 - x2;

        if( t == -1 )
        {
            return std::exp( - ( d * iS * d.transpose() )(0) );
        }

        Eigd dd = d * vec;
        double tt = ( t == 0 ? std::exp( - ( d * iS * d.transpose() )(0) ) : pow( t , 3.0 ) );

        double res;
        if( x1.cols() == 2 )
            res = d(0) * d(0) < S(0,0) &&
                  d(1) * d(1) < S(1,1) ? tt : 0.0 ;
//            res = dd(0) * dd(0) < val(0) &&
//                  dd(1) * dd(1) < val(1) ? tt : 0.0 ;
        else
            res = dd(0) * dd(0) < val(0) &&
                  dd(1) * dd(1) < val(1) &&
                  dd(2) * dd(2) < val(2) ? tt : 0.0 ;
        return res;
    }

};

}

#endif




//double res;
//if( x1.cols() == 2 )
////                res = dd(0) * dd(0) < val(0) &&
////                      dd(1) * dd(1) < val(1) ?
////                      std::exp( - ( d * iS * d.transpose() )(0) ) : 0.0 ;
//    res = d(0) * d(0) < S(0,0) &&
//          d(1) * d(1) < S(1,1) ?
//          std::exp( - ( d * iS * d.transpose() )(0) ) : 0.0 ;
//else

////                res = dd(0) * dd(0) < val(0) &&
////                      dd(1) * dd(1) < val(1) &&
////                      dd(2) * dd(2) < val(2) ?
////                      std::exp( - ( d * iS * d.transpose() )(0) ) : 0.0 ;

//    res = dd(0) * dd(0) < val(0) &&
//          dd(1) * dd(1) < val(1) &&
//          dd(2) * dd(2) < val(2) ? t : 0.0 ;

////                res = d(0) * d(0) < S(0,0) &&
////                      d(1) * d(1) < S(1,1) &&
////                      d(2) * d(2) < S(2,2) ?
////                      std::exp( - ( d * iS * d.transpose() )(0) ) : 0.0 ;
