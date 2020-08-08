#include "../image.h"

namespace cvpp
{

TPL_TC inline Image<float,1>
Image<T,C>::matchTemplate( const Image<T,C>& tpl )
{
    Img1f res( r() - tpl.r() + 1 , c() - tpl.c() + 1 );

    cv::matchTemplate( cv() , tpl.cv() , res.cv() , CV_TM_SQDIFF_NORMED );
    cv::normalize( res.cv() , res.cv() , 0 , 1 , cv::NORM_MINMAX , -1 , cv::Mat() );

    double minVal , maxVal;
    cv::Point minLoc , maxLoc , matchLoc;

    cv::minMaxLoc( res.cv() , &minVal , &maxVal , &minLoc , &maxLoc , cv::Mat() );
    matchLoc = minLoc;

    return res;
}

}
