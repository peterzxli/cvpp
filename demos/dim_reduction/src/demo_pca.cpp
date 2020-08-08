
#include <cvpp/interfaces/cpplot.h>
#include <cvpp/algorithms/dim_reduction/linear_pca.h>

using namespace cvpp;

int main()
{
    // CREATE DATASET

    Matd pts3 = MatWall3d( -0.1 , +0.1 , -1.0 , +1.0 , -1.0 , +1.0 , 10000 );
    pts3.RotateY( 60 ).RotateX( 45 );

    // PERFORM PCA

    LinearPCA pca( pts3 , 2 );
    Matd pts2 = pca.project( pts3 );

    // SANITY CHECK

    disp( "Sanity Check" , pts2.sum() , 9.80327e-14 );

    // CREATE PLOT INTERFACE

    CPPlot draw("Window" , 1  , 2 );
    draw[0].set3Dplot().setAxes( pts3 , 0.1 , 0.1 , 0.1 );
    draw[1].set2Dplot().setAxes( pts2 , 0.1 , 0.1 );

    // CREATE BUFFERS

    unsigned buf_pts3 = draw.addBuffer3D( pts3 );
    unsigned buf_pts2 = draw.addBuffer2D( pts2 );

    // DRAW

    while( draw.input() )
    {
        draw[0].clear().axes();             // Screen 0 (left)
        draw.psc(4,BLA).pts3D( buf_pts3 );  // Draw 3D points

        draw[1].clear().axes();             // Screen 1 (right)
        draw.psc(4,BLA).pts2D( buf_pts2 );  // Draw 2D points

        draw.updateWindow(30);              // Update window
    }

    return 0;
}
