#ifndef ROS_SEN2TOP_H
#define ROS_SEN2TOP_H

#include <cvpp/interfaces/cppture.h>

#include <cvpp/ros/ros_node.h>
#include <cvpp/ros/xsens/deviceclass.h>

#include <sensor_msgs/Imu.h>
#include <sensor_msgs/MagneticField.h>
#include <sensor_msgs/NavSatFix.h>

#include <xsens/xstime.h>
#include <xsens/xsdatapacket.h>
#include <xsens/xsportinfoarray.h>

#include <xcommunication/legacydatapacket.h>
#include <xcommunication/int_xsdatapacket.h>
#include <xcommunication/enumerateusbdevices.h>

namespace cvpp
{

class sen2top
{

protected:

    XsVector accel,magnet,gyro;
    XsQuaternion quaternion;

    ROSnode* node;

public:

    void run()
    {
        node = new ROSnode( "xsens" );

        Thread thread_sensors( &sen2top::run_sensors , *this );
        Thread thread_camera( &sen2top::run_camera , *this );

        thread_sensors.join();
        thread_camera.join();
    }

    void run_sensors()
    {
        unsigned pub_imu = node->addPublisher<sensor_msgs::Imu>( "/imu/data" );
        unsigned pub_mag = node->addPublisher<sensor_msgs::MagneticField>( "/imu/mag" );
//        unsigned pub_gps = node->addPublisher<sensor_msgs::NavSatFix>( "/android/navsat" );

        DeviceClass device;
        XsPortInfo mtPort( "/dev/ttyUSB0", XsBaud::numericToRate( 115200 ) );

        if( !device.openPort(mtPort) )
            std::runtime_error( "Could not open port. Aborting." );

        if( !device.gotoConfig() )
            std::runtime_error( "Could not put device into configuration mode. Aborting." );

        mtPort.setDeviceId( device.getDeviceId() );

        std::cout << "Found a device with id: " << mtPort.deviceId().toString().toStdString()
                  << " ( " << device.getProductCode().toStdString() << " )"
                  << " @ port: " << mtPort.portName().toStdString() << " , baudrate: " << mtPort.baudrate() << std::endl;

        XsOutputConfigurationArray configArray;

        XsOutputConfiguration quat( XDI_Quaternion , 10000 );
        configArray.push_back( quat );

        XsOutputConfiguration acc( XDI_Acceleration , 10000 );
        configArray.push_back( acc );

        XsOutputConfiguration mag( XDI_MagneticField , 10000 );
        configArray.push_back( mag );

        XsOutputConfiguration turn( XDI_RateOfTurn , 10000 );
        configArray.push_back( turn );

        if( !device.setOutputConfiguration( configArray ) )
            std::runtime_error("Could not configure MTmk4 device. Aborting.");

        if( !device.gotoMeasurement())
            std::runtime_error("Could not put device into measurement mode. Aborting.");

        XsByteArray data;
        XsMessageArray msgs;

        sensor_msgs::Imu imu_msg;
        sensor_msgs::MagneticField mag_msg;
        sensor_msgs::NavSatFix gps_msg;

        bool flag_imu,flag_mag,flag_gps;

        while( node->ok() )
        {
            flag_imu = flag_mag = flag_gps = false;

            device.readDataToBuffer( data );
            device.processBufferedData( data , msgs );

            for( XsMessageArray::iterator it = msgs.begin() ; it != msgs.end() ; ++it )
            {
                XsDataPacket packet;
                packet.setMessage( (*it) );
                packet.setDeviceId( mtPort.deviceId() );

                if( packet.containsOrientation() )
                {
                    quaternion = packet.orientationQuaternion();
                    imu_msg.orientation.w = quaternion.w();
                    imu_msg.orientation.x = quaternion.x();
                    imu_msg.orientation.y = quaternion.y();
                    imu_msg.orientation.z = quaternion.z();
                    flag_imu = true;
                }

                if( packet.containsCalibratedAcceleration() )
                {
                    accel = packet.calibratedAcceleration();
                    imu_msg.linear_acceleration.x = accel[0];
                    imu_msg.linear_acceleration.y = accel[1];
                    imu_msg.linear_acceleration.z = accel[2];
                    flag_imu = true;
                }

                if( packet.containsCalibratedGyroscopeData() )
                {
                    gyro = packet.calibratedGyroscopeData();
                    imu_msg.angular_velocity.x = gyro[0];
                    imu_msg.angular_velocity.y = gyro[1];
                    imu_msg.angular_velocity.z = gyro[2];
                    flag_imu = true;
                }

                if( packet.containsCalibratedMagneticField() )
                {
                    magnet = packet.calibratedMagneticField();
                    mag_msg.magnetic_field.x = magnet[0];
                    mag_msg.magnetic_field.y = magnet[1];
                    mag_msg.magnetic_field.z = magnet[2];
                    flag_mag = true;
                }

                if( flag_imu )
                {
                    imu_msg.header.stamp = ros::Time::now();
                    node->publish( pub_imu , imu_msg );
                }

                if( flag_mag )
                {
                    mag_msg.header.stamp = ros::Time::now();
                    node->publish( pub_mag , mag_msg );
                }

            }

            msgs.clear();
            XsTime::msleep(0);
        }

        std::cout << "Closing port..." << std::endl;
        device.close();
        std::cout << "Successful exit." << std::endl;
    }

    void run_camera()
    {
        Img3c raw;
        CPPture cap( 1 );

        unsigned pub_image = node->addImagePublisher( "/android/image" );

        while( node->ok() && cap.read( raw ) )
        {
            node->publishImage( pub_image , raw.cv() );
        }
    }

};

}

#endif
