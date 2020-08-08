
#include <cvpp/interfaces/cpplot.h>

#include <cvpp/objects/object_board.h>
#include <cvpp/objects/object_camera.h>

#include <cvpp/modules/cvis.h>

using namespace cvpp;

int main( int argc , char* argv[] )
{
    // SET PLOT INTERFACE

    CPPlot draw( "Window" , ULHW( 0 , 0 , 2 * 480 , 3 * 640 ) , 2 , 3 );

    // START OBJECTS

    Board board( 3 , 3 , 3 , 0.2 );
    Camera cam1( "../data/virtual" );
    Camera cam2( "../data/virtual" );

    // SET OBJECT POSES

    cam1.setPos( -1.0 , 0 , 0 ).setLook( 0 , 0 , 0 );
    cam2.setPos( -1.2 , 0 , 0 ).setLook( 0 , 0 , 0 );

    // SET DRAW SCREENS

    draw[0].set3Dworld().setViewer( -3 , 0 , 3 , 0 , 0 , 0 );

    draw[1].set3Dworld().setViewer( cam1.pose );
    draw[2].set3Dworld().setViewer( cam2.pose );

    draw[3].set2Dimage().setResolution( 960 , 1280 ).setBackground( BLA );
    draw[4].set2Dimage().setResolution( 960 , 1280 ).setBackground( BLA );
    draw[5].set2Dimage().setResolution( 960 , 1280 ).setBackground( BLA );

    // SET BOARD COLOR (FOR VISUALIZATION)

    Mati idx( board.n() ); idx.setIncrease();
    Matf clr = idx.toRGBlbl();

    // START EPIPOLAR VARIABLES

    CV F;
    CV epip1,epip2;

    bool control = 0;
    while( draw.input() )
    {
        // PROJECT WORLD POINTS INTO IMAGES

        Pts2f img1 = cam1.w2u( board.points() );
        Pts2f img2 = cam2.w2u( board.points() );

        Pts3f xyz1; xyz1.push( cam1.pose->getPosPt() );
        Pts3f xyz2; xyz2.push( cam2.pose->getPosPt() );

        Pts2f pos1 = cam2.w2u( xyz1 );
        Pts2f pos2 = cam1.w2u( xyz2 );

        // COMPUTE FUNDAMENTAL MATRIX AND EPIPOLES

        if( img1.n() == img2.n() )
            F = cvis::calcFmat( img1 , img2 , epip1 , epip2 );

        // DRAW SCREEN 0
        draw[0].clear();
        draw.psc(4,RED).object( board ).lwc(2,WHI).object( cam1 ).object( cam2 );
        draw.lwc(2,GRE).line3D( cam1.pose->getPosPt() , cam2.pose->getPosPt() );

        // DRAW SCREEN 1
        draw[1].clear();
        draw.psc(4,RED).object( board ).lwc(2,WHI).object( cam2 );

        // DRAW SCREEN 2
        draw[2].clear();
        draw.psc(4,RED).object( board ).lwc(2,WHI).object( cam1 );

        // DRAW SCREEN 3
        draw[3].clear();
        draw.ps(4).pts2D( img1 , clr ).pts2D( img2 , clr );
        draw.lwc(2,GRE).cct2D( img1 , img2 );

        // DRAW SCREEN 4
        draw[4].clear();
        draw[4].ps(8).pts2D( img1 , clr );
        if( img1.n() == img2.n() )
            draw.lwc(2,BLU).epip2D( epip2 ).psc(8,RED).pts2D( pos2 );

        // DRAW SCREEN 5
        draw[5].clear();
        draw[5].ps(8).pts2D( img2 , clr );
        if( img1.n() == img2.n() )
            draw.lwc(2,BLU).epip2D( epip1 ).psc(8,RED).pts2D( pos1 );

        // UPDATE WINDOW
        draw.updateWindow(30);

        // CHANGE CONTROL WITH TAB
        if( draw.keys.tab )
            control = !control , halt(100);

        // CONTROL CAMERA
        if( control == 0 )
             draw.control( cam1 );
        else draw.control( cam2 );
    }

    return 0;
}
