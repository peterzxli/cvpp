#include "object_drone.h"

namespace cvpp
{

// Destructor
inline
Drone::~Drone()
{
}

// Constructor
inline
Drone::Drone() : Object()
{
}

// Constructor
inline
Drone::Drone( const float& scale ) : Drone()
{
    initialise( scale );
}

// Object Constructor
inline
Drone::Drone( const Drone& obj )
{
    shareBuffer( obj );
}

// Initialise
inline void
Drone::initialise( const float& scale )
{
    float l = 0.3 * scale;
    float w = 0.2 * scale;
    float h = 0.1 * scale;

    pts.push( Pt3f( +l , +0.5 * w , +0.5 * h ) ).push( Pt3f( -l , +w , +h ) );
    pts.push( Pt3f( +l , -0.5 * w , +0.5 * h ) ).push( Pt3f( -l , -w , +h ) );
    pts.push( Pt3f( +l , +0.5 * w , -0.5 * h ) ).push( Pt3f( -l , +w , -h ) );
    pts.push( Pt3f( +l , -0.5 * w , -0.5 * h ) ).push( Pt3f( -l , -w , -h ) );

    clr.push( Pt3f( 0.7 , 0.7 , 0.7 ) ).push( Pt3f( 0.3 , 0.3 , 0.3 ) );
    clr.push( Pt3f( 0.7 , 0.7 , 0.7 ) ).push( Pt3f( 0.3 , 0.3 , 0.3 ) );
    clr.push( Pt3f( 0.7 , 0.7 , 0.7 ) ).push( Pt3f( 0.3 , 0.3 , 0.3 ) );
    clr.push( Pt3f( 0.7 , 0.7 , 0.7 ) ).push( Pt3f( 0.3 , 0.3 , 0.3 ) );

    idx.push( 0 ).push( 1 ).push( 3 ).push( 2 );
    idx.push( 4 ).push( 5 ).push( 7 ).push( 6 );
    idx.push( 0 ).push( 1 ).push( 5 ).push( 4 );
    idx.push( 3 ).push( 2 ).push( 6 ).push( 7 );
    idx.push( 1 ).push( 3 ).push( 7 ).push( 5 );
    idx.push( 0 ).push( 2 ).push( 6 ).push( 4 );

    startDataBuffer();
    startColorBuffer();
    startIndexBuffer();
}

// Draw
inline void
Drone::draw( CPPlot& draw ) const
{
    glPushMatrix();
    glMultMatrixf( pose->Rt().t().eig_data() );

    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );

        glBindBuffer( GL_ARRAY_BUFFER , bufferData.ptr );
        glVertexPointer( 3 , GL_FLOAT , 0 , 0 );
        glBindBuffer( GL_ARRAY_BUFFER , 0 );

        glBindBuffer( GL_ARRAY_BUFFER , bufferColor.ptr );
        glColorPointer( 3 , GL_FLOAT , 0 , 0 );
        glBindBuffer( GL_ARRAY_BUFFER , 0 );

        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , bufferIndex.ptr );
        glDrawElements( GL_QUADS , idx.n() , GL_UNSIGNED_INT , 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , 0 );

    glDisableClientState( GL_COLOR_ARRAY );
    glDisableClientState( GL_VERTEX_ARRAY );

    glPopMatrix();
}

}
