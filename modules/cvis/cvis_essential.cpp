#include "../cvis.h"

#include "opencv2/calib3d.hpp"
#include <cvpp/auxiliar/definitions.h>

namespace cvpp {
namespace cvis
{

CV calcEmat( const Pts2f& pts1 , const Pts2f& pts2 )
{
    double f = 600 ; Pt2d pp( 640 , 480 ) ;
    return cv::findEssentialMat( pts1.cv() , pts2.cv() , f , pp );
}

void decompEmat( const CV& E , CV& R1 , CV& R2 , CV& t )
{
    cv::decomposeEssentialMat( E , R1 , R2 , t );
}

CV calcEmat( const Pts2f& pts1 , const Pts2f& pts2 ,
             CV& R1 , CV& R2 , CV& t )
{
    CV E = calcEmat( pts1 , pts2 );
    decompEmat( E , R1 , R2 , t );
    return E;
}

bool checkPosDepth( const Camera& cam1 , const Camera& cam2 ,
                    const Pts3f& pts )
{
    return cam1.w2o( pts )[0].x > 0 &&
           cam2.w2o( pts )[0].x > 0;
}

bool checkPosDepth( const Camera& cam1 , const Pts2f& img1 ,
                    const Camera& cam2 , const Pts2f& img2 )
{
    Pts3f pts = triangulate( cam1 , img1 , cam2 , img2 );
    return checkPosDepth( cam1 , cam2 , pts );
}

}}
