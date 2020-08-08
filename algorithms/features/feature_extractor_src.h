#include "./feature_extractor.h"

namespace cvpp
{

TPL_D // Constructor
FeatureExtractor<D>::FeatureExtractor()
{
    algorithm = D::create();
}

TPL_D // Constructor
FeatureExtractor<D>::FeatureExtractor( const double& p1 )
{
    algorithm = D::create( p1 );
}

TPL_D // Constructor
FeatureExtractor<D>::FeatureExtractor( const double& p1 , const double& p2 , const double& p3 )
{
    algorithm = D::create( p1 , p2 , p3 );
}

TPL_D // Destructor
FeatureExtractor<D>::~FeatureExtractor()
{
}

// Extract Features
TPL_D TPL_TC KPts
FeatureExtractor<D>::compute( const Image<T,C>& img ) const
{
    KPts kpts;
    algorithm->detect( img.cv() , kpts );
    return kpts;
}

}
