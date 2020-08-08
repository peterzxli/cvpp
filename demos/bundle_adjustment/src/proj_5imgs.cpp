
#include <cvpp/interfaces/cpplot.h>
#include <cvpp/objects/object_camera.h>
#include <cvpp/modules/cvis.h>

#include "sba.h"

using namespace sba;
using namespace cvpp;

Seq<Img3c>
loadImages()
{
    Seq<Img3c> imgs( 5 );

    imgs[0].load( "../data/5imgs/DJI_0114.JPG" );
    imgs[1].load( "../data/5imgs/DJI_0115.JPG" );
    imgs[2].load( "../data/5imgs/DJI_0116.JPG" );
    imgs[3].load( "../data/5imgs/DJI_0117.JPG" );
    imgs[4].load( "../data/5imgs/DJI_0118.JPG" );

    return imgs;
}

void
load2Dpoints( const String& str1 , const String& str2 ,
              const Matf& mat , const int& a , const int& b , int& cnt , int& qty )
{
    Matf tmp1( str1 ) , tmp2( str2 );

    forLOOPi( tmp1.r() )
    {
        mat.row(qty++) << a , cnt , tmp1(i,0) , tmp1(i,1);
        mat.row(qty++) << b , cnt , tmp2(i,0) , tmp2(i,1);
        cnt++;
    }
}

Matf
load2Dpoints()
{
    int cnt = 0 , qty = 0;
    Matf mat( 10000 , 4 );

    load2Dpoints( "../data/5imgs/0_co_2D_01_0_.txt" ,
                  "../data/5imgs/0_co_2D_01_1_.txt" , mat , 0 , 1 , cnt , qty );
    load2Dpoints( "../data/5imgs/1_co_2D_02_0_.txt" ,
                  "../data/5imgs/1_co_2D_02_2_.txt" , mat , 0 , 2 , cnt , qty );
    load2Dpoints( "../data/5imgs/2_co_2D_03_0_.txt" ,
                  "../data/5imgs/2_co_2D_03_3_.txt" , mat , 0 , 3 , cnt , qty );
    load2Dpoints( "../data/5imgs/3_co_2D_04_0_.txt" ,
                  "../data/5imgs/3_co_2D_04_4_.txt" , mat , 0 , 4 , cnt , qty );
    load2Dpoints( "../data/5imgs/4_co_2D_12_1_.txt" ,
                  "../data/5imgs/4_co_2D_12_2_.txt" , mat , 1 , 2 , cnt , qty );
    load2Dpoints( "../data/5imgs/5_co_2D_13_1_.txt" ,
                  "../data/5imgs/5_co_2D_13_3_.txt" , mat , 1 , 3 , cnt , qty );
    load2Dpoints( "../data/5imgs/6_co_2D_14_1_.txt" ,
                  "../data/5imgs/6_co_2D_14_4_.txt" , mat , 1 , 4 , cnt , qty );
    load2Dpoints( "../data/5imgs/7_co_2D_23_2_.txt" ,
                  "../data/5imgs/7_co_2D_23_3_.txt" , mat , 2 , 3 , cnt , qty );
    load2Dpoints( "../data/5imgs/8_co_2D_24_2_.txt" ,
                  "../data/5imgs/8_co_2D_24_4_.txt" , mat , 2 , 4 , cnt , qty );
    load2Dpoints( "../data/5imgs/9_co_2D_34_3_.txt" ,
                  "../data/5imgs/9_co_2D_34_4_.txt" , mat , 3 , 4 , cnt , qty );

    mat.KeepU( qty );
    return mat;
}

SysSBA setupSBA( const Seq<Camera*>& cams ,
                 const Matf& pts2 , const Matf& pts3 )
{
    SysSBA sys;

    Matf mat_calib = cams[0]->matK();
    frame_common::CamParams cam_params;
    cam_params.fx = mat_calib(0,0) ; cam_params.fy = mat_calib(1,1) ;
    cam_params.cx = mat_calib(0,2) ; cam_params.cy = mat_calib(1,2) ;
    cam_params.tx = 0.0 ;

    forLOOPi( pts3.r() )
    {
        sys.addPoint( Point( - pts3(i,2) ,
                             - pts3(i,3) ,
                               pts3(i,1) , 1.0 )  );
    }

    forLOOPi( cams.size() )
    {
        cams[i]->pose->print();
        Vector4d trans( - cams[i]->pose->py() ,
                        - cams[i]->pose->pz() ,
                          cams[i]->pose->px() , 1.0 );

        Quaterniond rot(   cams[i]->pose->qw() ,
                         - cams[i]->pose->qy() ,
                         - cams[i]->pose->qz() ,
                           cams[i]->pose->qx() );

        sys.addNode( trans , rot , cam_params , false );
    }

    forLOOPi( pts2.r() )
    {
        Vector2d proj( pts2(i,2) , pts2(i,3) );
        sys.addMonoProj( pts2(i,0) , pts2(i,1) , proj );
    }

    return sys;
}

int main( int argc , char **argv )
{
    // Load Data
    Matf pts2 = load2Dpoints();
    SeqImg3c imgs = loadImages();
    int m = imgs.size();

    // Separate Points

    cvpp::Matrix<Pts2f> tabPts1( m , m ) , tabPts2( m , m );
    cvpp::Matrix<Veci> tabIndex( m , m );

    forLOOPiii( 0 , pts2.r() , 2 )
    {
        int a = pts2(i+0,0) , b = pts2(i+1,0);
        tabPts1(a,b).push( Pt2f( pts2(i+0,2) , pts2(i+0,3) ) );
        tabPts2(a,b).push( Pt2f( pts2(i+1,2) , pts2(i+1,3) ) );
        tabIndex(a,b).push( pts2(i,1) );
    }

    // Draw

    CPPlot draw( "Window" , ULHW( 2 * 480 , 3 * 640 ) , 2 , 3 );
    draw[0].set3Dworld().setViewer( -180.64 , 124.599 , -202.370 ,
                                    -179.66 , 124.793 , -202.319 );
    draw[1].set2Dimage().setResolution( imgs[0] );
    draw[2].set2Dimage().setResolution( imgs[1] );
    draw[3].set2Dimage().setResolution( imgs[2] );
    draw[4].set2Dimage().setResolution( imgs[3] );
    draw[5].set2Dimage().setResolution( imgs[4] );

    // Cameras

    float d = 99.5;
    Matf poses( "../data/5imgs/poses.txt" );
    Seq<Camera*> cams( imgs.size() );
    forLOOPi( cams.size() )
    {
        cams[i] = new Camera( "../data/5imgs/calib.txt" , d );
        cams[i]->setPos( poses(i,2) , poses(i,1) , poses(i,0) );
        cams[i]->pose->setOrient( poses(i,5) , poses(i,3) , poses(i,4) );
    }

    cvpp::Matrix<Pts3f> tabNear1( m , m ) , tabNear2( m , m );
    cvpp::Matrix<Pts3f> tabFar1( m , m ) , tabFar2( m , m );
    cvpp::Matrix<Pts3f> tabTriang( m , m );

    forLOOPi( tabPts1.r() )
    {   forLOOPjj( i + 1 , tabPts1.c() )
        {
            tabNear1(i,j) = cams[i]->u2w( tabPts1(i,j) , 0.9 * d );
            tabFar1(i,j)  = cams[i]->u2w( tabPts1(i,j) , 3.0 * d );
            tabNear2(i,j) = cams[j]->u2w( tabPts2(i,j) , 0.9 * d );
            tabFar2(i,j)  = cams[j]->u2w( tabPts2(i,j) , 3.0 * d );

            tabTriang(i,j).reset( tabFar1(i,j).n() );
            forLOOPk( tabTriang(i,j).n() )
                tabTriang(i,j)[k] = cvis::triangulate( cams[i]->getPosPt() , tabFar1(i,j)[k] ,
                                                       cams[j]->getPosPt() , tabFar2(i,j)[k] );
        }
    }

    int cnt = 0;
    Matf pts3( pts2.r() / 2 , 4 );
    forLOOPi( tabTriang.r() )
    {   forLOOPjj( i + 1 , tabTriang.c() )
        {   forLOOPk( tabTriang(i,j).n() )
            {
                pts3.row( cnt++ ) << tabIndex(i,j)[k] , tabTriang(i,j)[k].x ,
                                                        tabTriang(i,j)[k].y ,
                                                        tabTriang(i,j)[k].z ;
            }
        }
    }

    // Textures

    Seqi texs( imgs.size() );
    forLOOPi( imgs.size() )
        texs[i] = draw.addTexture( imgs[i] );

    // Loop

    int ii , jj , n = 1;
    bool change = true;
    while( draw.input() )
    {
        if( change )
        {
            ii = n / m ; jj = n % m;
            change = false; disp( ii , jj );
        }

        draw[0].clear();
        forLOOPi( imgs.size() )
        {
            draw.bindTexture( texs[i] );
            draw.clr(RGBint(i)).object( cams[i] );

//            draw.lwc(2,COLOR(ii));
//            forLOOPi( tabFar1(ii,jj).n() )
//                draw.line3D( cams[ii]->getPosPt() , tabFar1(ii,jj)[i] );
//            draw.psc(7,COLOR(ii)).pts3D( tabNear1(ii,jj) );

//            draw.lwc(2,COLOR(jj));
//            forLOOPi( tabFar2(ii,jj).n() )
//                draw.line3D( cams[jj]->getPosPt() , tabFar2(ii,jj)[i] );
//            draw.psc(7,COLOR(jj)).pts3D( tabNear2(ii,jj) );

//            draw.psc(7,CYA).pts3D( tabTriang(ii,jj) );
        }

        forLOOPi( imgs.size() )
            draw[i+1].clear().useTexture( texs[i] );

        draw[ii+1].psc(5,RGBint(ii)).pts2D( tabPts1(ii,jj) );
        draw[jj+1].psc(5,RGBint(jj)).pts2D( tabPts2(ii,jj) );

        draw.updateWindow(30);

        if( draw.keys.up   && n < pow(m,2) - 1 ) { n++; change = true; halt(100); }
        if( draw.keys.down && n > 0            ) { n--; change = true; halt(100); }

        if( draw.keys.enter )
        {
            pts2.save("pts2.txt");
            pts3.save("pts3.txt");

            SysSBA sys = setupSBA( cams , pts2 , pts3 );
            sys.doSBA( 10 , 1e-3 , SBA_SPARSE_CHOLESKY );

            forLOOPi( pts3.r() )
            {
                pts3(i,1) =   sys.tracks[i].point(2);
                pts3(i,2) = - sys.tracks[i].point(0);
                pts3(i,3) = - sys.tracks[i].point(1);
            }

            forLOOPi( cams.size() )
            {
                Eigen::Vector4d trans = sys.nodes[i].trans;
                Eigen::Quaterniond quat = sys.nodes[i].qrot;

                cams[i]->pose->setPos( trans(2) , - trans(0) , - trans(1) );
                cams[i]->pose->setOrient( quat.w() , quat.z() , - quat.x() , - quat.y() );

                cams[i]->pose->print();
            }

            halt(100);
        }
    }

    return 0;
}
