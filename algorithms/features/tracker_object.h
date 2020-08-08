#ifndef OBJECT_TRACKER_H
#define OBJECT_TRACKER_H

#include <cvpp/containers/image.h>
#include <cvpp/structs/struct_borders2.h>

#include <opencv2/tracking.hpp>

namespace cvpp
{

using cvTracker = cv::Tracker;

TPL_D
class ObjectTracker
{

protected:

    Rect2d rect;
    cv::Ptr<D> algorithm;

public:

    ObjectTracker( const String& );

    ~ObjectTracker();

    Borders2d brd() const { return rect; }

    TPL_TC const void start( const Image<T,C>& , const Borders2d& );
    TPL_TC const void update( const Image<T,C>& );

};

}

#include "./tracker_object_src.h"

#endif
