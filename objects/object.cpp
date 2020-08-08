#include "object.h"

namespace cvpp
{

// Destructor
Object::~Object()
{
    if( !share )
    {
        if( bufferData.started() )  glDeleteBuffers( 1 , &bufferData.ptr  );
        if( bufferColor.started() ) glDeleteBuffers( 1 , &bufferColor.ptr );
        if( bufferIndex.started() ) glDeleteBuffers( 1 , &bufferIndex.ptr );
    }
}

// Constructor
Object::Object()
{
    pts.reset(0);
    clr.reset(0);
    idx.reset(0);

    pose = std::make_shared< Posef >();
    share = false;
}

// Load Constructor
Object::Object( const String& str ) : Object()
{
    load( str );
}

// Load Constructor
Object::Object( const String& str , const int& n ) : Object()
{
    load( str , n );
}

// Share Buffer
void
Object::shareBuffer( const Object& obj )
{
    pts >> obj.pts;
    clr >> obj.clr;
    idx >> obj.idx;

    bufferData = obj.bufferData;
    bufferColor = obj.bufferColor;
    bufferIndex = obj.bufferIndex;

    share = true;
}

// Save
void
Object::save( const String& str ) const
{
    pose->save( str + "_pose" );

    pts.save( str + "_points" );
    clr.save( str + "_color"  );
    idx.save( str + "_index"  );
}

// Load
void
Object::load( const String& str )
{
    pose->load( str + "_pose" );

    pts.load( str + "_points" );
    clr.load( str + "_color"  );
    idx.load( str + "_index"  );

    if( !pts.empty() ) startDataBuffer();
    if( !clr.empty() ) startColorBuffer();
    if( !idx.empty() ) startIndexBuffer();
}

// Project
void
Object::project( const Object& obj , Pts3f& pts ) const
{
    obj.pose->o2w( obj.points() , pts );
    pose->w2o( pts , pts );
}

// Project
void
Object::project( const Pts3f& pts1 , Pts3f& pts2 ) const
{
    pose->w2o( pts1 , pts2 );
}

// Set Pose
Posef&
Object::setPose( const Posef& pose1 , const Posef& pose2 , const float& t )
{
    return pose->setPose( pose1 , pose2 , t );
}

// Start Data Buffer
void
Object::startDataBuffer()
{
    glGenBuffers( 1 , &bufferData.ptr );

    bufferData.type = BUFFER_DATA_FLOAT;
    bufferData.n = pts.n(); bufferData.d = pts.d();

    bufferData.minX = pts.d(0).min(); bufferData.maxX = pts.d(0).max();
    bufferData.minY = pts.d(1).min(); bufferData.maxY = pts.d(1).max();
    bufferData.minZ = pts.d(2).min(); bufferData.maxZ = pts.d(2).max();

    glBindBuffer( GL_ARRAY_BUFFER , bufferData.ptr );
    glBufferData( GL_ARRAY_BUFFER , pts.s() * sizeof(float) ,
                  &pts.eig_data()[0] , GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER , 0 );
}

// Update Data Buffer
void
Object::updateDataBuffer()
{
    bufferData.minX = pts.d(0).min(); bufferData.maxX = pts.d(0).max();
    bufferData.minY = pts.d(1).min(); bufferData.maxY = pts.d(1).max();
    bufferData.minZ = pts.d(2).min(); bufferData.maxZ = pts.d(2).max();

    glBindBuffer( GL_ARRAY_BUFFER , bufferData.ptr );
    glBufferSubData( GL_ARRAY_BUFFER , 0 , pts.s() * sizeof(float) ,
                     &pts.eig_data()[0] );
    glBindBuffer( GL_ARRAY_BUFFER , 0 );
}

// Start Color Buffer
void
Object::startColorBuffer()
{
    glGenBuffers( 1 , &bufferColor.ptr );

    bufferColor.type = BUFFER_DATA_FLOAT;
    bufferColor.n = clr.n(); bufferColor.d = clr.d();

    glBindBuffer( GL_ARRAY_BUFFER , bufferColor.ptr );
    glBufferData( GL_ARRAY_BUFFER , clr.s() * sizeof(float) ,
                  &clr.eig_data()[0] , GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER , 0 );
}

// Update Color Buffer
void
Object::updateColorBuffer()
{
    glBindBuffer( GL_ARRAY_BUFFER , bufferColor.ptr );
    glBufferSubData( GL_ARRAY_BUFFER , 0 , clr.s() * sizeof(float) ,
                     &clr.eig_data()[0] );
    glBindBuffer( GL_ARRAY_BUFFER , 0 );
}

// Start Index Buffer
void
Object::startIndexBuffer()
{
    glGenBuffers( 1 , &bufferIndex.ptr );

    bufferIndex.type = BUFFER_IDX;
    bufferIndex.n = idx.n();
    bufferIndex.d = idx.d();

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , bufferIndex.ptr );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER , idx.s() * sizeof(unsigned) ,
                  &idx.eig_data()[0] , GL_STATIC_DRAW );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , 0 );
}

}
