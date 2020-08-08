#ifndef ROS_TOP2TOP_H
#define ROS_TOP2TOP_H

#include <cvpp/ros/ros_node.h>

namespace cvpp
{

class top2top
{

protected:

    Img3c raw,img;
    bool update;

public:

    void imageCallback( const sensor_msgs::ImageConstPtr& msg )
    {
        raw >> cv_bridge::toCvShare( msg , "bgr8" )->image;
        update = true;
    }

    void run( const String& src , const String& dst ,
              const int& r = -1 , const int& c = -1 )
    {
        ROSnode node( "top2top" );
        update = false;

        unsigned pub_image = node.addImagePublisher( dst );
        node.addImageSubscriber( src , &top2top::imageCallback , this );

        while( node.ok() )
        {
            node.spin();

            if( update )
            {
                img = raw.resize( Dims( r , c ) );
                node.publishImage( pub_image , img.cv() );
                update = false;
            }
        }
    }
};

}

#endif
