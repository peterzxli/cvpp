#ifndef VSLAM_SYSTEM_VISUALIZATION_H
#define VSLAM_SYSTEM_VISUALIZATION_H

#include <ros/ros.h>
#include <sparse_bundle_adjustment/sba.h>

#include <visualization_msgs/Marker.h>
#include <geometry_msgs/PoseStamped.h>

namespace sba
{

void drawGraph(const SysSBA& sba ,
               const ros::Publisher& camera_pub ,
               const ros::Publisher& pose_pub   ,
               const ros::Publisher& point_pub  ,
               int decimation = 1 , int bicolor = 0 );

}

#endif
