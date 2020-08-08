#ifndef OBJECT_H
#define OBJECT_H

#define GL_GLEXT_PROTOTYPES

#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>

#include <cvpp/auxiliar/definitions.h>
#include <cvpp/auxiliar/definitions/definitions_cpplot.h>

#include <cvpp/structs/struct_buffer.h>
#include <cvpp/properties/pose.h>
#include <cvpp/containers/vector.h>

namespace cvpp
{

class CPPlot;
class World;

class Object
{

protected:

    bool share;

    Pts3f pts,clr;
    Veci idx;

    Buffer bufferData;
    Buffer bufferColor;
    Buffer bufferIndex;

public:

    Pointer< Posef > pose;

public:

    ~Object();

    Object();
    Object( const String& );
    Object( const String& , const int& );

    const int n() const { return pts.n(); }
    const bool started() const { return bufferData.ptr > 0; }

    Buffer& ptsBuffer() { return bufferData; }
    const Buffer& dataBuffer() const { return bufferData; }

    Buffer& clrBuffer() { return bufferColor; }
    const Buffer& colorBuffer() const { return bufferColor; }

    Buffer& idxBuffer() { return bufferIndex; }
    const Buffer& idxBuffer() const { return bufferIndex; }

    Pts3f& points() { return pts; }
    const Pts3f& points() const { return pts; }

    Pts3f wpoints() const { return pose->o2w( pts ); }
    Pts3f transform( const CV& cv ) const { return wpoints().transform( cv ); }
    Pts3f itransform( const CV& cv ) const { return wpoints().itransform( cv ); }

    Pts3f& color() { return clr; }
    const Pts3f& color() const { return clr; }

    Veci& index() { return idx; }
    const Veci& index() const { return idx; }

    void print() const { points().print(); }
    void info() const { points().info(); }

    void shareBuffer( const Object& );

    void project( const Object& obj , Pts3f& ) const;
    void project( const Pts3f& obj , Pts3f& ) const;

    Pts3f project( const Object& obj ) const { Pts3f pts( obj.n() ); project( obj , pts ); return pts; }
    Pts3f project( const Pts3f& pts1 ) const { Pts3f pts2( pts1.n() ); project( pts1 , pts2 ); return pts2; }

    virtual void save( const String& ) const;
    virtual void save( const String& str , const int& n ) const
    { save( str + std::to_string(n) ); }

    virtual void load( const String& );
    virtual void load( const String& str , const int& n )
    { load( str + std::to_string(n) ); }

    virtual void startDataBuffer();
    virtual void startColorBuffer();
    virtual void startIndexBuffer();

    virtual void updateDataBuffer();
    virtual void updateColorBuffer();

    virtual void updateBuffer()
    { updateDataBuffer(); updateColorBuffer(); }

    virtual void draw( CPPlot& ) const { disp( "BASE OBJECT DRAW" ); }
    virtual void draw( CPPlot& , const World& ) const { disp( "BASE OBJECT DRAW" ); }

    virtual Posef& setPos( const Pt3f& pt ) { return pose->setPos( pt ); }
    virtual Posef& setPos( const float& x , const float& y , const float& z )
    { return pose->setPos( x , y , z ); }

    virtual Posef& rotate( const float& x , const float& y , const float& z )
    { return pose->rotateXYZ( x , y , z ); }

    virtual Posef& setLook( const float& x , const float& y , const float& z )
    { return pose->setLook( x , y , z ); }

    Posef& setPose( const Posef& , const Posef& , const float& );
    TPL_T Posef& setPose( const T& tpl ) { return pose->setPose( tpl ); }

    virtual Posef& setPose( const Object& obj1 , const Object& obj2 , const float& t )
    { return setPose( *obj1.pose , *obj2.pose , t ); }
    virtual Posef& setPose( const Object& obj1 , const Posef& pose2 , const float& t )
    { return setPose( *obj1.pose , pose2 , t ); }
    virtual Posef& setPose( const Posef& pose1 , const Object& obj2 , const float& t )
    { return setPose( pose1 , *obj2.pose , t ); }

    virtual Posef& moveX( const float& x ) { return pose->moveX( x ); }
    virtual Posef& moveY( const float& y ) { return pose->moveY( y ); }
    virtual Posef& moveZ( const float& z ) { return pose->moveZ( z ); }

    virtual Posef& rotateX( const float& x ) { return pose->rotateX( x ); }
    virtual Posef& rotateY( const float& y ) { return pose->rotateY( y ); }
    virtual Posef& rotateZ( const float& z ) { return pose->rotateZ( z ); }

    virtual bool inside( const Pt3f& ) const { disp( "BASE OBJECT INSIDE" ); }
    virtual bool inside( const Pts3f& ) const { disp( "BASE OBJECT INSIDE" ); }

    Pt3f getPosPt() const { return pose->getPosPt(); }

    Pts3f o2w( const Pts3f& pts ) const { return pose->o2w( pts ); }
    Pts3f w2o( const Pts3f& pts ) const { return pose->w2o( pts ); }
    Pts3f o2w() const { return pose->o2w( points() ); }

    Object& operator=( const Posef& pose ) { *this->pose = pose; }

};

}

#endif
