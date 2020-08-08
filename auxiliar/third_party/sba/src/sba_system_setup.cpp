
#include <ros/ros.h>

#include "../../sparse_bundle_adjustment/include/sparse_bundle_adjustment/sba.h"
#include "../../sparse_bundle_adjustment/include/sparse_bundle_adjustment/visualization.h"

#include <time.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/PoseStamped.h>

using namespace sba;
using namespace std;

void setupSBA(SysSBA &sys)
{
    frame_common::CamParams cam_params;
    cam_params.fx = 430.0;
    cam_params.fy = 430.0;
    cam_params.cx = 320.0;
    cam_params.cy = 240.0;
    cam_params.tx =   0.0;

    int maxx = 640;
    int maxy = 480;

    int npts_x = 10;
    int npts_y = 5;
    
    double plane_width    = 5.0;
    double plane_height   = 2.5;
    double plane_distance = 5.0;

    vector< Point , Eigen::aligned_allocator<Point> > points;

    int cnt = 0;
    for( int ix = 0 ; ix < npts_x ; ix++ )
        for( int iy = 0 ; iy < npts_y ; iy++ )
        {
            points.push_back( Point( plane_width  / npts_x * ( ix + 0.5 ) ,
                                   - plane_height / npts_y * ( iy + 0.5 ) ,
                                     plane_distance , 1.0 ) );
            std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Points " << cnt << std::endl;
            std::cout << points[cnt++] << std::endl;
        }

    int nnodes = 5;
    double path_length = 3.0;
    
    for( int i = 0 ; i < nnodes ; i++ )
    {
        Vector4d trans( i / ( nnodes - 1.0 ) * path_length , 0 , 0 , 1 );

        Quaterniond rot( 1 , 0 , 0 , 0 );
        rot.normalize();

        std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Cameras " << i << std::endl;
        std::cout << trans << std::endl;
//        std::cout << rot << std::endl;

        sys.addNode( trans , rot , cam_params , false );
    }

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
    
    Vector2d proj;
    
    for( int i = 0 ; i < points.size() ; i++)
    {   for( int j = 0 ; j < sys.nodes.size() ; j++)
        {
            sys.nodes[j].setProjection();
            sys.nodes[j].project2im( proj , points[i] );

            if( proj.x() > 0 && proj.x() < maxx &&
                proj.y() > 0 && proj.y() < maxy )
            {
                sys.addMonoProj( j , i , proj );
//                std::cout << i << " " << j << " " << proj.x() << " " << proj.y() << std::endl;
            }
        }
    }
    
    double transscale = 1.0;
    double rotscale = 0.5;
    
    for( int i = 1 ; i < sys.nodes.size() ; i++ )
    {
        Vector4d temptrans = sys.nodes[i].trans;
        Quaterniond tempqrot = sys.nodes[i].qrot;

        temptrans.x() += 0.1;
        temptrans.y() += 0.1;
        temptrans.z() += 0.1;

        tempqrot.x() += 0.2;
        tempqrot.y() += 0.2;
        tempqrot.z() += 0.2;
        tempqrot.normalize();

//        temptrans.x() += transscale * (drand48() - 0.5 );
//        temptrans.y() += transscale * (drand48() - 0.5 );
//        temptrans.z() += transscale * (drand48() - 0.5 );

//        tempqrot.x() += rotscale * ( drand48() - 0.5 );
//        tempqrot.y() += rotscale * ( drand48() - 0.5 );
//        tempqrot.z() += rotscale * ( drand48() - 0.5 );
//        tempqrot.normalize();

        sys.nodes[i].trans = temptrans;
        sys.nodes[i].qrot = tempqrot;

        sys.nodes[i].normRot();
        sys.nodes[i].setTransform();
        sys.nodes[i].setProjection();
        sys.nodes[i].setDr(true);
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
    
    ROS_INFO( "Waiting before publishing topics..." );
    ros::Duration( 2.0 ).sleep();
    
    SysSBA sys;
    setupSBA( sys );
    
    ROS_INFO( "Cameras (nodes): %d, Points: %d" ,
              (int)sys.nodes.size() , (int)sys.tracks.size() );

    drawGraph( sys , cam_marker_pub , point_marker_pub , pose_pub );
    ros::spinOnce();
    
    ROS_INFO("Waiting before starting SBA..." );
    ros::Duration( 10.0 ).sleep();

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

    drawGraph( sys , cam_marker_pub , point_marker_pub , pose_pub );
    ros::spinOnce();

    ROS_INFO( "Waiting before ending program..." );
    ros::Duration( 5.0 ).sleep();
}

int main(int argc, char **argv)
{
    ros::init( argc , argv , "sba_system_setup" );
    ros::NodeHandle node;
    
    processSBA( node );
    ros::spinOnce();

    return 0;
}
