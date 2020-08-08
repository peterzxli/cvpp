#include "object_keyframe.h"

namespace cvpp
{

// Destructor
inline
Keyframe::~Keyframe()
{
}

// Constructor
inline
Keyframe::Keyframe() : Object()
{
}

// Object Constructor
inline
Keyframe::Keyframe( const Keyframe& obj ) : Keyframe()
{
    shareBuffer( obj );
}

// Camera Constructor
inline
Keyframe::Keyframe( Camera& cam ) : Keyframe()
{
    initialise( cam );
}

// Save
inline void
Keyframe::save( const String& str ) const
{
    Object::save( str );
    vars.save( str + "_variance" );
}

// Load
inline void
Keyframe::load( const String& str )
{
    Object::load( str );
    vars.load( str + "_variance" );
}

// Initialise
inline void
Keyframe::initialise( Camera& cam )
{
    this->cam = &cam;
}

// Draw
inline void
Keyframe::draw( CPPlot& draw ) const
{
    glPushMatrix();
    glMultMatrixf( pose->Rt().t().eig_data() );

        draw.psc(4,RED).pt3D( 0.0 , 0.0 , 0.0 );

        draw.lwc(2,WHITE);
        draw.loop3D( cam->world_borders );
        draw.cct3D( cam->world_borders );

        draw.ps(1);

        glEnableClientState( GL_VERTEX_ARRAY );
        glEnableClientState( GL_COLOR_ARRAY );

            glBindBuffer( GL_ARRAY_BUFFER , bufferData.ptr );
            glVertexPointer( 3 , GL_FLOAT , 0 , 0 );
            glBindBuffer( GL_ARRAY_BUFFER , 0 );

            glBindBuffer( GL_ARRAY_BUFFER , bufferColor.ptr );
            glColorPointer(  3 , GL_FLOAT , 0 , 0 );
            glBindBuffer( GL_ARRAY_BUFFER , 0 );

            glDrawArrays( GL_POINTS , 0 , bufferData.n );

        glDisableClientState( GL_COLOR_ARRAY );
        glDisableClientState( GL_VERTEX_ARRAY );

    glPopMatrix();
}

}
