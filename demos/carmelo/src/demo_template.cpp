
#include <cvpp/containers/vector.h>
#include <cvpp/containers/image.h>

#include <cvpp/interfaces/cpplot.h>

using namespace cvpp;

int main( int argc, char** argv )
{
    Img3c img( argv[1] ); img = img.XYZscale();
    Img3c tpl( argv[2] ); tpl = tpl.XYZscale();

    Img1f res = img.matchTemplate( tpl );

    Pt2i mtc = res.minPt();

    Pts2f pts;
    forLOOPmat( res )
        if( res(r,c) < 0.05 )
            pts.push( Pt2f( c , r ) );

    CPPlot draw("Window",ULHW( 0 , 0 , 360 , 640 ) );
    draw[0].set2Dimage();

    unsigned tex_img = draw.addTexture( img );

    int r = 20 , c = 40 ;

    String str_pos = "../data/positive/positive_";
    String str_neg = "../data/negative/negative_";
    int cnt_pos = 0 , cnt_neg = 0;

    while( draw.input() )
    {
        draw[0].clear().useTexture( tex_img );

        draw.lwc(2,BLU).quad2D( pts , tpl );
        draw.lwc(2,RED).quad2D( mtc , tpl );

        draw.updateWindow(30);

        if( draw.keys.p )
        {
            disp("Adding positive sample");
            img.b( draw.mousePos().x - r / 2 ,
                   draw.mousePos().y - c / 2 , r , c ).save(
                        str_pos + std::to_string( cnt_pos++ ) + ".jpg" );
            halt(100);
        }

        if( draw.keys.n )
        {
            disp("Adding negative sample");
            img.b( draw.mousePos().x - r / 2 ,
                   draw.mousePos().y - c / 2 , r , c ).save(
                        str_neg + std::to_string( cnt_neg++ ) + ".jpg" );
            halt(100);
        }
    }

    return 0;
}
