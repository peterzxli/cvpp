
#include <cvpp/interfaces/cpplot.h>
#include <cvpp/objects/object_camera.h>

using namespace cvpp;

void createDataset()
{
    Seq<Camera> cameras;
    Pts3f feats; Vec7f poses; Vec4f projs;

    float jmp = 0.5;
    int nx = 10 , ny = 5 , nz = 3 , nc = 5 ;
    Pt3f start( 5.0 , - 0.25 , 0.25 );

    forLOOPijk( nx , ny , nz )
            feats.push( start + jmp * Pt3f( k , - i , j ) );

    Posef start_pose , finish_pose;
    start_pose.setPos(  0.0 ,   0.0 , 0.0 );
    finish_pose.setPos( 0.0 , - 3.0 , 0.0 );

    forLOOPi( nc )
    {
        double perc = double( i ) / double( nc - 1 );

        cameras.push_back( Camera( "data/calib.txt" ) );
        cameras.back().setPose( start_pose , finish_pose , perc );

        poses.push( Arr7f( cameras.back().pose->px() ,
                           cameras.back().pose->py() ,
                           cameras.back().pose->pz() ,
                           cameras.back().pose->qw() ,
                           cameras.back().pose->qx() ,
                           cameras.back().pose->qy() ,
                           cameras.back().pose->qz() ) );
    }

    Pts2f imgs;
    forLOOPi( feats.n() )
    {
        forLOOPj( cameras.size() )
        {
            imgs = cameras[j].w2u( feats(i) );
            imgs.mat() += 0.5;

            if( !imgs.empty() )
                projs.push( Arr4f( i , j , imgs[0].x , imgs[0].y ) );
        }
    }

    feats.save( "data/feats_raw.txt" );
    poses.save( "data/poses_raw.txt"  );
    projs.save( "data/projs_raw.txt"  );

    float noise_feats = 0.3;

    forLOOPi( feats.n() )
    {
        feats[i].x += randf( noise_feats );
        feats[i].y += randf( noise_feats );
        feats[i].z += randf( noise_feats );
    }

    float noise_trans =  0.4;
    float noise_rot   = 25.0;

    forLOOPii( 1 , poses.n() )
    {
        cameras[i].pose->moveX( randf( noise_trans ) );
        cameras[i].pose->moveY( randf( noise_trans ) );
        cameras[i].pose->moveZ( randf( noise_trans ) );

        cameras[i].pose->rotateX( randf( noise_rot ) );
        cameras[i].pose->rotateY( randf( noise_rot ) );
        cameras[i].pose->rotateZ( randf( noise_rot ) );

        poses[i] = Arr7f( cameras[i].pose->px() ,
                          cameras[i].pose->py() ,
                          cameras[i].pose->pz() ,
                          cameras[i].pose->qw() ,
                          cameras[i].pose->qx() ,
                          cameras[i].pose->qy() ,
                          cameras[i].pose->qz() );
    }

    feats.save( "data/feats_nsy.txt" );
    poses.save( "data/poses_nsy.txt" );
}

int main()
{
    createDataset();

    Pts3f feats_raw( "data/feats_raw.txt" );
    Pts3f feats_nsy( "data/feats_nsy.txt" );

    Matf poses_raw( "data/poses_raw.txt" );
    Matf poses_nsy( "data/poses_nsy.txt" );

    Seq<Camera*> cameras_raw , cameras_nsy;

    CPPlot draw( "Window" );
    draw[0].set3Dworld().setViewer( -5.70305 , -3.53051 , 3.56151 ,
                                    -4.78986 , -3.35889 , 3.19188 );

    forLOOPi( poses_raw.r() )
    {
        cameras_raw.push_back( new Camera( "data/calib.txt" ) );
        cameras_raw.back()->axesOn();

        cameras_raw.back()->pose->setPos(
                    poses_raw(i,0) , poses_raw(i,1) , poses_raw(i,2) );
        cameras_raw.back()->pose->setOrient(
                    poses_raw(i,3) , poses_raw(i,4) , poses_raw(i,5) , poses_raw(i,6) );
    }

    forLOOPi( poses_nsy.r() )
    {
        cameras_nsy.push_back( new Camera( "data/calib.txt" ) );
        cameras_nsy.back()->axesOn();

        cameras_nsy.back()->pose->setPos(
                    poses_nsy(i,0) , poses_nsy(i,1) , poses_nsy(i,2) );
        cameras_nsy.back()->pose->setOrient(
                    poses_nsy(i,3) , poses_nsy(i,4) , poses_nsy(i,5) , poses_nsy(i,6) );
    }

    while( draw.input() )
    {
        draw[0].clear();

        forLOOPi( cameras_raw.size() )
            draw.lwc(2,WHI).object( cameras_raw[i] );
        forLOOPi( cameras_nsy.size() )
            draw.lwc(2,RED).object( cameras_nsy[i] );

        draw.psc(4,WHI).pts3D( feats_raw );
        draw.psc(4,RED).pts3D( feats_nsy );

        forLOOPi( feats_raw.n() )
            draw.psc(2,YEL).line3D( feats_raw[i] ,
                                    feats_nsy[i] );
        forLOOPi( cameras_raw.size() )
            draw.psc(2,YEL).line3D( cameras_raw[i]->pose->getPosPt() ,
                                    cameras_nsy[i]->pose->getPosPt() );

        draw.updateWindow(30);
    }

    return 0;
}
