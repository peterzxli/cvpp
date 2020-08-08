#ifndef ROS_TOP2VID_H
#define ROS_TOP2VID_H

#include <cvpp/interfaces/cpprint.h>
#include <cvpp/ros/ros_node.h>

namespace cvpp
{

class top2vid
{

protected:

    Img3c img;
    bool update,first;

public:

    void imageCallback( const sensor_msgs::ImageConstPtr& msg )
    {
        img >> cv_bridge::toCvShare( msg , "bgr8" )->image;
        update = true;
    }

    void run( const String& src , const String& dst , const int& fps )
    {
        ROSnode node( "top2vid" );
        CPPrint* video;

        node.addImageSubscriber( src , &top2vid::imageCallback , this );

        update = false , first = true;
        while( node.ok() )
        {
            if( update )
            {
                if( first )
                {
                    video = new CPPrint( dst , fps , Size( img.c() , img.r() ) , true );
                    first = false;
                }

                video->write( img );
                update = false;
            }

            node.spin();
        }
    }

};

}

#endif
