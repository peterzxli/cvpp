#ifndef ROS_VID2TOP_H
#define ROS_VID2TOP_H

#include <cvpp/interfaces/cppture.h>
#include <cvpp/ros/ros_node.h>

namespace cvpp
{

class vid2top
{

protected:

    Img3c raw,img;

public:

    void run( const String& src , const String& dst , const double& fps )
    {
        CPPture cap( src );
        ROSnode node( "vid2top" );

        unsigned pub_image = node.addImagePublisher( dst );

        ros::Rate rate( fps );
        while( node.ok() && cap.read( raw ) )
        {
            node.publishImage( pub_image , raw.cv() );
            rate.sleep();
        }
    }
};

}

#endif
