#ifndef CLASSIFIER_OBJECT_H
#define CLASSIFIER_OBJECT_H

#include <cvpp/containers/image.h>

#include "opencv2/objdetect.hpp"

namespace cvpp
{

class Classifier
{

protected:

    cv::CascadeClassifier classifier;

public:

    Classifier();
    Classifier( const String& );

    const void initialise( const String& );

    TPL_TC Seq<Rect2i> detect( const Image<T,C>& );

};

}

#include "./classifier_object_src.h"

#endif
