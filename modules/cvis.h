#ifndef CVIS_H
#define CVIS_H

#include <cvpp/objects/object_camera.h>

namespace cvpp {
namespace cvis
{

// FUNDAMENTAL

CV calcFmat( const Pts2f& , const Pts2f& , const float& = 3.0 , const float& = 0.99 );
CV calcFmat( const Pts2f& , const Pts2f& , CV& , CV& , const float& = 3.0 , const float& = 0.99 );

CV epipolar( const Pts2f& , const CV& , const int& );

CV epipPrev( const Pts2f& , const CV& );
CV epipNext( const Pts2f& , const CV& );


// ESSENTIAL

CV calcEmat( const Pts2f& , const Pts2f& );
CV calcEmat( const Pts2f& , const Pts2f& , CV& , CV& , CV& );

void decompEmat( const CV& , CV& , CV& , CV& );

bool checkPosDepth( const Camera& , const Camera& , const Pts3f& );
bool checkPosDepth( const Camera& , const Pts2f& , const Camera& , const Pts2f& );

// SOLVER

Posef solvePnP( const Pts3f& , const Pts2f& , const Camera& );
Posef solvePnP( const Seq<Pt3f>& , const Seq<Pt2f>& , const Camera& );
Posef solvePnP( const Object& , const Pts2f& , const Camera& );

// TRANSFORM

int calcRelPose( Camera& , const Pts2f& , const Camera& , const Pts2f& ,
                 const CV& , const CV& , const CV& , const float& = 1.0 );

Posef calcRelPose( const Camera& ,
                   const CV& , const CV& , const float& = 1.0 );

Posef calcRelPose( const Camera& , const Pts2f& , const Camera& , const Pts2f& ,
                   const CV& , const CV& , const CV& , const float& = 1.0 );

CV calcWarpMat( const Pts2f& , const Pts2f& );

CV calcTransfMat( const Pts3f& , const Pts3f& );
CV calcTransfMat( const Object& , const Object& );

// TRIANGULATE

Pt3f triangulate( const Pt3f& , const Pt3f& , const Pt3f& , const Pt3f& );
Pts3f triangulate( const Camera& , const Pts2f& , const Camera& , const Pts2f& );

// RODRIGUES

CV rodrigues( const CV& );

// CONVERT

Matf alignVectorMAT( const CV& );
CV alignTransVectorCV( const CV& );

}}

#endif
