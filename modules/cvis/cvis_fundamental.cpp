#include "../cvis.h"

#include "opencv2/calib3d.hpp"
#include <cvpp/auxiliar/definitions.h>

namespace cvpp {
namespace cvis
{

CV calcFmat( const Pts2f& pts1 , const Pts2f& pts2 ,
                const float& thr , const float& prb )
{
    return cv::findFundamentalMat( pts1.cv() , pts2.cv() ,
                                   CV_FM_RANSAC , thr , prb );
}

CV calcFmat( const Pts2f& pts1 , const Pts2f& pts2 , CV& epips1 , CV& epips2 ,
                const float& thr , const float& prb )
{
    CV F = calcFmat( pts1 , pts2 , thr , prb );
    epips1 = epipNext( pts1 , F );
    epips2 = epipPrev( pts2 , F );
    return F;
}

CV epipPrev( const Pts2f& pts , const CV& F ) { return epipolar( pts , F , 2 ); }
CV epipNext( const Pts2f& pts , const CV& F ) { return epipolar( pts , F , 1 ); }

CV epipolar( const Pts2f& pts , const CV& F , const int& num )
{
    CV epips;
    cv::computeCorrespondEpilines( pts.cv() , num , F , epips );
    return epips;
}

}}

