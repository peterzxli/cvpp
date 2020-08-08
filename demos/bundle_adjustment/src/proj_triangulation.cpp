
#include <cvpp/interfaces/cpplot.h>
#include <cvpp/objects/object_camera.h>
#include <cvpp/modules/cvis.h>

using namespace cvpp;

int main()
{
    int n_cams = 2;
    String calib_file = "../data/calib.txt";

    SeqPts2f feats( n_cams );
    Vec4f projs( "../data/projs_raw.txt" );
    forLOOPi( projs.n() )
        feats[ projs[i][1] ].push( Pt2f( projs[i][2] , projs[i][3] ) );

    SeqImg3c images( n_cams );
    images[0].load( "../data/DJI_0064.JPG" );
    images[1].load( "../data/DJI_0067.JPG" );

    CPPlot draw("Window",1,2);
    draw[0].set3Dworld().setViewer( -355.712 , -46.9418 , 428.125 ,
                                    -354.842 , -46.8486 , 427.642 );
    draw[1].set2Dimage().setResolution( 1500 , 2000 );

    Seqi texs( n_cams );
    Seq<Camera*> cams( n_cams );
    forLOOPi( n_cams )
    {
        texs[i] = draw.addTexture( images[i] );
        cams[i] = new Camera( calib_file , 30 );
    }

    float x0 = 0.0 , y0 = 0.0 , z0 = 100.0 ;
    cams[0]->pose->setPose( z0 , x0 , y0 ,
                            0.99987 , 0.00011 , 0.00005 , -0.01616 );

    float x1 = -26.49 , y1 =  58.07 , z1 = 100.00;
    cams[1]->pose->setPose( z1 , x1 , y1 ,
                            0.99987 , 0.00003 , 0.00003 , -0.01609 );

    SeqPts3f triang1( n_cams );
    SeqPts3f triang2( n_cams );

    Pts3f results( 41 );

    int show = 1;
    bool change = true;
    while( draw.input() )
    {
        if( change == true )
        {
            forLOOPi( n_cams )
            {
                triang1[i] = cams[i]->u2w( feats[i] ,   39.9 );
                triang2[i] = cams[i]->u2w( feats[i] , 2000.0 );
            }

            forLOOPi( 41 )
            {
                results[i] = cvis::triangulate( cams[0]->pose->getPosPt() , triang2[0][i] ,
                                                cams[1]->pose->getPosPt() , triang2[1][i] );
            }

            results.save("../data/feats_nsy.txt");

            cams[1]->pose->print();
            change = false; halt(100);
        }

        draw[0].clear();
        forLOOPi( n_cams )
            draw.bindTexture( texs[i] ).lwc( 2 , show == i ? RED : WHI ).object( cams[i] );

        forLOOPi( n_cams )
        {
            draw.psc(6,RED).pts3D( triang1[i] );
            forLOOPj( triang2[i].n() )
                draw.lwc(1,YEL).line3D( cams[i]->getPosPt() , triang2[i][j] );
        }

        forLOOPi( n_cams )
        {
            draw.psc(6,RED).pts3D( triang1[i] );
            forLOOPj( triang2[i].n() )
                draw.lwc(1,YEL).line3D( cams[i]->getPosPt() , triang2[i][j] );
        }

        forLOOPi( 41 )
        {
            draw.psc(8,RED).pts3D( results );
        }

        draw[1].clear();
        draw.useTexture( texs[show] );
        draw.psc(6,RED).pts2D( feats[show] );

        draw.updateWindow(30);

//        if( draw.keys.up   ) { show = std::min( show + 1  , n_cams - 1 ) ; halt(100); }
//        if( draw.keys.down ) { show = std::max( show - 1 ,       0     ) ; halt(100); }

        if( draw.keys.up    ) { cams[1]->pose->moveZ(   5 ); change = true; }
        if( draw.keys.down  ) { cams[1]->pose->moveZ( - 5 ); change = true; }
        if( draw.keys.right ) { cams[1]->pose->moveY( - 5 ); change = true; }
        if( draw.keys.left  ) { cams[1]->pose->moveY(   5 ); change = true; }
    }

    return 0;
}
