#include "./feature_tracker.h"

namespace cvpp
{

// Constructor
FeatureTracker::FeatureTracker()
{
    list_img.reserve( 10000 );
    list_pts.reserve( 10000 );

    winSize = Size( 31 , 31 );
    subWinSize = Size( 10 , 10 );

    maxLevel = 3 , minEig = 0.001;

    termCrit = cv::TermCriteria( cv::TermCriteria::COUNT |
                                 cv::TermCriteria::EPS , 30 , 0.01 );
}

// Destructor
FeatureTracker::~FeatureTracker()
{
}

// Start GOOD Tracking
TPL_TC const void
FeatureTracker::startGOOD( const Image<T,C>& img , const unsigned& max_feat ,
                           const double& qlty_level , const double& min_dist )
{
    list_img.push_back( img.clone() );
    list_pts.resize( iter() );

    cv::goodFeaturesToTrack( cImage().cv() , cFeats().seq() ,
                             max_feat , qlty_level , min_dist );
    cFeats().update();
}

// Loop GOOD Tracking
TPL_TC const void
FeatureTracker::loopGOOD( const Image<T,C>& img )
{
    list_img.push_back( img.clone() );
    list_pts.resize( iter() );

    cv::calcOpticalFlowPyrLK( pImage().cv()  , cImage().cv()  ,
                              pFeats().seq() , cFeats().seq() ,
                              status , error , winSize , maxLevel , termCrit , 0 , minEig );
    cFeats().update();

    unsigned k = 0;
    forLOOPi( status.size() )
    {
        if( status[i] == 1 && error[i] < 5 )
        {
            pFeats()[k] = pFeats()[i];
            cFeats()[k] = cFeats()[i];

            k++;
        }
    }

    pFeats().keepFront( k );
    cFeats().keepFront( k );
}

}
