
#include <cvpp/interfaces/cpplot.h>
#include <cvpp/objects/object_board.h>
#include <cvpp/objects/object_camera.h>

#include <cvpp/modules/cvis.h>

using namespace cvpp;

int main( int argc , char* argv[] )
{
    // SET DRAW INTERFACE

    CPPlot draw( "Window" , 1 , 2 );
    draw[0].set3Dworld().setViewer( -3 , 0 , 3 , 0 , 0 , 0 );
    draw[1].set2Dimage().setResolution( 960 , 1280 ).setBackground( BLA );

    // START OBJECTS

    Board board( 3 , 3 , 3 , 0.2 );
    Camera cam1( "../data/virtual" );
    Camera cam2( "../data/virtual" );

    cam1.setPos( -1.0 , 0 , 0 ).setLook( 0 , 0 , 0 );
    cam2.setPos( -1.0 , 0 , 0 ).setLook( 0 , 0 , 0 );

    // DRAW

    while( draw.input() )
    {
        // PROJECT POINTS

        Pts2f img = cam1.w2u( board.points() );

        // CALCULATE POSE

        if( img.n() == board.n() )
            cam2 = cvis::solvePnP( board , img , cam1 );

        // DRAW SCREEN 0

        draw[0].clear();
        draw.psc(4,RED).object( board ).lwc(2,WHI).object( cam1 ).object( cam2 );
        draw.psc(8,GRE).pts3D( cam2.o2w() );

        // DRAW SCREEN 1

        draw[1].clear();
        draw.psc(4,RED).pts2D( img );

        // UPDATE WINDOW

        draw.updateWindow(30);

        // CONTROL CAMERA

        draw.control( cam1 );
    }

    return 0;
}
