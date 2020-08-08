#ifndef ROS_AND2TOP_H
#define ROS_AND2TOP_H

#include <cvpp/interfaces/cppture.h>

#include <cvpp/ros/ros_node.h>
#include <cvpp/network/socket/udp_sub.h>

#include <sensor_msgs/Imu.h>
#include <sensor_msgs/MagneticField.h>
#include <sensor_msgs/NavSatFix.h>


namespace cvpp
{

class and2top
{

protected:

    ROSnode* node;

public:

    void run()
    {
        node = new ROSnode( "android" );

        Thread thread_sensors( &and2top::run_sensors , *this );
        Thread thread_camera( &and2top::run_camera , *this );

        thread_sensors.join();
        thread_camera.join();
    }

    void run_sensors()
    {
        UDPsub udp( "5555" );

        unsigned imu = node->addPublisher<sensor_msgs::Imu>( "/android/inertial" );
        unsigned mag = node->addPublisher<sensor_msgs::MagneticField>( "/android/magnetic" );
        unsigned gps = node->addPublisher<sensor_msgs::NavSatFix>( "/android/navsat" );

        int qty;
        float split[20];

        sensor_msgs::Imu imu_msg;
        sensor_msgs::MagneticField mag_msg;
        sensor_msgs::NavSatFix gps_msg;

        bool flag_imu,flag_mag,flag_gps;

        while( node->ok() )
        {
            flag_imu = flag_mag = flag_gps = false;

            udp.listen();
            qty = tokenFloat( udp.buffer , split );

            forLOOPiii( 0 , qty , 4 )
            {
                if( split[i] == 1 )
                {
                    gps_msg.latitude  = split[i+1];
                    gps_msg.longitude = split[i+2];
                    gps_msg.altitude  = split[i+3];
                    flag_gps = true;
                }

                if( split[i] == 3 )
                {
                    imu_msg.linear_acceleration.x = split[i+1];
                    imu_msg.linear_acceleration.y = split[i+2];
                    imu_msg.linear_acceleration.z = split[i+3];
                    flag_imu = true;
                }

                if( split[i] == 4 )
                {
                    imu_msg.angular_velocity.x = split[i+1];
                    imu_msg.angular_velocity.y = split[i+2];
                    imu_msg.angular_velocity.z = split[i+3];
                    flag_imu = true;
                }

                if( split[i] == 5 )
                {
                    mag_msg.magnetic_field.x = split[i+1];
                    mag_msg.magnetic_field.y = split[i+2];
                    mag_msg.magnetic_field.z = split[i+3];
                    flag_mag = true;
                }
            }

            if( flag_gps )
            {
                gps_msg.header.stamp = ros::Time::now();
                node->publish( gps , gps_msg );
            }

            if( flag_imu )
            {
                imu_msg.header.stamp = ros::Time::now();
                node->publish( imu , imu_msg );
            }

            if( flag_mag )
            {
                mag_msg.header.stamp = ros::Time::now();
                node->publish( mag , mag_msg );
            }
        }
    }

    void run_camera()
    {
        Img3c raw;
        CPPture cap( 2 );

        unsigned pub_image = node->addImagePublisher( "/android/image" );

        while( node->ok() && cap.read( raw ) )
        {
            node->publishImage( pub_image , raw.cv() );
        }
    }

};

}

#endif
