
#include <ros/ros.h>

#include "../../sparse_bundle_adjustment/include/sparse_bundle_adjustment/sba.h"
#include "../../sparse_bundle_adjustment/include/sparse_bundle_adjustment/visualization.h"

#include <time.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/PoseStamped.h>

#include <cvpp/interfaces/cpplot.h>
#include <cvpp/objects/object_camera.h>

using namespace sba;
using namespace std;
using namespace cvpp;

void setupSBA( SysSBA& sys )
{
    // Calibration Matrix

    frame_common::CamParams cam_params;
    cam_params.fx = 430.0 ; cam_params.fy = 430.0 ;
    cam_params.cx = 320.0 ; cam_params.cy = 240.0 ;
    cam_params.tx =   0.0 ;

    // Load Data

    Matf mat_points( "data/data_points_nsy.txt" );
    Matf mat_poses(  "data/data_poses_nsy.txt"  );
    Matf mat_projs(  "data/data_projs_raw.txt"  );

    // Store Points

    vector< Point , Eigen::aligned_allocator<Point> > points;
    forLOOPi( mat_points.r() )
    {
        points.push_back( Point( - mat_points(i,1) ,
                                 - mat_points(i,2) ,
                                   mat_points(i,0) , 1.0 ) );

        disp( "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Points " , i );
        disp( points[i] );
    }

    // Noisy Points

    unsigned short seed = 10;//(unsigned short)time( NULL );
    seed48( &seed );

    for( int i = 0 ; i < points.size() ; i++ )
    {
        Vector4d temppoint = points[i];
//        temppoint.x() += drand48() - 0.5;
//        temppoint.y() += drand48() - 0.5;
//        temppoint.z() += drand48() - 0.5;
        sys.addPoint( temppoint );
    }

    // Store Cameras

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

        disp( "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Cameras" , i );
        disp( trans );
//        disp( rot );
    }

    // Noisy Cameras

    double transscale = 1.0;
    double rotscale = 0.5;

    for( int i = 1 ; i < sys.nodes.size() ; i++ )
    {
        Vector4d temptrans = sys.nodes[i].trans;
        Quaterniond tempqrot = sys.nodes[i].qrot;

//        temptrans.x() += transscale * (drand48() - 0.5 );
//        temptrans.y() += transscale * (drand48() - 0.5 );
//        temptrans.z() += transscale * (drand48() - 0.5 );

        temptrans.x() += 0.1;
        temptrans.y() += 0.1;
        temptrans.z() += 0.1;

//        tempqrot.x() += rotscale * ( drand48() - 0.5 );
//        tempqrot.y() += rotscale * ( drand48() - 0.5 );
//        tempqrot.z() += rotscale * ( drand48() - 0.5 );
//        tempqrot.normalize();

        tempqrot.x() += 0.2;
        tempqrot.y() += 0.2;
        tempqrot.z() += 0.2;
        tempqrot.normalize();

        sys.nodes[i].trans = temptrans;
        sys.nodes[i].qrot = tempqrot;

        sys.nodes[i].normRot();
        sys.nodes[i].setTransform();
        sys.nodes[i].setProjection();
        sys.nodes[i].setDr(true);
    }

    // Store Projections

    forLOOPi( mat_projs.r() )
    {
        Vector2d proj( mat_projs(i,2) , mat_projs(i,3) );
        sys.addMonoProj( mat_projs(i,1) , mat_projs(i,0) , proj );

//        disp( mat_projs(i,0) , mat_projs(i,1) , mat_projs(i,2) , mat_projs(i,3) );
    }

}

void processSBA(ros::NodeHandle node)
{
    ros::Publisher cam_marker_pub =
            node.advertise<visualization_msgs::Marker>( "/sba/cameras" , 100 );
    ros::Publisher point_marker_pub =
            node.advertise<visualization_msgs::Marker>( "/sba/points" , 100 );
    ros::Publisher pose_pub =
            node.advertise<geometry_msgs::PoseStamped>( "/sba/poses" , 100 );

    ros::spinOnce();
    
    SysSBA sys;
    setupSBA( sys );
    
    ROS_INFO( "Cameras (nodes): %d, Points: %d" ,
              (int)sys.nodes.size() , (int)sys.tracks.size() );

    sys.doSBA( 10 , 1e-3 , SBA_SPARSE_CHOLESKY );
    
    int npts = sys.tracks.size();

    ROS_INFO( "Bad projs (> 10 pix): %d, Cost without: %f" ,
              (int)sys.countBad( 10.0 ) , sqrt( sys.calcCost( 10.0 ) / npts ) );
    ROS_INFO( "Bad projs (>  5 pix): %d, Cost without: %f" ,
              (int)sys.countBad(  5.0 ) , sqrt( sys.calcCost( 5.0 ) / npts ) );
    ROS_INFO( "Bad projs (>  2 pix): %d, Cost without: %f" ,
              (int)sys.countBad(  2.0 ) , sqrt( sys.calcCost( 2.0 ) / npts ) );
    
    ROS_INFO( "Cameras (nodes): %d, Points: %d" ,
              (int)sys.nodes.size() , (int)sys.tracks.size() );
}

int main(int argc, char **argv)
{
//    ros::init( argc , argv , "sba_system_setup" );
//    ros::NodeHandle node;

//    processSBA( node );
//    ros::spinOnce();

    Pts3f points_raw( "data/data_points_raw.txt" );
    Pts3f points_nsy( "data/data_points_nsy.txt" );
    Matf poses_raw( "data/data_poses_raw.txt" );
    Matf poses_nsy( "data/data_poses_nsy.txt" );
    Matf projs_raw( "data/data_projs_raw.txt" );

    int n_cams = poses_raw.r();
    int n_pts = points_raw.n();

    STD<Camera*> cameras_raw , cameras_nsy , cameras_est ;

    CPPlot draw( "Window" );
    draw[0].set3Dworld().setViewer( -6.00 , -1.32 , 1.06 ,
                                    -5.00 , -1.32 , 1.06 );

/////////////////////////////////////////////////////////////////////////////////////

    // Raw Cameras

    forLOOPi( poses_raw.r() )
    {
        cameras_raw.push_back( new Camera( "data/calib.txt" ) );
        cameras_raw.back()->pose->setPos(
                    poses_raw(i,0) , poses_raw(i,1) , poses_raw(i,2) );
        cameras_raw.back()->pose->setOrient(
                    poses_raw(i,3) , poses_raw(i,4) , poses_raw(i,5) , poses_raw(i,6) );
        cameras_raw.back()->axesOn();
    }

/////////////////////////////////////////////////////////////////////////////////////

    SysSBA sys;
    setupSBA( sys );

/////////////////////////////////////////////////////////////////////////////////////

    // Estimated Points (Before)

    Pts3f points_est;
    forLOOPi( n_pts )
    {
        points_est.push( Pt3f(   sys.tracks[i].point(2) ,
                               - sys.tracks[i].point(0) ,
                               - sys.tracks[i].point(1) ) );
    }

    // Estimated Cameras (Before)

    cameras_nsy.clear();
    forLOOPi( n_cams )
    {
        Eigen::Vector4d trans = sys.nodes[i].trans;
        Eigen::Quaterniond quat = sys.nodes[i].qrot;

        cameras_nsy.push_back( new Camera( "data/calib.txt" ) );
        cameras_nsy.back()->pose->setPos( trans(2) , - trans(0) , - trans(1) );
        cameras_nsy.back()->pose->setOrient( quat.w() , quat.z() , - quat.x() , - quat.y() );
        cameras_nsy.back()->axesOn();

        disp( "################################################### Refined Cameras" , i );
        disp( trans );
        disp( quat.w() , quat.x() , quat.y() , quat.z() );
    }

/////////////////////////////////////////////////////////////////////////////////////

    sys.doSBA( 10 , 1e-3 , SBA_SPARSE_CHOLESKY );

/////////////////////////////////////////////////////////////////////////////////////

    // Estimated Points (After)

    points_est.reset();// Pts3f points_est;
    forLOOPi( n_pts )
    {
        points_est.push( Pt3f(   sys.tracks[i].point(2) ,
                               - sys.tracks[i].point(0) ,
                               - sys.tracks[i].point(1) ) );
    }

    // Estimated Cameras (After)

    forLOOPi( n_cams )
    {
        Eigen::Vector4d trans = sys.nodes[i].trans;
        Eigen::Quaterniond quat = sys.nodes[i].qrot;

        cameras_est.push_back( new Camera( "data/calib.txt" ) );
        cameras_est.back()->pose->setPos( trans(2) , - trans(0) , - trans(1) );
        cameras_est.back()->pose->setOrient( quat.w() , quat.z() , - quat.x() , - quat.y() );
        cameras_est.back()->axesOn();

        disp( "################################################### Refined Cameras" , i );
        disp( trans );
        disp( quat.w() , quat.x() , quat.y() , quat.z() );
    }

    double scl_pose_raw = dist( cameras_raw.back()->getPosPt() , cameras_raw.front()->getPosPt() );
    double scl_pose_est = dist( cameras_est.back()->getPosPt() , cameras_est.front()->getPosPt() );
    double scl_pose = scl_pose_raw / scl_pose_est;

    forLOOPi( n_cams ) cameras_est[i]->pose->scale( scl_pose );

    double scl_point_raw = dist( cameras_raw.front()->getPosPt() , points_raw[0] );
    double scl_point_est = dist( cameras_est.front()->getPosPt() , points_est[0] );
    double scl_point = scl_point_raw / scl_point_est;

    points_est.mat() *= scl_point;

/////////////////////////////////////////////////////////////////////////////////////

    SPts2f pimgs( n_cams );
    SPts3f pprojs_raw1( n_cams ) , pprojs_raw2( n_cams );
    SPts3f pprojs_nsy1( n_cams ) , pprojs_nsy2( n_cams );
    SPts3f pprojs_est1( n_cams ) , pprojs_est2( n_cams );

    forLOOPi( n_cams )
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

        draw.psc(5,WHI).pts3D( points_raw );
        forLOOPi( n_cams ) draw.lwc(2,WHI).object( cameras_raw[i] );

        if( show == 1 )
        {
            draw.psc(5,RED).pts3D( points_nsy );
            forLOOPi( n_cams )
                draw.lwc(2,RED).object( cameras_nsy[i] ).psc(6,RED).pts3D( cameras_nsy[i]->wpoints() );
            forLOOPi( n_pts )
                draw.psc(1,YEL).line3D( points_raw[i] , points_nsy[i] );
            forLOOPi( n_cams )
                draw.psc(1,YEL).line3D( cameras_raw[i]->pose->getPosPt() ,
                                        cameras_nsy[i]->pose->getPosPt() );
        }

        if( show == 2 )
        {
            draw.psc(6,GRE).pts3D( points_est );
            forLOOPi( n_cams )
                draw.lwc(2,GRE).object( cameras_est[i] ).psc(6,GRE).pts3D( cameras_est[i]->wpoints() );
            forLOOPi( n_pts )
                draw.psc(1,YEL).line3D( points_raw[i] , points_est[i] );
            forLOOPi( n_cams )
                draw.psc(1,YEL).line3D( cameras_raw[i]->pose->getPosPt() ,
                                        cameras_est[i]->pose->getPosPt() );
        }

        forLOOPi( n_cams )
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
