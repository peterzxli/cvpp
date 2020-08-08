
#include <cvpp/interfaces/cpplot.h>
#include <cvpp/algorithms/dim_reduction/linear_pca.h>

using namespace cvpp;

// Update neighbours
void search( const KDtreef& tree , const Matf& pos , const int& k , const Matf& pts , Matf& nns )
{
    // SEARCH FOR NEIGHBOURS

    SSeqi idx; SSeqf dst;
    tree.knnSearch( pos , k , idx , dst );

    // UPDATE NEIGHBOUR LIST

    for( int i = 0 ; i < k ; ++i )
        nns.row(i) = pts.row( idx[0][i] );
}

int main()
{
    // DIMENSION VARIABLES

    int n = 1000 , d = 3 , k = 10 ;

    // CREATE DATASET

    Matf pts( n , d ); pts.setRand( 2 );
    Matf pos( 1 , d ); pos << 0.0 , 0.0 , 0.0;
    Matf nns( k , d );

    // CREATE KDTREE

    KDtreef tree( pts );
    search( tree , pos , k , pts , nns );

    // SANITY CHECK

    disp( "Sanity Check" , nns.sum() , -2.22788 );

    // CREATE PLOT INTERFACE

    CPPlot draw( "Window" );
    draw[0].set3Dplot().setAxes( pts );

    // CREATE BUFFERS

    unsigned buf_pts = draw.addBuffer3D( pts );

    // DRAW

    bool changed = false;
    while( draw.input() )
    {
        draw[0].clear().axes();             // Screen 0 (left)
        draw.psc(4,BLA).pts3D( buf_pts );   // Draw Points
        draw.psc(8,RED).pts3D( pos );       // Draw Position
        draw.psc(8,BLU).pts3D( nns );       // Draw Neighbours

        draw.updateWindow(30);              // Update window

        // CONTROL POSITION

        if( draw.keys.up )    { pos(0) += 0.1; changed = true; }
        if( draw.keys.down )  { pos(0) -= 0.1; changed = true; }
        if( draw.keys.left )  { pos(1) += 0.1; changed = true; }
        if( draw.keys.right ) { pos(1) -= 0.1; changed = true; }
        if( draw.keys.a )     { pos(2) += 0.1; changed = true; }
        if( draw.keys.z )     { pos(2) -= 0.1; changed = true; }

        // UPDATE NEIGHBOURS

        if( changed )
        {
            search( tree , pos , k , pts , nns );
            changed = false;
        }
    }

    return 0;
}
