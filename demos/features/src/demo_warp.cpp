
#include <cvpp/interfaces/cpplot.h>

using namespace cvpp;

int main()
{
    // IMAGE SIZE

    double r = 480 , c = 640 ;

    // LOAD IMAGE

    Img3c img1( "../data/gandalf.jpg" );
    img1.Resize( r , c );

    //SET POINTS IN FIRST IMAGE

    Pts2f pts1;
    pts1.push( Pt2f( 0 , 0 ) ).push( Pt2f( c , 0 ) )
        .push( Pt2f( 0 , r ) ).push( Pt2f( c , r ) );

    // SET POINTS IN SECOND IMAGE

    Pts2f pts2;
    pts2.push( Pt2f( 1*c/4 , 1*r/4 ) ).push( Pt2f( 2*c/4 , 1*r/4 ) )
        .push( Pt2f( 1*c/4 , 3*r/4 ) ).push( Pt2f( 3*c/4 , 3*r/4 ) );

    // WARP IMAGE 2

    Img3c img2 = img1.warp( pts1 , pts2 );

    // START DRAW INTERFACE

    CPPlot draw( "Window" , 1 , 2 );
    draw[0].set2Dimage().setResolution( img1 );
    draw[1].set2Dimage().setResolution( img2 );

    // CREATE TEXTURES

    unsigned tex1 = draw.addTexture( img1 );
    unsigned tex2 = draw.addTexture( img2 );

    int n = 0;
    bool change = false;
    while( draw.input() )
    {
        // DRAW IMAGES

        draw[0].clear().useTexture( tex1 ).psc(5,RED).pts2D( pts1 );
        draw[1].clear().useTexture( tex2 ).psc(5,RED).pts2D( pts2 );

        // UPDATE FRAME

        draw.updateWindow(30);

        // CONTROL POINT

        if( draw.keys.up    ) { pts2.mat()(n,1) -= 5 , change = true; }
        if( draw.keys.down  ) { pts2.mat()(n,1) += 5 , change = true; }
        if( draw.keys.left  ) { pts2.mat()(n,0) -= 5 , change = true; }
        if( draw.keys.right ) { pts2.mat()(n,0) += 5 , change = true; }

        // CHANGE POINT

        if( draw.keys.tab ) { n = ++n % 4; halt(100); }

        // IF THERE IS A CHANGE

        if( change )
        {
            img2.Warp( img1 , pts1 , pts2 );
            draw.updTexture( tex2 , img2 );
            change = false;
        }
    }

    return 0;
}
