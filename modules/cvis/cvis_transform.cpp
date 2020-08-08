#include "../cvis.h"

namespace cvpp {
namespace cvis
{

Posef calcRelPose( const Camera& cam1 ,
                   const CV& R , const CV& t , const float& scale )
{
    Posef pose;

    Matf tvec = cam1.pose->R() * alignVectorMAT( t ) * scale;
    CV rmat = rodrigues( alignTransVectorCV( rodrigues( R ) ) );

    pose.setPos( tvec ).setOrient( rmat );
    pose += cam1.pose;

    return pose;
}

int calcRelPose( Camera& cam2 , const Pts2f& pts2 , const Camera& cam1 , const Pts2f& pts1 ,
                  const CV& R1 , const CV& R2 , const CV& t , const float& scale )
{
    Pts2f img1 = pts1(0) , img2 = pts2(0);

    cam2 = calcRelPose( cam1 , R1 ,  t , scale );
    if( checkPosDepth( cam1 , img1 , cam2 , img2 ) ) return 1;

    cam2 = calcRelPose( cam1 , R2 ,  t , scale );
    if( checkPosDepth( cam1 , img1 , cam2 , img2 ) ) return 2;

    cam2 = calcRelPose( cam1 , R1 , -t , scale );
    if( checkPosDepth( cam1 , img1 , cam2 , img2 ) ) return 3;

    cam2 = calcRelPose( cam1 , R2 , -t , scale );
    if( checkPosDepth( cam1 , img1 , cam2 , img2 ) ) return 4;

    return 0;
}

CV calcWarpMat( const Pts2f& pts1 , const Pts2f& pts2 )
{
    return cv::getPerspectiveTransform( pts1.seq() , pts2.seq() );
}

CV calcTransfMat( const Pts3f& pts1 , const Pts3f& pts2 )
{
    Seqc inl; CV mat;
    cv::estimateAffine3D( pts1.seq() , pts2.seq() , mat , inl );
    return mat;
}

CV calcTransfMat( const Object& obj1 , const Object& obj2 )
{
    return calcTransfMat( obj1.wpoints() , obj2.wpoints() );
}

}}
