#ifndef FEATURE_TRACKER_H
#define FEATURE_TRACKER_H

#include <cvpp/containers/vector.h>
#include <cvpp/containers/image.h>

#include <opencv2/optflow.hpp>

namespace cvpp
{

class FeatureTracker
{

protected:

    Seq<Img1c> list_img;
    Seq<Pts2f> list_pts;

    Seqc status;
    Seqf error;

    Size winSize,subWinSize;
    cv::TermCriteria termCrit;

    int maxLevel;
    double minEig;

public:

    FeatureTracker();

    ~FeatureTracker();

    const unsigned iter() const { return list_img.size(); }

    Pts2f& pFeats() { return list_pts[ iter() - 2 ]; }
    Pts2f& cFeats() { return list_pts[ iter() - 1 ]; }

    Img1c& pImage() { return list_img[ iter() - 2 ]; }
    Img1c& cImage() { return list_img[ iter() - 1 ]; }

    TPL_TC const void startGOOD( const Image<T,C>& , const unsigned& = 100 ,
                                 const double& = 0.01 , const double& = 10.0 );

    TPL_TC const void loopGOOD( const Image<T,C>& );

};

}

#include "./feature_tracker_src.h"

#endif
