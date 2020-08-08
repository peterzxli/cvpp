#include "./feature_matcher.h"

namespace cvpp
{

TPL_D // Constructor
FeatureMatcher<D>::FeatureMatcher()
{
    algorithm = new D;
}

TPL_D // Destructor
FeatureMatcher<D>::~FeatureMatcher()
{
    delete algorithm;
}

TPL_D // Match Descriptors
MPts
FeatureMatcher<D>::compute( const CV& desc1 , const CV& desc2 ) const
{
    MPts mtc;
    algorithm->match( desc1 , desc2 , mtc );
    return mtc;
}

// Parse Matches
TPL_D const void
FeatureMatcher<D>::parse( const KPts& kpts1 , const KPts& kpts2 , const MPts& mtc ,
                       Pts2f& pts1 , Pts2f& pts2 , const float& thr ) const
{
    float min = PINF , max = NINF ;
    forLOOPi( mtc.size() )
    {
        if( mtc[i].distance < min ) min = mtc[i].distance;
        if( mtc[i].distance > max ) max = mtc[i].distance;
    }

    pts1.reset().reserve( mtc.size() );
    pts2.reset().reserve( mtc.size() );

    forLOOPi( mtc.size() )
    {
        if( mtc[i].distance < thr * min )
        {
            pts1.push( kpts1[ mtc[i].queryIdx ].pt );
            pts2.push( kpts2[ mtc[i].trainIdx ].pt );
        }
    }
}

}
