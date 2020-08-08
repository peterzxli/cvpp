
#include <iostream>
#include "lib/icpPointToPlane.h"
#include "lib/icpPointToPoint.h"

#include <cvpp/interfaces/cpplot.h>

using namespace std;
using namespace cvpp;

class ICP
{
protected:

    IcpPointToPlane *icp;

public:

    ICP( const Matd& M )
    {
        icp = new IcpPointToPlane( M.raw_data() , M.r() , M.c() );
    }

    ~ICP()
    {
        delete icp;
    }

    void fit( const Matd& M , Matd& R , Matd& t )
    {
        if( R.empty() ) R.reset( 3 , 3 ).setIdentity();
        if( t.empty() ) t.reset( 1 , 3 ).setVal(0);

        MatICP RR( 3 , 3 , R.raw_data() );
        MatICP tt( 3 , 1 , t.raw_data() );

        icp->fit( M.raw_data() , M.r() , RR , tt , -1 );

        R = Matd( 3 , 3 , *RR.val );
        t = Matd( 1 , 3 , *tt.val );
    }

    Matd fit( const Matd& M )
    {
        Matd R , t;
        fit( M , R , t );
        return M * R.t() + t;
    }

};

int main (int argc, char** argv)
{
    int dim = 3;
    int numM = 10000;
    int numT =  2500;

    int k;

    Matd M( numM , dim ); k = 0;
    for( double x = -2.0 ; x <= 2.0 ; x += 0.04 )
    {   for( double y = -2.0 ; y <= 2.0 ; y += 0.04 )
        {
            double z = 5 * x * exp( - ( pow( x , 2.0 ) + pow( y , 2.0 ) ) );
            M.row( k++ ) << x , y , z ;
        }
    }

    Matd T( numT , dim ); k = 0;
    for( double x = -2.0 ; x <= 2.0 ; x += 0.08 )
    {   for( double y = -2.0 ; y <= 2.0 ; y += 0.08 )
        {
            double z = 5 * x * exp( - ( pow( x , 2.0 ) + pow( y , 2.0 ) ) );
            T.row( k++ ) << x , y , z ;
        }
    }

    M.RotateZ( 10 );
    M.RotateY( 25 );

    M.AddRand( 0.1 );
    T.AddRand( 0.1 );

    M += Mat13d( 1.0 , 1.5 , 2.0 );

    ICP icp( M );

//    Matd R,t; icp.fit( T , R , t );
//    Matd F = T * R.t() + t;
    Matd F = icp.fit( T );

    CPPlot draw( "Window" );
    draw[0].set3Dworld();

    int buf_M = draw.addBuffer3D( M );
    int buf_T = draw.addBuffer3D( T );
    int buf_F = draw.addBuffer3D( F );

    while( draw.input() )
    {
        draw[0].clear();
        draw.psc(3,RED).pts3D( buf_M );
        draw.psc(3,BLU).pts3D( buf_T );
        draw.psc(4,WHI).pts3D( buf_F );
        draw.updateWindow(30);
    }

//    free(M);
//    free(T);

    return 0;
}

