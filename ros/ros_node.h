#ifndef ROS_NODE_H
#define ROS_NODE_H

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

#include <cvpp/containers/matrix.h>
#include <cvpp/containers/image.h>

#include <std_msgs/Empty.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/UInt8MultiArray.h>

#include <geometry_msgs/Vector3.h>

using msgImg3c = sensor_msgs::ImageConstPtr;
using msgMatf = std_msgs::Float32MultiArray;
using msgMatc = std_msgs::UInt8MultiArray;
using msgFloat = std_msgs::Float32;

namespace cvpp
{

class ROSnode
{

protected:

    ros::NodeHandle* node;

    Seq< ros::Publisher > pubs;
    Seq< ros::Subscriber > subs;

    Seq< image_transport::Publisher > img_pubs;
    Seq< image_transport::Subscriber > img_subs;

    image_transport::ImageTransport* img_trans;

public:

    ROSnode( const String& );
    ~ROSnode();

    void spin() { ros::spinOnce(); }
    const bool ok() { return ros::ok(); }

    TPL_T void addSubscriber( const String& , void function( const T& ) );
    TPL_TU void addSubscriber( const String& , void (U::*)( const T& ) , U* );

    TPL_T void addImageSubscriber( const String& , void function( const T& ) );
    TPL_TU void addImageSubscriber( const String& , void (U::*)( const T& ) , U* );

    TPL_T int addPublisher( const String& );
    int addImagePublisher( const String& );

    int addFloatPublisher( const String& str ) { return addPublisher<msgFloat>( str ); }

    int addMatfPublisher( const String& str ) { return addPublisher<msgMatf>( str ); }
    int addMatcPublisher( const String& str ) { return addPublisher<msgMatc>( str ); }

    TPL_T void publish( const int& , const T& ) const;
    void publish( const int& , const sensor_msgs::ImagePtr& ) const;

    void publishEmpty( const int& n ) const
    { publish( n , std_msgs::Empty() ); }

    void publishString( const int& n , const String& str )
    { std_msgs::String msg; msg.data = str; publish( n , msg ); }

    TPL_T void publishVector3( const int& n , const T& x , const T& y , const T& z )
    { geometry_msgs::Vector3 msg; msg.x = x; msg.y = y; msg.z = z; publish( n , msg ); }

    void publishImage( const int& n , const CV& cv ) const
    { std_msgs::Header header; header.stamp = ros::Time::now();
      publish( n , cv_bridge::CvImage( header , "bgr8" , cv ).toImageMsg() ); }

    void publishImage( const int& n , const Img3c& img ) const
    { publishImage( n , img.cv() ); }

    void publishFloat( const int& n , const float& val ) const
    { msgFloat msg; msg.data = val; publish( n , msg ); }

    void publishMatrix( const int& n , const Matf& mat ) const
    { msgMatf msg; mat.toROSmsg( msg ); publish( n , msg ); }

    void publishMatrix( const int& n , const Matc& mat ) const
    { msgMatc msg; mat.toROSmsg( msg ); publish( n , msg ); }

};

}

#include "./ros_node_src.h"

#endif
