
#include <cvpp/interfaces/cpplot.h>
#include <cvpp/interfaces/cppture.h>

#include <cvpp/interfaces/cppture.h>
#include <cvpp/objects/object_board.h>
#include <cvpp/objects/object_world.h>
#include <cvpp/objects/object_camera.h>

using namespace cvpp;

int main( int argc , char* argv[] )
{
    // LOAD DATA

    Matd pts( "../data/riegl_pts_01" ); pts.SampleRows( 5 );
    Matf clr( "../data/riegl_clr_01" ); clr.SampleRows( 5 );

    Pts3f wld = pts.toFloat();
    Pts2f img; Vecf dep; Matf tex;

    // SET PLOT INTERFACE

    CPPlot draw( "Window" , ULHW( 2 * 400 , 2 * 600 ) , 2 , 2 );
    draw[0].set3Dworld().setViewer( 0.0739633 , -1.463760 , 1.049420 ,
                                    0.0916358 , -0.581741 , 0.578544 );

    // INITIALISE CAMERA

    Camera cam( "../data/virtual" ); cam.setLook( 0.0 , 1.0 , 0.0 );
    draw[1].set3Dworld().setViewer( cam.pose ).calibrate( cam.matK() , cam.height() , cam.width() );

    // INITIALISE IMAGE SCREEN

    draw[2].set2Dimage().setResolution( 480 , 640 ).setBackground(BLA);

    // CREATE BUFFERS

    unsigned buf_pts = draw.addBuffer3D( pts );
    unsigned buf_clr = draw.addBuffer3D( clr );

    // DRAW

    while( draw.input() )
    {
        img = cam.w2r( wld , dep );             // Project world points
        tex = dep.toRGBjet( 0.1 , 10.0 );       // Calculate image points color

        draw[0].clear();                        // Screen 0 (upper left)
        draw.ps(3).pts3D( buf_pts , buf_clr );  // Draw world points
        draw.lwc(2,WHI).object( cam );          // Draw camera

        draw[1].clear();                        // Screen 1 (upper right)
        draw.ps(3).pts3D( buf_pts , buf_clr );  // Draw world points

        draw[2].clear();                        // Screen 2 (bottom left)
        draw.ps(3).pts2D( img , tex );          // Draw image points

        draw.updateWindow(30);                  // Update window
        draw.control( cam );                    // Control camera

        if( draw.keys.enter )                   // Save image if enter is hit
            draw[2].save( "img.png" );
    }

    return 0;
}
