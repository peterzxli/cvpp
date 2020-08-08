#include "../cvis.h"

#include "opencv2/calib3d.hpp"
#include <cvpp/auxiliar/definitions.h>

namespace cvpp {
namespace cvis
{

CV alignTransVectorCV( const CV& src )
{
    CV dst = src.clone();

    dst.at<double>(0) = + src.at<double>(2);
    dst.at<double>(1) = - src.at<double>(0);
    dst.at<double>(2) = - src.at<double>(1);

    return dst;
}

Matf alignVectorMAT( const CV& src )
{
    Matf dst( 3 );

    dst(0) = - src.at<double>(2) ,
    dst(1) = + src.at<double>(0) ,
    dst(2) = + src.at<double>(1) ;

    return dst;
}

}}

