
#include <cvpp/interfaces/cpplot.h>
#include <cvpp/algorithms/dim_reduction/kernel_pca.h>

using namespace cvpp;

int main()
{
    // LOAD DATASET

    Matd X( "../data/circles_X" );
    Matd Y( "../data/circles_Y" );

    // CREATE KERNEL PCA

    KernelPCA kpca( X , 2 , 15 );

    // SEPARATE CLASSES

    Matd X0 = X.sampleRows( Y == 0 );
    Matd X1 = X.sampleRows( Y == 1 );

    // PROJECT POINTS

    Matd Z  = kpca.project( X  );
    Matd Z0 = kpca.project( X0 );
    Matd Z1 = kpca.project( X1 );

    disp( "Sanity Check" , Z.sum()  , -2.18055e-15 );
    disp( "Sanity Check" , Z0.sum() , -13.7138 );
    disp( "Sanity Check" , Z1.sum() , +13.7138 );

    // CREATE PLOT INTERFACE

    CPPlot draw("Window",1,2);
    draw[0].set2Dplot().setAxes( X , 0.1 , 0.1 );
    draw[1].set2Dplot().setAxes( Z , 0.1 , 0.1 );

    // CREATE BUFFERS

    unsigned buf_x0 = draw.addBuffer2D( X0 );
    unsigned buf_x1 = draw.addBuffer2D( X1 );

    unsigned buf_z = draw.addBuffer2D( Z );
    unsigned buf_z0 = draw.addBuffer2D( Z0 );
    unsigned buf_z1 = draw.addBuffer2D( Z1 );

    // DRAW

    while( draw.input() )
    {
        draw[0].clear().axes();             // Screen 0 (left)

        draw.psc(4,RED).pts2D( buf_x0 );    // Draw class 0 (original)
        draw.psc(4,BLU).pts2D( buf_x1 );    // Draw class 1 (original)

        draw[1].clear().axes();             // Screen 1 (right)

        draw.psc(5,RED).pts2D( buf_z0 );    // Draw class 0 (projected)
        draw.psc(5,BLU).pts2D( buf_z1 );    // Draw class 1 (projected)
        draw.psc(3,BLA).pts2D( buf_z  );    // Draw both classes (projected)

        draw.updateWindow(30);              // Update window
    }

    return 0;
}
