
#include <cvpp/interfaces/cpplot.h>
#include <cvpp/modules/cvis.h>

#include <cvpp/objects/object_board.h>
#include <cvpp/objects/object_camera.h>

using namespace cvpp;

int main()
{
    // START DRAW INTERFACE

    CPPlot draw( "Window" );
    draw[0].set3Dworld().setViewer( -2.0 , 0.0 , 2.0 );

    // CREATE BOARDS

    Seq<Board> brd(2);
    brd[0].initialise( 3 , 4 , 5 , 0.2 );
    brd[1].initialise( 3 , 4 , 5 , 0.2 );

    // SET BOARDS POSITION

    brd[0].setPos( 0.0 , 0.0 , 0.0 );
    brd[1].setPos( 0.3 , 0.3 , 0.0 );

    // TRANSFORM BOARDS

    CV T = cvis::calcTransfMat( brd[0] , brd[1] );
    Pts3f pts3 = brd[0].transform( T );
    Pts3f pts4 = brd[1].itransform( T );

    // LOOP DRAW

    int n = 0;
    while( draw.input() )
    {
        draw[0].clear();

        draw.psc(6,RED).object( brd[0] );  // Draw first board
        draw.psc(6,BLU).object( brd[1] );  // Draw second board

        draw.lwc(3,CYA).line3D( pts3 );    // Draw first board transformed
        draw.lwc(3,MAG).line3D( pts4 );    // Draw second board transformed

        draw.updateWindow(30);             // Update window

        if( draw.keys.tab )
            n = ++n % 2 , halt(100);       // Switch board control

        if( draw.control( brd[n] ) )       // Move board
        {
            T = cvis::calcTransfMat( brd[0] , brd[1] );  // Calculate transform matrix
            pts3.Transform( brd[0].wpoints() , T );      // Transform first board
            pts4.iTransform( brd[1].wpoints() , T );     // Transform second board
        }
    }

    return 0;
}
