#ifndef ROS_TOP2SCR_H
#define ROS_TOP2SCR_H

#include <cvpp/interfaces/cpplot.h>
#include <cvpp/ros/ros_node.h>

namespace cvpp
{

class top2scr
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

    void run( const String& src )
    {
        ROSnode node( "top2scr" );
        CPPlot draw("Window"); draw[0].set2Dimage();
        unsigned tex;

        node.addImageSubscriber( src , &top2scr::imageCallback , this );

        update = false , first = true;
        while( draw.input() && node.ok() )
        {
            if( update )
            {
                if( first )
                {
		    img.info();
                    tex = draw.addTexture( img );
                    draw[0].setResolution( img );
                    first = false;
                }

                draw[0].clear().useTexture( tex , img );
                draw.updateWindow();
                update = false;
            }

            node.spin();
        }
    }

};

}

#endif
