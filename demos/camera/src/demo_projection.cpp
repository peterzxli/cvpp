
#include <cvpp/interfaces/cpplot.h>
#include <cvpp/interfaces/cppture.h>

#include <cvpp/interfaces/cppture.h>
#include <cvpp/objects/object_board.h>
#include <cvpp/objects/object_world.h>
#include <cvpp/objects/object_camera.h>

using namespace cvpp;

int main( int argc , char* argv[] )
{
    // SET CAPTURE INTERFACE

    CPPture capture(0);

    // SET PLOT INTERFACE

    CPPlot draw( "Window" , ULHW( 480 , 2 * 640 ) , 1 , 2 );
    draw[0].set2Dimage();
    draw[1].set3Dworld().setViewer( -2.0 , 0.0 , 0.0 ,
                                     0.0 , 0.0 , 0.0 );

    // CREATE OBJECTS

    Camera cam( "../data/webcam" );
    cam.setPos( -1.0 , 0.0 , 0.0 );

    Board board( 3.0 , 3.0 , 3.0 , 0.1 );
    board.setPos( 1.0 , 0.0 , 0.0 );

    World world;
    world.push( board );

    // SET TEXTURE

    unsigned tex = draw.addTexture3U( 480 , 640 );

    // DRAW

    Img3c img;
    while( draw.input() && capture.read( img ) )
    {
        draw[0].clear();                            // Screen 0 (left)

        draw.useTexture( tex , img );               // Draw texture
        draw.psc(6,RED).pts2D( cam.w2d( board ) );  // Draw image points

        draw[1].clear();                            // Screen 1 (right)

        draw.psc(4,RED).object( world );            // Draw world points
        draw.lwc(2,WHI).object( cam , world );      // Draw camera

        draw.updateWindow();                        // Update window
        draw.control( cam );                        // Control camera
    }


    return 0;
}
