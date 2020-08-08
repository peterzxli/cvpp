#ifndef ROS_CAM2SCR_H
#define ROS_CAM2SCR_H

#include <cvpp/interfaces/cpplot.h>
#include <cvpp/interfaces/cppture.h>

namespace cvpp
{

class cam2scr
{

protected:

    Img3c img;

public:


    void run( const int& idx )
    {
        CPPture cap( idx );
        CPPlot draw("Window"); draw[0].set2Dimage();

        cap.read( img );
        unsigned tex = draw.addTexture( img );

        while( draw.input() && cap.read( img ) )
        {
            draw[0].clear().useTexture( tex , img );
            draw.updateWindow();
        }
    }

};

}

#endif
