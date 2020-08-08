#include "./object_camera.h"

namespace cvpp
{

// Destructor
inline
Camera::~Camera()
{
}

// Constructor
inline
Camera::Camera() : Object()
{
    D.reset(8);

    K.reset(3,3);
    P.reset(3,3);

    M.reset(3,3);
    M.eig() <<  0 ,  0  , 1 ,
               -1 ,  0  , 0 ,
                0 , -1  , 0 ;

    axesOff();
}

// Constructor (String)
inline
Camera::Camera( const String& str , const double& scl , const bool& off ) : Camera()
{
    calibrate( str , scl , off );
}

// Constructor (Matrix)
inline
Camera::Camera( const int& wdt , const int& hgt , const Matf& K , const Matf& D ,
                const double& scl , const bool& off ) : Camera()
{
    calibrate( wdt , hgt , K , D , scl , off );
}

// Draw
inline void
Camera::draw( CPPlot& draw ) const
{
    glPushMatrix();
    glMultMatrixf( pose->Rt().t().eig_data() );

        glEnableClientState( GL_VERTEX_ARRAY );

            glBindBuffer( GL_ARRAY_BUFFER , bufferData.ptr );
            glVertexPointer( 3 , GL_FLOAT , 0 , 0 );
            glBindBuffer( GL_ARRAY_BUFFER , 0 );

            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , bufferIndex.ptr );
            glDrawElements( GL_LINES , bufferIndex.n , GL_UNSIGNED_INT , 0 );
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , 0 );

            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

        glDisableClientState( GL_VERTEX_ARRAY );

        if( with_axes )
        {
            draw.clr(GRE).line3D( Pt3f( 0 , 0 , 0 ) , Pt3f( 1.2 * scl , 0.0 , 0.0 ) );
            draw.clr(BLU).line3D( Pt3f( 0 , 0 , 0 ) , Pt3f( 0.0 , 1.2 * scl , 0.0 ) );
            draw.clr(RED).line3D( Pt3f( 0 , 0 , 0 ) , Pt3f( 0.0 , 0.0 , 1.2 * scl ) );
        }

        if( draw.hasTexture() )
            draw.useTexture( world_borders );

    glPopMatrix();
}

// Draw
inline void
Camera::draw( CPPlot& draw ,
              const World& world ) const
{
    this->draw( draw );

    glPushMatrix();
    glMultMatrixf( pose->Rt().t().eig_data() );

        for( unsigned i = 0 ; i < world.qtyObjects() ; i++ )
        {
            Pts2f img( world[i].n() );
            this->w2d( world[i] , img );

            if( !img.empty() )
            {
                Pts3f pts1( img.n() );
                Pts3f pts2( img.n() );
                Pts3f lns1( img.n() );
                Pts3f lns2( img.n() );

                u2o( img , pts1 , 0.09999 );
                d2o( img , pts2 , 0.10001 );
                u2o( img , lns1 , 0.10000 );
                d2o( img , lns2 , 5.00000 );

                draw.psc(5,RED).pts3D( pts1 );
                draw.lwc(2,YELLOW).cct3D( lns1 );
                draw.lwc(2,YELLOW).cct3D( pts2 , lns2 );
            }
        }

    glPopMatrix();
}

// Calibrate
inline const bool
Camera::calibrate( const String& filename , const double& scl , const bool& offset )
{
    std::ifstream file;

    file.open( filename.c_str() );
    if( !file.is_open() )
    {
        std::cout << "UNABLE TO FIND CALIBRATION FILE : "
                  << filename << std::endl;
        return false;
    }

    file >> wdt >> hgt;

    file >> K(0,0) >> K(0,1) >> K(0,2)
         >> K(1,0) >> K(1,1) >> K(1,2)
         >> K(2,0) >> K(2,1) >> K(2,2);

    file >> D(0) >> D(1) >> D(2) >> D(3) >> D(4);
    D(5) = D(6) = D(7) = 0;

    file.close();

    return calibrate( scl , offset );
}

// Calibrate
inline const bool
Camera::calibrate( const int& wdt , const int& hgt , const Matf& K , const Matf& D ,
                   const double& scl , const bool& offset )
{
    this->hgt = hgt;
    this->wdt = wdt;

    this->K = K.clone();
    this->D = D.clone();

    return calibrate( scl , offset );
}

// Calibrate
inline const bool
Camera::calibrate( const double& scl , const bool& offset )
{
    P = cv::getOptimalNewCameraMatrix( K.cv() , D.cv() ,
                                       Size( wdt , hgt ) , 0 );

    cv::initUndistortRectifyMap( K.cv() , D.cv() , CV() , P.cv() ,
                                 Size( wdt , hgt ) , CV_32FC1 , map1 , map2 );

    iK = K.inverse(); Kt = K.transpose(); iKt = iK.transpose();
    iP = P.inverse(); Pt = P.transpose(); iPt = iP.transpose();

    pts.reset( 5 );
    pts[0] = Pt3d( 0.0 , 0.0 , 0.0 );
    world_borders >> pts(1,4);

    if( !offset )
        this->removeOffset();

    image_borders.luwh( 0.0 , 0.0 , wdt , hgt );
    u2o( image_borders.points() , world_borders.points() , scl );
    this->scl = scl;

    idx.reset( 16 );
    idx.eig() << 0 , 1 , 0 , 2 , 0 , 3 , 0 , 4 ,
                 1 , 2 , 2 , 3 , 3 , 4 , 4 , 1 ;

    startDataBuffer();
    startIndexBuffer();

    return true;
}

// Remove Offset
inline Camera&
Camera::removeOffset()
{
    M.eig() <<  1 , 0 , 0 ,
                0 , 1 , 0 ,
                0 , 0 , 1 ;
    return *this;
}

// Undistort
inline void
Camera::undistort( const CV& src ,
                         CV& dst ) const
{
    cv::remap( src , dst , map1 , map2 , cv::INTER_LINEAR );
}

// Undistort
inline void
Camera::undistort( CV& cv ) const
{
    undistort( cv , cv );
}

// Distort
inline void
Camera::distort( const Pt2f& src ,
                       Pt2f& dst ) const
{
    float xx = src.x * src.x;
    float yy = src.y * src.y;
    float xy = src.x * src.y;

    float r2 = xx + yy;

    float dxy =      2.0 * xy;
    float dx  = r2 + 2.0 * xx;
    float dy  = r2 + 2.0 * yy;

    float num_dist = 1.0 + r2 * ( D(0) + r2 * ( D(1) + r2 * D(4) ) );
    float den_dist = 1.0 + r2 * ( D(5) + r2 * ( D(6) + r2 * D(7) ) );

    dst.x = src.x * num_dist / den_dist + D(2) * dxy + D(3) * dx;
    dst.y = src.y * num_dist / den_dist + D(3) * dxy + D(2) * dy;
}

// Undistort
inline void
Camera::undistort( const Pt3f& src ,
                         Pt3f& dst ) const
{
    float x = src.x;
    float y = src.y;

    float r2,xx,yy,xy,dxy,dx,dy;
    float num_dist,den_dist;

    int niter = 5;
    for( int i = 0 ; i < niter ; i++ )
    {
        xx = dst.x * dst.x;
        yy = dst.y * dst.y;
        xy = dst.x * dst.y;

        r2 = xx + yy;

        dxy =      2.0 * xy;
        dx  = r2 + 2.0 * xx;
        dy  = r2 + 2.0 * yy;

        num_dist = 1.0 + r2 * ( D(0) + r2 * ( D(1) + r2 * D(4) ) );
        den_dist = 1.0 + r2 * ( D(5) + r2 * ( D(6) + r2 * D(7) ) );

        dst.x = ( x - D(2) * dxy - D(3) * dx ) * den_dist / num_dist;
        dst.y = ( y - D(3) * dxy - D(2) * dy ) * den_dist / num_dist;
    }
}

// Distort
inline void
Camera::distort( const Pts2f& src ,
                       Pts2f& dst ) const
{
    #pragma omp parallel for
    forLOOPi( src.n() ) distort( src[i] , dst[i] );
}

// Undistort
inline void
Camera::undistort( const Pts3f& src ,
                         Pts3f& dst ) const
{
    #pragma omp parallel for
    forLOOPi( src.n() ) undistort( src[i] , dst[i] );
}

// World to Distorted (Pts3f)
inline void
Camera::w2d( const Pts3f& wld ,
                   Pts2f& dst ) const
{
    Pts3f obj( wld.n() );
    this->pose->w2o( wld , obj );
    this->o2d( obj , dst );
}

// World to Distorted (Pts3f) IDX
inline void
Camera::w2d( const Pts3f& wld ,
                   Pts2f& dst , Veci& idx ) const
{
    Pts3f obj( wld.n() );
    this->pose->w2o( wld , obj );
    this->o2d( obj , dst , idx );
}

// World to Undistorted (Pts3f)
inline void
Camera::w2u( const Pts3f& wld ,
                   Pts2f& und ) const
{
    Pts3f obj( wld.n() );
    this->pose->w2o( wld , obj );
    this->o2u( obj , und );
}

// World to Undistorted (Pts3f) IDX
inline void
Camera::w2u( const Pts3f& wld ,
                   Pts2f& und , Veci& idx ) const
{
    Pts3f obj( wld.n() );
    this->pose->w2o( wld , obj );
    this->o2u( obj , und , idx );
}

// World to Undistorted (Pts3f) DEP
inline void
Camera::w2z( const Pts3f& wld , Pts2f& und , Vecf& dep ,
             const bool& filter , const float& thr ) const
{
    Pts3f obj( wld.n() );
    this->pose->w2o( wld , obj );
    this->o2z( obj , und , dep , filter , thr );
}

// World to Undistorted (Pts3f) RAD
inline void
Camera::w2r( const Pts3f& wld , Pts2f& und , Vecf& rad ,
             const bool& filter , const float& thr ) const
{
    Pts3f obj( wld.n() );
    this->pose->w2o( wld , obj );
    this->o2r( obj , und , rad , filter , thr );
}

// World to Distorted (Object)
inline void
Camera::w2d( const Object& obj ,
                   Pts2f&  dst ) const
{
    Pts3f wld( obj.n() );
    obj.pose->o2w( obj.points() , wld );
    this->w2d( wld , dst );
}

// World to Distorted (Object) IDX
inline void
Camera::w2d( const Object& obj ,
                   Pts2f&  dst , Veci& idx ) const
{
    Pts3f wld( obj.n() );
    obj.pose->o2w( obj.points() , wld );
    this->w2d( wld , dst , idx );
}

// World to Undistorted (Object)
inline void
Camera::w2u( const Object& obj ,
                   Pts2f&  und ) const
{
    Pts3f wld( obj.points().n() );
    obj.pose->o2w( obj.points() , wld );
    this->w2u( wld , und );
}

// World to Undistorted (Object) IDX
inline void
Camera::w2u( const Object& obj ,
                   Pts2f&  und , Veci& idx ) const
{
    Pts3f wld( obj.points().n() );
    obj.pose->o2w( obj.points() , wld );
    this->w2u( wld , und , idx );
}

// World to Undistorted (Object) DEP
inline void
Camera::w2z( const Object& obj , Pts2f&  und , Vecf& dep ,
             const bool& filter , const float& thr ) const
{
    Pts3f wld( obj.points().n() );
    obj.pose->o2w( obj.points() , wld );
    this->w2z( wld , und , dep , filter , thr );
}

// World to Undistorted (Object) RAD
inline void
Camera::w2r( const Object& obj , Pts2f&  und , Vecf& rad ,
             const bool& filter , const float& thr ) const
{
    Pts3f wld( obj.points().n() );
    obj.pose->o2w( obj.points() , wld );
    this->w2r( wld , und , rad , filter , thr );
}

// Object do Distorted
inline void
Camera::o2d( const Pts3f& obj ,
                   Pts2f& dst ) const
{
    o2u( obj , dst );

    if( !dst.empty() )
    {
        project( dst , iPt );
        distort( dst , dst );
        project( dst ,  Kt );
    }
}

// Object do Distorted IDX
inline void
Camera::o2d( const Pts3f& obj ,
                   Pts2f& dst , Veci& idx ) const
{
    o2u( obj , dst , idx );

    if( !dst.empty() )
    {
        project( dst , iPt );
        distort( dst , dst );
        project( dst ,  Kt );
    }
}

// Object to Undistorted
inline void
Camera::o2u( const Pts3f& obj ,
                   Pts2f& und ) const
{
    und.resize( obj.n() );

    filter3D( obj * M , und );
    if( !und.empty() )
    {
        project(  und , Pt );
        filter2D( und );
    }
}

// Object to Undistorted IDX
inline void
Camera::o2u( const Pts3f& obj ,
                   Pts2f& und , Veci& idx ) const
{
    und.resize( obj.n() );

    filter3D( obj * M , und , idx );
    if( !und.empty() )
    {
        project(  und , Pt );
        filter2D( und , idx );
    }
}

// Object to Undistorted DEP
inline void
Camera::o2z( const Pts3f& obj , Pts2f& und , Vecf& dep ,
             const bool& filter , const float& thr ) const
{
    und.resize( obj.n() );

    filter3D( obj * M , und , dep , thr );
    if( !und.empty() )
    {
        project( und , Pt );
        if( filter ) filter2D( und , dep );
    }
}

// Object to Undistorted RAD
inline void
Camera::o2r( const Pts3f& obj , Pts2f& und , Vecf& rad ,
             const bool& filter , const float& thr ) const
{
    und.resize( obj.n() );
    Veci idx;

    filter3D( obj * M , und , idx , thr );
    if( !und.empty() )
    {
        project( und , Pt );
        if( filter ) filter2D( und , idx );
    }

    rad.reset( idx.n() );
    for( unsigned i = 0 ; i < rad.n() ; i++ )
        rad[i] = sqrt( pow( obj[ idx[i] ].x , 2.0 )
                     + pow( obj[ idx[i] ].y , 2.0 )
                     + pow( obj[ idx[i] ].z , 2.0 ) );
}

// Distorted to Object
inline void
Camera::d2o( const Pts2f& dst , Pts3f& obj ,
             const float& depth ) const
{
    obj.resize( dst.n() );
    obj.d(0,2) = dst.mat();
    obj.d(2) = 1.0;

    obj.mat() *= iKt;
    undistort( obj , obj );
    obj.mat() *= depth;
    obj.mat() *= M.inverse();
}

// Undistorted to Object
inline void
Camera::u2o( const Pts2f& und , Pts3f& obj ,
             const float& depth ) const
{
    obj.resize( und.n() );
    obj.d(0,2) = und.mat();
    obj.d(2) = 1.0;

    obj.mat() *= iPt;
    obj.mat() *= depth;
    obj.mat() *= M.inverse();
}

// Distorted to Object
inline void
Camera::d2o( const Pts2f& dst , Pts3f& obj ,
             const Matf& depth ) const
{
    obj.resize( dst.n() );
    obj.d(0,2) = dst.mat();
    obj.d(2) = 1.0;

    obj.mat() *= iKt;
    undistort( obj , obj );
    obj.mat() %= depth;
    obj.mat() *= M.inverse();
}

// Undistorted to Object
inline void
Camera::u2o( const Pts2f& und , Pts3f& obj ,
             const Matf& depth ) const
{
    obj.resize( und.n() );
    obj.d(0,2) = und.mat();
    obj.d(2) = 1.0;

    obj.mat() *= iPt;
    obj.mat() %= depth;
    obj.mat() *= M.inverse();
}

// Undistorted to Object
inline void
Camera::start_u2o( const Pts2f& und , Pts3f& obj ) const
{
    obj.resize( und.n() );
    obj.d(0,2) = und.mat();
    obj.d(2) = 1.0;

    obj.mat() *= iPt;
}

// Undistorted to Object
inline void
Camera::finish_u2o( Pts3f& obj , const Matf& depth ) const
{
    obj.mat() %= depth;
    obj.mat() *= M.inverse();
}

// Filter 2D
inline void
Camera::filter2D( Pts2f& pts ) const
{
    unsigned k = 0;
    for( unsigned i = 0 ; i < pts.n() ; i++ )
        if( image_borders.inside( pts[i] ) )
            pts[k++] = pts[i];
    pts.keepFront( k );
}

// Filter 2D IDX
inline void
Camera::filter2D( Pts2f& pts , Veci& idx ) const
{
    unsigned k = 0;
    for( unsigned i = 0 ; i < pts.n() ; i++ )
        if( image_borders.inside( pts[i] ) )
            pts[k] = pts[i] , idx[k] = idx[i] , k++;
    pts.keepFront( k ) , idx.keepFront( k );
}

// Filter 2D DEP
inline void
Camera::filter2D( Pts2f& pts , Vecf& dep ) const
{
    unsigned k = 0;
    for( unsigned i = 0 ; i < pts.n() ; i++ )
        if( image_borders.inside( pts[i] ) )
            pts[k] = pts[i] , dep[k] = dep[i] , k++;
    pts.keepFront( k ) , dep.keepFront( k );
}

// Filter 3D
inline void
Camera::filter3D( const Pts3f& obj , Pts2f& und ,
                  const float& thr ) const
{
    unsigned k = 0;
    for( unsigned i = 0 ; i < obj.n() ; i++ )
        if( obj[i].z > thr )
        {
            und[k].x = obj[i].x / obj[i].z;
            und[k].y = obj[i].y / obj[i].z;
            k++;
        }
    und.keepFront( k );
}

// Filter 3D IDX
inline void
Camera::filter3D( const Pts3f& obj , Pts2f& und , Veci& idx ,
                  const float& thr ) const
{
    idx.reset( obj.n() );

    unsigned k = 0;
    for( unsigned i = 0 ; i < obj.n() ; i++ )
        if( obj[i].z > thr )
        {
            und[k].x = obj[i].x / obj[i].z;
            und[k].y = obj[i].y / obj[i].z;
            idx[k++] = i;
        }
    und.keepFront( k ); idx.keepFront( k );
}

// Filter 3D DEP
inline void
Camera::filter3D( const Pts3f& obj , Pts2f& und , Vecf& dep ,
                  const float& thr ) const
{
    dep.reset( obj.n() );

    unsigned k = 0;
    for( unsigned i = 0 ; i < obj.n() ; i++ )
        if( obj[i].z > thr )
        {
            und[k].x = obj[i].x / obj[i].z;
            und[k].y = obj[i].y / obj[i].z;
            dep[k++] = obj[i].z;
        }
    und.keepFront( k ); dep.keepFront( k );
}

// Project
inline void
Camera::project( Pts2f& pts ,
                 const Matf& mat ) const
{
    pts.mat() *= mat.b(0,0,2,2);
    pts.mat() += mat.b(2,0,1,2);
}

// Project Depth
inline void
Camera::projectDepth( const Matf& frame , const float& near , const float& far ,
                      Pts2f& pts2 , Pts3f& pts3 , Vecf& dep ) const
{
    pts2.reset().reserve( frame.s() );
    dep.reset().reserve( frame.s() );

    forLOOPij( frame.r() , frame.c() )
    {   if( frame(i,j) < 1.0 )
        {
            pts2.insert( Pt2f( j , i ) );
            dep.insert( far * near / ( far + frame(i,j) * ( near - far ) ) );
        }
    }

    pts2.update();
    dep.update();

    if( pts2.n() > 0 )
         pts3 = u2o( pts2 , dep.mat() );
    else pts3.reset();
}

// Project Depth
inline void
Camera::projectDepth( const Matf& frame , const float& near , const float& far ,
                      Pts3f& pts3 , Vecf& dep ) const
{
    Pts2f pts2;
    projectDepth( frame , near , far , pts2 , pts3 , dep );
}

// Project Depth
inline void
Camera::projectDepth( const Matf& frame , const float& near , const float& far ,
                      Pts2f& pts2 , Pts3f& pts3 , Vecf& dep , Img3c& color ) const
{
    projectDepth( frame , near , far , pts2 , pts3 , dep );

    color.reset( frame.r() , frame.c() ).setVal(0);
    Matf clr = dep.mat().toRGBjet( near , far );

    forLOOPij( pts2.n() , 3 )
        color( pts2[i].y , pts2[i].x , j ) = 255 * clr( i , 2 - j );
}

// Project Depth
inline void
Camera::projectDepth( const Matf& frame , const float& near , const float& far ,
                      Pts3f& pts3 , Vecf& dep , Img3c& color ) const
{
    Pts2f pts2;
    projectDepth( frame , near , far , pts2 , pts3 , dep , color );
}

// Project Depth
inline void
Camera::projectDepth( const Matf& frame , const float& near , const float& far ,
                      Pts2f& pts2 , Pts3f& pts3 , Matf& clr , Img3c& color ) const
{
    Vecf dep;
    projectDepth( frame , near , far , pts2 , pts3 , dep );

    color.reset( frame.r() , frame.c() ).setVal(0);
    clr = dep.mat().toRGBjet( near , far );

    forLOOPij( pts2.n() , 3 )
        color( pts2[i].y , pts2[i].x , j ) = 255 * clr( i , 2 - j );
}

// Project Depth
inline void
Camera::projectDepth( const Matf& frame , const float& near , const float& far ,
                      Pts3f& pts3 , Matf& clr , Img3c& color ) const
{
    Pts2f pts2;
    projectDepth( frame , near , far , pts2 , pts3 , clr , color );
}

}
