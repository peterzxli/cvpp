#ifndef OBJECT_CAMERA_H
#define OBJECT_CAMERA_H

#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <cvpp/interfaces/cpplot.h>

#include <cvpp/structs/struct_borders2.h>
#include <cvpp/structs/struct_borders3.h>

#include "./object.h"
#include "./object_world.h"

namespace cvpp
{

class Camera : public Object
{

protected:

    Matf D,M;
    Matf K,iK,Kt,iKt;
    Matf P,iP,Pt,iPt;
    CV map1,map2;

    int wdt,hgt;

    float scl;
    bool with_axes;

public:

    Borders2f image_borders;
    Borders3f world_borders;

public:

    ~Camera();

    Camera();
    Camera( const String& , const double& = 0.1 , const bool& = true );
    Camera( const int& , const int& , const Matf& , const Matf& ,
            const double& = 0.1 , const bool& = true );

    Camera& operator=( const Posef& pose ) { Object::operator=( pose ); }

    void draw( CPPlot& ) const;
    void draw( CPPlot& , const World& ) const;

    const int& width()  const { return wdt; }
    const int& height() const { return hgt; }

    const Matf& matK()  const { return K;  }
    const Matf& matP()  const { return P;  }
    const Matf& matKi() const { return iK; }
    const Matf& matPi() const { return iP; }

    const Matf& matD() const { return D; }

    const bool calibrate( const String& , const double& = 0.1 , const bool& = true );
    const bool calibrate( const int& , const int& , const Matf& , const Matf& ,
                          const double& = 0.1 , const bool& = true );
    const bool calibrate( const double& = 0.1 , const bool& = true );

    Camera& removeOffset();

    void axesOn()  { with_axes = true;  }
    void axesOff() { with_axes = false; }

    void undistort( const CV& , CV& ) const;
    void undistort( CV& ) const;

    TPL_TC void undistort( const Image<T,C>& src , Image<T,C>& dst ) const
    { undistort( src.cv() , dst.cv() ); }

    TPL_TC void undistort( Image<T,C>& dst ) const
    { undistort( dst.cv() ); }

    void distort( const Pt2f& , Pt2f& ) const;
    void distort( const Pts2f& , Pts2f& ) const;

    void undistort( const Pt3f& , Pt3f& ) const;
    void undistort( const Pts3f& , Pts3f& ) const;

    void w2d( const Pts3f& , Pts2f& ) const;
    void w2u( const Pts3f& , Pts2f& ) const;

    void w2d( const Pts3f& , Pts2f& , Veci& ) const;
    void w2u( const Pts3f& , Pts2f& , Veci& ) const;
    void w2z( const Pts3f& , Pts2f& , Vecf& , const bool& = true , const float& = 0.0 ) const;
    void w2r( const Pts3f& , Pts2f& , Vecf& , const bool& = true , const float& = 0.0 ) const;

    Pts2f w2d( const Pts3f& w ) const { Pts2f d; w2d( w , d ); return d; }
    Pts2f w2u( const Pts3f& w ) const { Pts2f u; w2u( w , u ); return u; }

    Pts2f w2d( const Pts3f& w , Veci& i ) const { Pts2f d; w2d( w , d , i ); return d; }
    Pts2f w2u( const Pts3f& w , Veci& i ) const { Pts2f u; w2u( w , u , i ); return u; }
    Pts2f w2z( const Pts3f& w , Vecf& z , const bool& filter = true , const float& thr = 0.0 ) const { Pts2f u; w2z( w , u , z , filter , thr ); return u; }
    Pts2f w2r( const Pts3f& w , Vecf& r , const bool& filter = true , const float& thr = 0.0 ) const { Pts2f u; w2r( w , u , r , filter , thr ); return u; }

    void w2d( const Object& , Pts2f& ) const;
    void w2u( const Object& , Pts2f& ) const;

    void w2d( const Object& , Pts2f& , Veci& ) const;
    void w2u( const Object& , Pts2f& , Veci& ) const;
    void w2z( const Object& , Pts2f& , Vecf& , const bool& = true , const float& = 0.0 ) const;
    void w2r( const Object& , Pts2f& , Vecf& , const bool& = true , const float& = 0.0 ) const;

    Pts2f w2d( const Object& w ) const { Pts2f d; w2d( w , d ); return d; }
    Pts2f w2u( const Object& w ) const { Pts2f u; w2u( w , u ); return u; }

    Pts2f w2d( const Object& w , Veci& i ) const { Pts2f d; w2d( w , d , i ); return d; }
    Pts2f w2u( const Object& w , Veci& i ) const { Pts2f u; w2u( w , u , i ); return u; }
    Pts2f w2z( const Object& w , Vecf& z , const bool& filter = true , const float& thr = 0.0 ) const { Pts2f u; w2z( w , u , z , filter , thr ); return u; }
    Pts2f w2r( const Object& w , Vecf& r , const bool& filter = true , const float& thr = 0.0 ) const { Pts2f u; w2r( w , u , r , filter , thr ); return u; }

    void o2d( const Pts3f& , Pts2f& ) const;
    void o2u( const Pts3f& , Pts2f& ) const;

    void o2d( const Pts3f& , Pts2f& , Veci& ) const;
    void o2u( const Pts3f& , Pts2f& , Veci& ) const;
    void o2z( const Pts3f& , Pts2f& , Vecf& , const bool& = true , const float& = 0.0 ) const;
    void o2r( const Pts3f& , Pts2f& , Vecf& , const bool& = true , const float& = 0.0 ) const;

    Pts2f o2d( const Pts3f& o ) const { Pts2f d; o2d( o , d ); return d; }
    Pts2f o2u( const Pts3f& o ) const { Pts2f u; o2u( o , u ); return u; }

    Pts2f o2d( const Pts3f& o , Veci& i ) const { Pts2f d; o2d( o , d , i ); return d; }
    Pts2f o2u( const Pts3f& o , Veci& i ) const { Pts2f u; o2u( o , u , i ); return u; }
    Pts2f o2z( const Pts3f& o , Vecf& z , const bool& filter = true , const float& thr = 0.0 ) const { Pts2f u; o2z( o , u , z , filter , thr ); return u; }
    Pts2f o2r( const Pts3f& o , Vecf& r , const bool& filter = true , const float& thr = 0.0 ) const { Pts2f u; o2r( o , u , r , filter , thr ); return u; }

    void d2o( const Pts2f& , Pts3f& , const float& ) const;
    void d2o( const Pts2f& , Pts3f& , const Matf& ) const;

    void u2o( const Pts2f& , Pts3f& , const float& ) const;
    void u2o( const Pts2f& , Pts3f& , const Matf& ) const;

    void start_u2o( const Pts2f& , Pts3f& ) const ;
    void finish_u2o( Pts3f& , const Matf& ) const;

    Pts3f d2o( const Pts2f& d , const float& s = 1.0 ) const { Pts3f o; d2o( d , o , s ); return o; }
    Pts3f d2o( const Pts2f& d , const Matf& s ) const { Pts3f o; d2o( d , o , s ); return o; }

    Pts3f u2o( const Pts2f& u , const float& s = 1.0 ) const { Pts3f o; u2o( u , o , s ); return o; }
    Pts3f u2o( const Pts2f& u , const Matf& s ) const { Pts3f o; u2o( u , o , s ); return o; }

    Pts3f d2w( const Pts2f& d , const float& s = 1.0 ) const { return o2w( d2o( d , s ) ); }
    Pts3f d2w( const Pts2f& d , const Matf& s ) const { return o2w( d2o( d , s ) ); }

    Pts3f u2w( const Pts2f& u , const float& s = 1.0 ) const { return o2w( u2o( u , s ) ); }
    Pts3f u2w( const Pts2f& u , const Matf& s ) const { return o2w( u2o( u , s ) ); }

    void filter2D( Pts2f& ) const;
    void filter2D( Pts2f& , Veci& ) const;
    void filter2D( Pts2f& , Vecf& ) const;

    void filter3D( const Pts3f& , Pts2f& , const float& = 0.0 ) const;
    void filter3D( const Pts3f& , Pts2f& , Veci& , const float& = 0.0 ) const;
    void filter3D( const Pts3f& , Pts2f& , Vecf& , const float& = 0.0 ) const;

    void project( Pts2f& , const Matf& ) const;

    void projectDepth( const Matf& , const float& , const float& , Pts2f& , Pts3f& , Vecf& ) const;
    void projectDepth( const Matf& , const float& , const float& , Pts3f& , Vecf& ) const;
    void projectDepth( const Matf& , const float& , const float& , Pts2f& , Pts3f& , Vecf& , Img3c& ) const;
    void projectDepth( const Matf& , const float& , const float& , Pts3f& , Vecf& , Img3c& ) const;
    void projectDepth( const Matf& , const float& , const float& , Pts2f& , Pts3f& , Matf& , Img3c& ) const;
    void projectDepth( const Matf& , const float& , const float& , Pts3f& , Matf& , Img3c& ) const;


};

}

#include "./object_camera_src.h"

#endif
