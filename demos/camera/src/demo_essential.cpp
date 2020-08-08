
#include <cvpp/interfaces/cpplot.h>

#include <cvpp/objects/object_board.h>
#include <cvpp/objects/object_camera.h>

#include <cvpp/auxiliar/macros.h>
#include <cvpp/modules/cvis.h>

using namespace cvpp;
using namespace cvis;

int main( int argc , char* argv[] )
{
    // START DRAW INTERFACE

    CPPlot draw( "Window" , ULHW( 0 , 0 , 2 * 480 , 3 * 640 ) , 2 , 3 );

    // CREATE BOARD

    Board board( 3 , 3 , 3 , 0.2 );

    // CREATE CAMERAS

    Camera cam1( "../data/virtual" );
    Camera cam2( "../data/virtual" );

    Camera camA( "../data/virtual" );
    Camera camB( "../data/virtual" );
    Camera camC( "../data/virtual" );
    Camera camD( "../data/virtual" );

    Camera cam( "../data/virtual" );

    // POSITION CAMERAS

    cam1.setPos( -1.0 , 0.5 , 0 ).setLook( 0 , 0.5 , 0 );
    cam2.setPos( -1.2 , 0.0 , 0 ).setLook( 0 , 0 , 0 );

    // SET SCREENS

    draw[0].set3Dworld().setViewer( -2 , 0 , 1 , 0 , 0 , -1 );

    draw[1].set3Dworld().setViewer( cam1.pose ).calibrate( cam1.matK() );
    draw[2].set3Dworld().setViewer( cam2.pose ).calibrate( cam2.matK() );

    draw[3].set2Dimage().setResolution( 960 , 1280 ).setBackground( BLA );
    draw[4].set2Dimage().setResolution( 960 , 1280 ).setBackground( BLA );
    draw[5].set2Dimage().setResolution( 960 , 1280 ).setBackground( BLA );

    // SET BOARD POINT COLORS

    Mati idx( board.n() ); idx.setIncrease();
    Matf clr = idx.toRGBlbl();

    // START VARIABLES

    float scale;
    Pts3f pA,pB,pC,pD;
    Pts2f img1,img2;
    CV E,R1,R2,t;

    int crt = 0;
    bool control = 0;

    // DRAW

    while( draw.input() )
    {
        // PROJECT BOARD POINTS TO SCREENS

        img1 = cam1.w2u( board.points() );
        img2 = cam2.w2u( board.points() );

        if( img1.n() == img2.n() )
        {
            // CALCULATE SCALE

            scale = norm( cam1.pose->getPosPt() ,
                          cam2.pose->getPosPt() );

            // CALCULATE ESSENTIAL MATRIX

            E = calcEmat( img1 , img2 , R1 , R2 , t );

            // FOUR POSSIBLE CAM POSES

            camA = calcRelPose( cam2 , R1 ,  t , scale );
            camB = calcRelPose( cam2 , R2 ,  t , scale );
            camC = calcRelPose( cam2 , R1 , -t , scale );
            camD = calcRelPose( cam2 , R2 , -t , scale );

            // CALCULATE CORRECT CAM POSE

            crt = calcRelPose( cam , img1 , cam2 , img2 , R1 , R2 , t , scale );

            // TRIANGULATE FOR FOUR POSSIBLE CAM POSES

            pA = triangulate( camA , img1 , cam2 , img2 );
            pB = triangulate( camB , img1 , cam2 , img2 );
            pC = triangulate( camC , img1 , cam2 , img2 );
            pD = triangulate( camD , img1 , cam2 , img2 );
        }

        // CALCULATE LINES FOR BASE CAM

        Pts3f wld2a = cam2.u2w( img2 , -10.0 );
        Pts3f wld2b = cam2.u2w( img2 , +10.0 );

        // DRAW SCREEN 0

        draw[0].clear();
        draw.psc(5,WHI).object( board ).lwc(2,WHI).object( cam1 ); // CAM 1

        draw.lwc(2,WHI).object( cam2 ).psc( 6 , YEL ).pts3D( cam2.o2w() ); // CAM2 + EDGES

        draw.lwc(2,WHI).object( camA ).psc( 6 , crt == 1 ? GRE : RED ).pts3D( camA.o2w() ); // CAMA + EDGES
        draw.lwc(2,WHI).object( camB ).psc( 6 , crt == 2 ? GRE : RED ).pts3D( camB.o2w() ); // CAMB + EDGES
        draw.lwc(2,WHI).object( camC ).psc( 6 , crt == 3 ? GRE : RED ).pts3D( camC.o2w() ); // CAMC + EDGES
        draw.lwc(2,WHI).object( camD ).psc( 6 , crt == 4 ? GRE : RED ).pts3D( camD.o2w() ); // CAMD + EDGES

        draw.lwc(2,WHI).object( cam  ).psc( 9 , PUR ).pts3D( cam.o2w() ); // CORRECT CAM + EDGES

        if( img1.n() == img2.n() )
        {
            // TRIANGULATE POINTS

            draw.psc( 9 , crt == 1 ? GRE : RED ).pts3D( pA );
            draw.psc( 9 , crt == 2 ? GRE : RED ).pts3D( pB );
            draw.psc( 9 , crt == 3 ? GRE : RED ).pts3D( pC );
            draw.psc( 9 , crt == 4 ? GRE : RED ).pts3D( pD );

            // BASE CAM LINES

            draw.lwc(2,YEL).cct3D( wld2a , wld2b );
        }

        // DRAW SCREEN 1

        draw[1].clear();
        draw.psc(4,RED).object( board ).lwc(2,WHI).object( cam2 );

        // DRAW SCREEN 2

        draw[2].clear();
        draw.psc(4,RED).object( board ).lwc(2,WHI).object( cam1 );

        // DRAW SCREEN 3

        draw[3].clear();
        draw.ps(4).pts2D( img1 , clr ).pts2D( img2 , clr );
        if( img1.n() == img2.n() )
            draw.lwc(2,GRE).cct2D( img1 , img2 );

        // DRAW SCREEN 4

        draw[4].clear();
        draw[4].ps(8).pts2D( img1 , clr );

        // DRAW SCREEN 5

        draw[5].clear();
        draw[5].ps(8).pts2D( img2 , clr );

        draw.updateWindow(30);

        // CHANGE CONTROL

        if( draw.keys.tab )
            control = !control , halt(100);

        // CONTROL CAMERA

        if( control == 0 )
             draw.control( cam1 );
        else draw.control( cam2 );
    }

    return 0;
}


