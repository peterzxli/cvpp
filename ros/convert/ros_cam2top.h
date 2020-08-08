#ifndef ROS_CAM2TOP_H
#define ROS_CAM2TOP_H

#include <cvpp/interfaces/cppture.h>
#include <cvpp/ros/ros_node.h>

namespace cvpp
{

class cam2top
{

protected:

    Img3c raw,img;

public:

    void run( const int& src , const String& dst )
    {
        ROSnode node( "cam2top" );
        CPPture cap( src );

        unsigned pub_image = node.addImagePublisher( dst );

        while( node.ok() && cap.read( raw ) )
        {
            node.publishImage( pub_image , raw.cv() );
        }
    }
};

}

#endif
