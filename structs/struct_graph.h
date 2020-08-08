#ifndef GRAPH_H
#define GRAPH_H

#include "../auxiliar/macros.h"
#include "../auxiliar/definitions.h"

#include "../structs/struct_lsd.h"

#include "../properties/pose.h"
#include "../objects/object_camera.h"
#include "../objects/object_keyframe.h"

#include "../ros/extra_msgs/keyframeMsg.h"
#include "../ros/extra_msgs/keyframeGraphMsg.h"

namespace cvpp
{

class Graph
{

protected:

    Camera* cam;
    CPPlot* draw;

    Seq<Posef> poses;
    Seq<Keyframe> keyframes;
    Seq<Constraint> constraints;

    Seq<Img3c> frames;
    Seq<int> ids;

    Mati flag;

public:

    unsigned bufferIdx;
    bool hasBuffer;

public:

    Graph()
    {
    }

    ~Graph()
    {
    }

    const int n_poses() const { return poses.size();  }
    const int n_keyframes() const { return keyframes.size(); }
    const int n_constraints() const { return constraints.size(); }

    Keyframe& cKeyframe() { return keyframes[bufferIdx]; }

    Seq<Posef>& getPoses() { return poses;  }
    Seq<Keyframe>& getKeyframes() { return keyframes; }
    Seq<Constraint>& getConstraints() { return constraints; }
    Seq<Img3c>& getFrames() { return frames; }

    Posef& getPose( const int& idx ) { return poses[idx];  }
    Keyframe& getKeyframe(const int& idx ) { return keyframes[idx]; }
    Constraint& getConstraint( const int& idx ) { return constraints[idx]; }
    Img3c& getFrame( const int& idx ) { return frames[idx]; }

    const Posef& getConstraintToPose( const int& idx ) const { return *keyframes[ constraints[idx].to ].pose; }
    const Posef& getConstraintFromPose( const int& idx ) const { return *keyframes[ constraints[idx].from ].pose; }

    void setBuffer() { cKeyframe().startDataBuffer(); cKeyframe().startColorBuffer(); hasBuffer = false; }
    void updateBuffer() { cKeyframe().updateDataBuffer(); hasBuffer = false; }

    void initialise( Camera& cam , CPPlot& draw )
    {
        this->cam = &cam;
        this->draw = &draw;

        hasBuffer = false;

        poses.reserve(10000);
        frames.reserve(10000);

        ids.reserve(1000);
        keyframes.reserve(1000);
        constraints.reserve(1000);
    }

    void addFrame( const Img3c& img )
    {
        frames.resize( frames.size() + 1 );
        img.cv().copyTo( frames.back().cv() );
        frames.back().update();

    }

    void addPose( const lsd_slam_viewer::keyframeMsg& msg )
    {
        poses.resize( poses.size() + 1 );
        poses.back().setPose( msg.camToWorld[4] , msg.camToWorld[5] , msg.camToWorld[6] ,
                              msg.camToWorld[3] , msg.camToWorld[0] , msg.camToWorld[1] , msg.camToWorld[2] );
    }

    void addKeyframe( const lsd_slam_viewer::keyframeGraphMsg& msg ,
                                  Constraint* constraint , GraphKeyframe* keyframe )
    {
        for( int i = 0 ; i < msg.numFrames ; i++ )
        {
            keyframes[i].pose->setPose( keyframe[i].pose[4] , keyframe[i].pose[5] , keyframe[i].pose[6] ,
                                        keyframe[i].pose[3] , keyframe[i].pose[0] , keyframe[i].pose[1] , keyframe[i].pose[2] );
        }

        Constraint* constraint_ptr;

        for( int i = 0 ; i < msg.numConstraints ; i++ )
        {
            if( i < constraints.size() )
            {
                constraint_ptr = &constraints[i];
            }
            else
            {
                constraints.resize( constraints.size() + 1 );
                constraint_ptr = &constraints.back();
            }

            constraint_ptr->to = constraint[i].to;
            constraint_ptr->from = constraint[i].from;

            for( int j = 0 ; j < ids.size() ; j++ )
            {
                if( constraint_ptr->to == ids[j] ) constraint_ptr->to = j;
                if( constraint_ptr->from == ids[j] ) constraint_ptr->from = j;
            }
        }
    }

    void addPointcloud( const lsd_slam_viewer::keyframeMsg& msg ,
                                    GraphPointcloud* pointcloud )
    {
        int id = -1;
        for( unsigned i = 0 ; i < ids.size() ; i++ )
        {   if( ids[i] == msg.id )
            {
                id = i;
                break;
            }
        }

        if( id < 0 )
        {
            ids.push_back( msg.id );
            keyframes.resize( keyframes.size() + 1 );
            keyframes.back().initialise( *cam );
            id = n_keyframes() - 1;

            keyframes[id].pose->setPose( msg.camToWorld[4] , msg.camToWorld[5] , msg.camToWorld[6] ,
                                        msg.camToWorld[3] , msg.camToWorld[0] , msg.camToWorld[1] , msg.camToWorld[2] );
        }

        Keyframe* keyframe;
        keyframe = &keyframes[id];

        float my_absTH = 0.1;
        float my_scaledTH = 0.001;
        float my_minNearSupport = 7;
        float my_scale = keyframe->pose->getOrient().norm();

        unsigned my_sparsifyFactor = 1;

        unsigned width = cam->width() , height = cam->height();

        keyframe->mean.reset( height , width );
        keyframe->var.reset( height , width );

        keyframe->cmean.reset( height , width , 0 );
        keyframe->cvar.reset( height , width , 0 );

        keyframe->frame.reset( height , width );
        keyframe->frame = frames[msg.id];

        #pragma omp parallel for
        for( unsigned i = 0 ; i < height ; i++ )
        {   for( unsigned j = 0 ; j < width ; j++ )
            {
                unsigned coord = j + i * width;
                keyframe->mean(i,j) = pointcloud[coord].depth_mean;
                keyframe->var(i,j)  = pointcloud[coord].depth_var;
            }
        }

        float fxi = cam->matPi()(0,0) , fyi = cam->matPi()(1,1);
        float cxi = cam->matPi()(0,2) , cyi = cam->matPi()(1,2);

        flag.reset( height , width ).setVal(0);

        #pragma omp parallel for
        for( int i = 1 ; i < height - 1 ; i++ )
        {   for( int j = 1 ; j < width - 1 ; j++ )
            {
                float inv_mean = keyframe->mean(i,j);
                float inv_var  = keyframe->var(i,j);

                if( inv_mean <= 0 )
                    continue;
                if( my_sparsifyFactor > 1 && rand() % my_sparsifyFactor != 0 )
                    continue;

                float mean = 1.0 / inv_mean;
                float mean4 = pow( mean , 4 );

                if( inv_var * mean4 > my_scaledTH )
                    continue;
                if( inv_var * mean4 * pow( my_scale , 2 ) > my_absTH )
                    continue;

                float diff;
                if( my_minNearSupport > 1 )
                {
                    unsigned nearSupport = 0;
                    for( int di = -1 ; di <= 1 ; di++ )
                    {   for( int dj = -1 ; dj <= 1 ; dj++ )
                        {   if( keyframe->mean( i + di , j + dj ) > 0 )
                            {
                                diff = keyframe->mean( i + di , j + dj ) - inv_mean;
                                if( pow( diff , 2 ) < 2 * inv_var )
                                    nearSupport++;
                            }
                        }
                    }

                    if( nearSupport < my_minNearSupport )
                        continue;
                }

                flag( i , j ) = 1;
            }
        }

        unsigned qty = flag.sum();
        keyframe->points().resize( qty );
        keyframe->variance().resize( qty );
        keyframe->color().resize( qty );

        float r,g,b;

        unsigned cnt = 0;
        for( int i = 1 ; i < height - 1 ; i++ )
        {   for( int j = 1 ; j < width - 1 ; j++ )
            {   if( flag( i , j ) )
                {
                    float inv_mean = keyframe->mean(i,j) , mean = 1.0 / inv_mean;
                    float inv_var  = keyframe->var(i,j) , var = 1.0 / inv_var;

                    keyframe->points()[cnt] = Pt3f( ( (float)j * fxi + cxi ) * mean ,
                                                    ( (float)i * fyi + cyi ) * mean ,
                                                                               mean );

                    keyframe->color()[cnt] = Pt3f( (float)frames[msg.id](i,j,2) / 255.0 ,
                                                   (float)frames[msg.id](i,j,1) / 255.0 ,
                                                   (float)frames[msg.id](i,j,0) / 255.0 );

                    keyframe->variance()[cnt] = var;

                    RGBlsd( inv_mean , r , g , b );

                    keyframe->cmean(i,j,0) = 255 - r;
                    keyframe->cmean(i,j,1) = 255 - g;
                    keyframe->cmean(i,j,2) = 255 - b;

                    RGBlsd( - 0.5 * log10( inv_var ) , r , g , b );

                    keyframe->cvar(i,j,0) = r;
                    keyframe->cvar(i,j,1) = g;
                    keyframe->cvar(i,j,2) = b;

                    cnt++;
                }
            }
        }

        bufferIdx = id;
        hasBuffer = true;
    }

};

}

#endif
