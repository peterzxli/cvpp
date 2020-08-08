
#include <iostream>
#include "lib/icpPointToPlane.h"
#include "lib/icpPointToPoint.h"

#include <cvpp/interfaces/cpplot.h>

using namespace std;
using namespace cvpp;

int main (int argc, char** argv)
{
    int32_t dim = 3;
    int32_t numM = 10000;
    int32_t numT = 2500;

    double* M = (double*)calloc(3*numM,sizeof(double));
    double* T = (double*)calloc(3*numT,sizeof(double));

    Matd MM( numM , dim , M );
    Matd TT( numT , dim , T );

    {
        int32_t k=0;
        for (double x=-2; x<2; x+=0.04) {
            for (double y=-2; y<2; y+=0.04) {
                double z=5*x*exp(-x*x-y*y);
                M[k*3+0] = x;
                M[k*3+1] = y;
                M[k*3+2] = z;
                k++;
            }
        }
    }

    {
        int32_t k=0;
        for (double x=-2; x<2; x+=0.08) {
            for (double y=-2; y<2; y+=0.08) {
                double z=5*x*exp(-x*x-y*y);
                T[k*3+0] = x-0.5;
                T[k*3+1] = y-1;
                T[k*3+2] = z-1.5;
                k++;
            }
        }
    }

    MM.RotateZ( 10 );
    MM.RotateY( 25 );

    MM.AddRand( 0.1 );
    TT.AddRand( 0.1 );

    MatICP R = MatICP::eye(3);
    MatICP t(3,1);

//    IcpPointToPoint icp(M,num,dim);
    IcpPointToPlane icp(M,numM,dim);
    icp.fit(T,numT,R,t,-1);

    cout << "R:" << endl << R << endl << endl;
    cout << "t:" << endl << t << endl << endl;

    Matd RR( 3 , 3 , *R.val );
    Matd tt( 1 , 3 , *t.val );

    Matd FF = TT * RR.t() + tt;

    CPPlot draw( "Window" );
    draw[0].set3Dworld();

    int buf_M = draw.addBuffer3D( MM );
    int buf_T = draw.addBuffer3D( TT );
    int buf_F = draw.addBuffer3D( FF );

    while( draw.input() )
    {
        draw[0].clear();
        draw.psc(3,RED).pts3D( buf_M );
        draw.psc(3,BLU).pts3D( buf_T );
        draw.psc(4,WHI).pts3D( buf_F );
        draw.updateWindow(30);
    }

    free(M);
    free(T);

    return 0;
}

