#include "../cvis.h"

namespace cvpp {
namespace cvis
{

Posef solvePnP( const Object& obj , const Pts2f& img , const Camera& cam )
{
    return solvePnP( obj.o2w().seq() , img.seq() , cam );
}

Posef solvePnP( const Pts3f& wld , const Pts2f& img , const Camera& cam )
{
    return solvePnP( wld.seq() , img.seq() , cam );
}

Posef solvePnP( const Seq<Pt3f>& wld , const Seq<Pt2f>& img , const Camera& cam )
{
    CV rvec,tvec;
    cv::solvePnP( wld , img , cam.matK().cv() , cam.matD().cv() , rvec , tvec );

    CV Rt,R;
    cv::Rodrigues( rvec , Rt );
    cv::transpose( Rt , R );
    CV t = - R * tvec;

    Posef pose;

    Matf trans( t , COPY );
    pose.setPos( trans );

    Matf rot( R , COPY );
    rot.RotateX( 90 ).RotateZ( 90 );
    pose.setOrient( rot );

    return pose;
}

}}
