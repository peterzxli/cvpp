
#include <cvpp/ros/ros_node.h>

namespace cvpp
{

inline
ROSnode::ROSnode( const String& str )
{
    int argc = 0 ; char** argv = NULL;
    ros::init( argc , argv , str );

    node = new ros::NodeHandle;
    img_trans = NULL;
}

inline
ROSnode::~ROSnode()
{
    if( node ) delete node;
    if( img_trans ) delete img_trans;
}

// Add Subscriber
TPL_T inline void
ROSnode::addSubscriber( const String& str ,
                        void function( const T& ) )
{
    subs.push_back( node->subscribe( str , 1000 , function ) );
}

// Add Subscriber
TPL_TU inline void
ROSnode::addSubscriber( const String& str ,
                        void (U::* function)( const T& ) , U* ptr )
{
    subs.push_back( node->subscribe( str , 1000 , function , ptr ) );
}

// Add Image Subscriber
TPL_T inline void
ROSnode::addImageSubscriber( const String& str ,
                             void function( const T& ) )
{
    if( !img_trans )
        img_trans = new image_transport::ImageTransport( *node );

    img_subs.push_back( img_trans->subscribe( str , 1000 ,  function ) );
}

// Add Image Subscriber
TPL_TU inline void
ROSnode::addImageSubscriber( const String& str ,
                             void (U::* function)( const T& ) , U* ptr )
{
    if( !img_trans )
        img_trans = new image_transport::ImageTransport( *node );

    img_subs.push_back( img_trans->subscribe( str , 1000 ,  function , ptr ) );
}

// Add Publisher
TPL_T inline int
ROSnode::addPublisher( const String& str )
{
    pubs.push_back( node->advertise<T>( str , 1000 ) );
    return pubs.size() - 1;
}

// Add Image Publisher
inline int
ROSnode::addImagePublisher( const String& str )
{
    if( !img_trans )
        img_trans = new image_transport::ImageTransport( *node );

    img_pubs.push_back( img_trans->advertise( str , 1000 ) );
    return img_pubs.size() - 1;
}

// Publish
TPL_T inline void
ROSnode::publish( const int& n , const T& msg ) const
{
    pubs[n].publish( msg );
}

// Publish
inline void
ROSnode::publish( const int& n , const sensor_msgs::ImagePtr& msg ) const
{
    img_pubs[n].publish( msg );
}

}
