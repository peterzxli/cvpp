#ifndef STRUCT_SCREEN_H
#define STRUCT_SCREEN_H

#include <cvpp/structs/struct_borders2.h>
#include <cvpp/properties/pose.h>

namespace cvpp
{

class Screen
{

protected:

public:

    unsigned type,view;
    Borders2f borders,resolution,resoriginal;
    Scalar background;

    String title;

    bool lockX,lockY,lockZ,changed;
    unsigned nTickX,nTickY,nTickZ;

    float fov , fx , fy , cx , cy ;
    float w , h , far , near ;

    Pointer< Posef > viewer;
    Posef view_original;

    bool isCalibrated;
    double perspective[16];

public:

    bool isLocked() const { return lockX && lockY && lockZ; }

    Screen()
    {
        fov = 45; view = 0;
        nTickX = nTickY = nTickZ = 5;

        fx = 600 , fy = 600 , cx = 640 , cy = 480 ;
        w  = 1280 , h = 960 , far = 1000 , near = 0.001 ;

        isCalibrated = false;
        lockX = lockY = lockZ = false;
        changed = false;

        viewer = std::make_shared< Posef >();
    }

    Screen( const Screen& scr )
    {
        *this = scr;
    }

    Screen& operator=( const Screen& scr )
    {
        this->fov = scr.fov;
        this->view = scr.view;

        this->lockX = scr.lockX;
        this->lockY = scr.lockY;
        this->lockZ = scr.lockZ;

        this->viewer = scr.viewer;
    }

    void initialise( const Borders2f& borders ,
                           const Scalar& background )
    {
        this->borders = borders;
        this->background = background;
    }

    void calibrate()
    {
        perspective[0] = 2 * fx / w ;
        perspective[5] = 2 * fy / h ;

        perspective[1] = perspective[2] = perspective[3] = 0 ;
        perspective[4] = perspective[6] = perspective[7] = 0 ;

        perspective[8] = 2.0 * ( cx / w ) - 1.0 ;
        perspective[9] = 2.0 * ( cy / h ) - 1.0 ;

        perspective[10] = - ( far + near ) / ( far - near ) ;
        perspective[11] = - 1.0 ;

        perspective[12] = perspective[13] = perspective[15] = 0;
        perspective[14] = - 2.0 * far * near / ( far - near );

        isCalibrated = true;
    }

    TPL_T void remOffset( Pts2<T>* pts ) const
    {
        (*pts) -= resolution.lu();
        pts->mat().c(0) *= borders.w() / resolution.w();
        pts->mat().c(1) *= borders.h() / resolution.h();
        (*pts) += borders.lu();
    }

    TPL_T Pts2<T> remOffset( const Pts2<T>& pts ) const
    {
        Pts2<T> tmp = pts.clone();
        remOffset( &tmp );
        return tmp;
    }

};

}

#endif
