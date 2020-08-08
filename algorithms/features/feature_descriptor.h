#ifndef FEATURE_DESCRIPTOR_H
#define FEATURE_DESCRIPTOR_H

#include <cvpp/containers/image.h>

namespace cvpp
{

TPL_D
class FeatureDescriptor
{

protected:

    cv::Ptr<D> algorithm;

public:

    FeatureDescriptor();

    ~FeatureDescriptor();

    TPL_TC CV compute( const Image<T,C>& , KPts& ) const;

};

}

#include "./feature_descriptor_src.h"

#endif
