
#include <cvpp/interfaces/cpplot.h>
#include <cvpp/objects/object_camera.h>

#include "sba.h"

using namespace sba;
using namespace std;
using namespace cvpp;

SysSBA setupSBA()
{
    SysSBA sys;

    Camera calib( "data/calib.txt" );
    Matf mat_calib = calib.matK();

    frame_common::CamParams cam_params;
    cam_params.fx = mat_calib(0,0) ; cam_params.fy = mat_calib(1,1) ;
    cam_params.cx = mat_calib(0,2) ; cam_params.cy = mat_calib(1,2) ;
    cam_params.tx =   0.0 ;

    Matf mat_feats( "data/feats_nsy.txt" );
    Matf mat_poses( "data/poses_nsy.txt"  );
    Matf mat_projs( "data/projs_raw.txt"  );

    forLOOPi( mat_feats.r() )
    {
        sys.addPoint( Point( - mat_feats(i,1) ,
                             - mat_feats(i,2) ,
                               mat_feats(i,0) , 1.0 )  );
    }

    forLOOPi( mat_poses.r() )
    {
        Vector4d trans( - mat_poses(i,1) ,
                        - mat_poses(i,2) ,
                          mat_poses(i,0) , 1.0 );

        Quaterniond rot(   mat_poses(i,3) ,
                         - mat_poses(i,5) ,
                         - mat_poses(i,6) ,
                           mat_poses(i,4) );

        sys.addNode( trans , rot , cam_params , false );
    }

    forLOOPi( mat_projs.r() )
    {
        Vector2d proj( mat_projs(i,2) , mat_projs(i,3) );
        sys.addMonoProj( mat_projs(i,1) , mat_projs(i,0) , proj );
    }

    return sys;
}

int main(int argc, char **argv)
{
    Pts3f feats_raw( "data/feats_raw.txt" );
    Matf  poses_raw( "data/poses_raw.txt" );
    Matf  projs_raw( "data/projs_raw.txt" );

    int n_poses = poses_raw.r();
    int n_feats = feats_raw.n();

    CPPlot draw( "Window" );
    draw[0].set3Dworld().setViewer( -6.00 , -1.32 , 1.06 ,
                                    -5.00 , -1.32 , 1.06 );

/////////////////////////////////////////////////////////////////////////////////////

    Seq<Camera*> cameras_raw;
    forLOOPi( poses_raw.r() )
    {
        cameras_raw.push_back( new Camera( "data/calib.txt" ) );
        cameras_raw.back()->pose->setPos( poses_raw(i,0) , poses_raw(i,1) , poses_raw(i,2) );
        cameras_raw.back()->pose->setOrient( poses_raw(i,3) , poses_raw(i,4) , poses_raw(i,5) , poses_raw(i,6) );
        cameras_raw.back()->axesOn();
    }

/////////////////////////////////////////////////////////////////////////////////////

    SysSBA sys = setupSBA();

/////////////////////////////////////////////////////////////////////////////////////

    Pts3f feats_nsy;
    forLOOPi( n_feats )
    {
        feats_nsy.push( Pt3f(   sys.tracks[i].point(2) ,
                              - sys.tracks[i].point(0) ,
                              - sys.tracks[i].point(1) ) );
    }

    Seq<Camera*> cameras_nsy;
    forLOOPi( n_poses )
    {
        Eigen::Vector4d trans = sys.nodes[i].trans;
        Eigen::Quaterniond quat = sys.nodes[i].qrot;

        cameras_nsy.push_back( new Camera( "data/calib.txt" ) );
        cameras_nsy.back()->pose->setPos( trans(2) , - trans(0) , - trans(1) );
        cameras_nsy.back()->pose->setOrient( quat.w() , quat.z() , - quat.x() , - quat.y() );
        cameras_nsy.back()->axesOn();
    }

/////////////////////////////////////////////////////////////////////////////////////

    sys.doSBA( 10 , 1e-3 , SBA_SPARSE_CHOLESKY );

/////////////////////////////////////////////////////////////////////////////////////

    Pts3f feats_est;
    forLOOPi( n_feats )
    {
        feats_est.push( Pt3f(   sys.tracks[i].point(2) ,
                              - sys.tracks[i].point(0) ,
                              - sys.tracks[i].point(1) ) );
    }

    Seq<Camera*> cameras_est;
    forLOOPi( n_poses )
    {
        Eigen::Vector4d trans = sys.nodes[i].trans;
        Eigen::Quaterniond quat = sys.nodes[i].qrot;

        cameras_est.push_back( new Camera( "data/calib.txt" ) );
        cameras_est.back()->pose->setPos( trans(2) , - trans(0) , - trans(1) );
        cameras_est.back()->pose->setOrient( quat.w() , quat.z() , - quat.x() , - quat.y() );
        cameras_est.back()->axesOn();
    }

    double scl_pose_raw = dist( cameras_raw.back()->getPosPt() , cameras_raw.front()->getPosPt() );
    double scl_pose_est = dist( cameras_est.back()->getPosPt() , cameras_est.front()->getPosPt() );
    double scl_pose = scl_pose_raw / scl_pose_est;

    forLOOPi( n_poses ) cameras_est[i]->pose->scale( scl_pose );

    double scl_point_raw = dist( cameras_raw.front()->getPosPt() , feats_raw[0] );
    double scl_point_est = dist( cameras_est.front()->getPosPt() , feats_est[0] );
    double scl_point = scl_point_raw / scl_point_est;

    feats_est.mat() *= scl_point;

/////////////////////////////////////////////////////////////////////////////////////

    SeqPts2f pimgs( n_poses );
    SeqPts3f pprojs_raw1( n_poses ) , pprojs_raw2( n_poses );
    SeqPts3f pprojs_nsy1( n_poses ) , pprojs_nsy2( n_poses );
    SeqPts3f pprojs_est1( n_poses ) , pprojs_est2( n_poses );

    forLOOPi( n_poses )
    {
        forLOOPj( projs_raw.r() )
            if( projs_raw(j,1) == i )
                pimgs[i].push( Pt2f( projs_raw(j,2) , projs_raw(j,3) ) );

        pprojs_raw1[i] = cameras_raw[i]->u2w( pimgs[i] , 0.1 );
        pprojs_raw2[i] = cameras_raw[i]->u2w( pimgs[i] , 6.0 );

        pprojs_nsy1[i] = cameras_nsy[i]->u2w( pimgs[i] , 0.1 );
        pprojs_nsy2[i] = cameras_nsy[i]->u2w( pimgs[i] , 6.0 );

        pprojs_est1[i] = cameras_est[i]->u2w( pimgs[i] , 0.1 );
        pprojs_est2[i] = cameras_est[i]->u2w( pimgs[i] , 6.0 );
    }

    int show = 0;
    bool lines = false;

    while( draw.input() )
    {
        draw[0].clear();

        draw.psc(5,WHI).pts3D( feats_raw );
        forLOOPi( n_poses ) draw.lwc(2,WHI).object( cameras_raw[i] );

        if( show == 1 )
        {
            draw.psc(5,RED).pts3D( feats_nsy );
            forLOOPi( n_poses )
                draw.lwc(2,RED).object( cameras_nsy[i] ).psc(6,RED).pts3D( cameras_nsy[i]->wpoints() );
            forLOOPi( n_feats )
                draw.psc(1,YEL).line3D( feats_raw[i] , feats_nsy[i] );
            forLOOPi( n_poses )
                draw.psc(1,YEL).line3D( cameras_raw[i]->pose->getPosPt() ,
                                        cameras_nsy[i]->pose->getPosPt() );
        }

        if( show == 2 )
        {
            draw.psc(6,GRE).pts3D( feats_est );
            forLOOPi( n_poses )
                draw.lwc(2,GRE).object( cameras_est[i] ).psc(6,GRE).pts3D( cameras_est[i]->wpoints() );
            forLOOPi( n_feats )
                draw.psc(1,YEL).line3D( feats_raw[i] , feats_est[i] );
            forLOOPi( n_poses )
                draw.psc(1,YEL).line3D( cameras_raw[i]->pose->getPosPt() ,
                                        cameras_est[i]->pose->getPosPt() );
        }

        forLOOPi( n_poses )
        {
            switch( show )
            {
            case 0:
                if( lines )
                {
                    draw.psc(4,RED).pts3D( pprojs_raw1[i] );
                    forLOOPj( pprojs_raw2[i].n() )
                        draw.psc(1,YEL).line3D( cameras_raw[i]->pose->getPosPt() ,
                                                pprojs_raw2[i][j] );
                }
                break;
            case 1:
                if( lines )
                {
                    draw.psc(4,RED).pts3D( pprojs_nsy1[i] );
                    forLOOPj( pprojs_nsy2[i].n() )
                        draw.psc(1,YEL).line3D( cameras_nsy[i]->pose->getPosPt() ,
                                                pprojs_nsy2[i][j] );
                }
                break;
            case 2:
                if( lines )
                {
                    draw.psc(4,RED).pts3D( pprojs_est1[i] );
                    forLOOPj( pprojs_est2[i].n() )
                        draw.psc(1,YEL).line3D( cameras_est[i]->pose->getPosPt() ,
                                                pprojs_est2[i][j] );
                }
                break;
            }

        }

        draw.updateWindow(30);

        if( draw.keys.enter ) { show = ++show % 3 ; halt(100) ; }
        if( draw.keys.space ) { lines = !lines ; halt(100) ; }
    }

    return 0;
}
