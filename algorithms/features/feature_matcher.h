#ifndef FEATURE_MATCHER_H
#define FEATURE_MATCHER_H

#include <cvpp/containers/image.h>
#include <cvpp/containers/vector.h>

namespace cvpp
{

TPL_D
class FeatureMatcher
{

protected:

    cv::DescriptorMatcher* algorithm;

public:

    FeatureMatcher();

    ~FeatureMatcher();

    MPts compute( const CV& , const CV& ) const;

    const void parse( const KPts& , const KPts& , const MPts& ,
                      Pts2f& , Pts2f& , const float& = 2.0 ) const;

};

}

#include "./feature_matcher_src.h"

#endif
