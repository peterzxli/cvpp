#ifndef FEATURE_EXTRACTOR_H
#define FEATURE_EXTRACTOR_H

#include <cvpp/containers/image.h>

namespace cvpp
{

TPL_D
class FeatureExtractor
{

protected:

    cv::Ptr<D> algorithm;

public:

    FeatureExtractor();
    FeatureExtractor( const double& );
    FeatureExtractor( const double& , const double& , const double& );

    ~FeatureExtractor();

    TPL_TC KPts compute( const Image<T,C>& ) const;

};

}

#include "./feature_extractor_src.h"

#endif
