#include "../cvis.h"

#include "opencv2/calib3d.hpp"
#include <cvpp/auxiliar/definitions.h>

namespace cvpp {
namespace cvis
{

CV rodrigues( const CV& src )
{
    CV dst;
    cv::Rodrigues( src , dst );
    return dst;
}

}}

//Matf rvec2rmat1( const CV& r )
//{
//    Matf mr = r.clone();
//    float n = sqrt( mr.sqsum() ) , cn = cos(n);
//    mr /= n;

//    Matf M( 3 , 3 );
//    M <<     0   , - mr(2) ,   mr(1) ,
//           mr(2) ,     0   , - mr(0) ,
//         - mr(1) ,   mr(0) ,     0   ;

//    Matf cnI( 3 , 3 );
//    cnI.setIdentity( cn );

//    Matf A = cnI;
//    Matf B = ( 1 - cn ) * mr * mr.t();
//    Matf C = sin(n) * M;

//    return A + B + C;
//}

//Matf rvec2rmat2( const CV& r )
//{
//    float n = cv::norm( r );
//    if( n == 0 ) return MatIDTYf( 3 );
//    float sn = sin(n) , cn = cos(n) , cn1 = 1.0 - cn ;

//    float x = r.at<double>(0) / n ;
//    float y = r.at<double>(1) / n ;
//    float z = r.at<double>(2) / n ;

//    Matf R( 3 , 3 );
//    R <<       cn + x * x * cn1 , - z * sn + y * x * cn1 ,   y * sn + z * x * cn1 ,
//           z * sn + x * y * cn1 ,       cn + y * y * cn1 , - x * sn + z * y * cn1 ,
//         - y * sn + x * z * cn1 ,   x * sn + y * z * cn1 ,       cn + z * z * cn1 ;

//    return R;
//}

//Matf rmat2rvec1( const CV& R )
//{
//    Matf mR = R;
//    Matf RRT2 = ( mR - mR.t() ) / 2.0;

//    float x = RRT2(2,1);
//    float y = RRT2(0,2);
//    float z = RRT2(1,0);

//    float s = sqrt( x*x + y*y + z*z );
//    float c = ( mR(0,0) + mR(1,1) + mR(2,2) - 1.0 ) / 2.0;

//    Matf mr( 3 );
//    mr << x , y , z ;
//    mr = mr / s * atan2( s , c );

//    return mr;
//}

//Matf rmat2rvec2( const CV& R )
//{
//    float x = ( R.at<double>(2,1) - R.at<double>(1,2) ) / 2.0 ;
//    float y = ( R.at<double>(0,2) - R.at<double>(2,0) ) / 2.0 ;
//    float z = ( R.at<double>(1,0) - R.at<double>(0,1) ) / 2.0 ;

//    float s = sqrt( x * x + y * y + z * z );
//    float c = ( R.at<double>(0,0) + R.at<double>(1,1) + R.at<double>(2,2) - 1.0 ) / 2.0;

//    disp( s , c );
//    if( s == 0 )
//    {
//        if( c == 1 )
//        {
//           return MatZEROSf( 3 );
//        }

//        if( c == -1 )
//        {
//            Matf r( 3 );
//                            r(0) = PI * R.at<double>(0,0);
//            if( r(0) == 0 ) r(1) = PI * R.at<double>(1,1) ; else r(1) = 0.0;
//            if( r(1) == 0 ) r(2) = PI * R.at<double>(2,2) ; else r(2) = 0.0;

//            return r;
//        }
//    }
//    else
//    {
//        Matf r( 3 ); r << x , y , z ;
//        return r / s * atan2( s , c );
//    }
//}
