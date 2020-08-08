#include "./classifier_object.h"

namespace cvpp
{

Classifier::Classifier()
{
}

Classifier::Classifier( const String& str )
{
    initialise( str );
}

const void
Classifier::initialise( const String& str )
{
    if( !classifier.load( str ) )
        disp( "ERROR LOADING CLASSIFIER" );
}

TPL_TC Seq<Rect2i>
Classifier::detect( const Image<T,C>& img )
{
    Seq<Rect2i> rects;
    classifier.detectMultiScale(
                img.cv() , rects , 1.1 , 2 , 0 | cv::CASCADE_SCALE_IMAGE , Size( 30 , 30 ) );
    return rects;
}

}
