#include "./tracker_object.h"

namespace cvpp
{

TPL_D // Constructor
ObjectTracker<D>::ObjectTracker( const String& str )
{
    algorithm = D::create( str );
}

TPL_D // Destructor
ObjectTracker<D>::~ObjectTracker()
{
}

// Start
TPL_D TPL_TC const void
ObjectTracker<D>::start( const Image<T,C>& img , const Borders2d& brd )
{
    rect = brd.rect();
    algorithm->init( img.cv() , rect );
}

// Update
TPL_D TPL_TC const void
ObjectTracker<D>::update( const Image<T,C>& img )
{
    algorithm->update( img.cv() , rect );
}

}
