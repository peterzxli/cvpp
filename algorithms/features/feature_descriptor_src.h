#include "./feature_descriptor.h"

namespace cvpp
{

TPL_D // Constructor
FeatureDescriptor<D>::FeatureDescriptor()
{
    algorithm = D::create();
}

TPL_D // Destructor
FeatureDescriptor<D>::~FeatureDescriptor()
{
}

// Describe Features
TPL_D TPL_TC CV
FeatureDescriptor<D>::compute( const Image<T,C>& img , KPts& kpts ) const
{
    CV desc;
    algorithm->compute( img.cv() , kpts , desc );
    return desc;
}

}
