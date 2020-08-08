#include "object_wall.h"

namespace cvpp
{

// Destructor
inline
Wall::~Wall()
{
}

// Constructor
inline
Wall::Wall() : Object()
{
}

// Constructor
inline
Wall::Wall( const float& w , const float& h , const float& d , const Scalar& c ) : Wall()
{
    initialise( w , h , d , c );
}

// Constructor
inline
Wall::Wall( const float& w , const float& h , const float& d , const int& t ) : Wall()
{
    initialise( w , h , d , t );
}

// Object Constructor
inline
Wall::Wall( const Wall& obj )
{
    shareBuffer( obj );
}

// Initialise
inline void
Wall::initialise( const float& w , const float& h , const float& d , const Scalar& c )
{
    initialise( w , h , d );
    clr = c;
}

// Initialise
inline void
Wall::initialise( const float& w , const float& h , const float& d , const int& t )
{
    initialise( w , h , d );
    tex = t;

    brds.resize( 6 );
    brds[0][0] = pts[2]; brds[0][1] = pts[3]; brds[0][2] = pts[0]; brds[0][3] = pts[1]; // 0 1 2 3
    brds[1][0] = pts[5]; brds[1][1] = pts[4]; brds[1][2] = pts[7]; brds[1][3] = pts[6]; // 4 5 6 7
    brds[2][0] = pts[6]; brds[2][1] = pts[7]; brds[2][2] = pts[0]; brds[2][3] = pts[1]; // 0 1 6 7
    brds[3][0] = pts[5]; brds[3][1] = pts[4]; brds[3][2] = pts[3]; brds[3][3] = pts[2]; // 2 3 4 5
    brds[4][0] = pts[5]; brds[4][1] = pts[6]; brds[4][2] = pts[1]; brds[4][3] = pts[2]; // 1 2 5 6
    brds[5][0] = pts[4]; brds[5][1] = pts[7]; brds[5][2] = pts[0]; brds[5][3] = pts[3]; // 0 3 4 7
}

// Initialise
inline void
Wall::initialise( const float& w , const float& h , const float& d )
{
    float ww = w / 2 , dd = d / 2;

    pts.push( Pt3f( - dd , - ww , 0 ) ); // 0
    pts.push( Pt3f( - dd , - ww , h ) ); // 1
    pts.push( Pt3f( - dd , + ww , h ) ); // 2
    pts.push( Pt3f( - dd , + ww , 0 ) ); // 3
    pts.push( Pt3f( + dd , + ww , 0 ) ); // 4
    pts.push( Pt3f( + dd , + ww , h ) ); // 5
    pts.push( Pt3f( + dd , - ww , h ) ); // 6
    pts.push( Pt3f( + dd , - ww , 0 ) ); // 7

    idx.reset( 24 );
    idx.eig() << 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 ,
                 1 , 2 , 5 , 6 , 0 , 3 , 4 , 7 ,
                 0 , 1 , 6 , 7 , 2 , 3 , 4 , 5 ;

    Matf tmp = pts.limRows();
    lims.push( Pt3f( tmp(0,0) , tmp(0,1) , tmp(0,2) ) );
    lims.push( Pt3f( tmp(1,0) , tmp(1,1) , tmp(1,2) ) );

    startDataBuffer();
    startIndexBuffer();

    clr = WHI;
    tex = -1;
}

// Draw
inline void
Wall::draw( CPPlot& draw ) const
{
    glPushMatrix();
    glMultMatrixf( pose->Rt().t().eig_data() );

    if( tex == -1 )
    {
        glEnableClientState( GL_VERTEX_ARRAY );

            glBindBuffer( GL_ARRAY_BUFFER , bufferData.ptr );
            glVertexPointer( 3 , GL_FLOAT , 0 , 0 );
            glBindBuffer( GL_ARRAY_BUFFER , 0 );

            glBindBuffer( GL_ARRAY_BUFFER , bufferColor.ptr );
            glColorPointer( 3 , GL_FLOAT , 0 , 0 );
            glBindBuffer( GL_ARRAY_BUFFER , 0 );

            draw.lwc( 2 , WHITE );
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , bufferIndex.ptr );
            glDrawElements( GL_QUADS , bufferIndex.n , GL_UNSIGNED_INT , 0 );
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , 0 );

            draw.clr( clr );
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , bufferIndex.ptr );
            glDrawElements( GL_QUADS , bufferIndex.n , GL_UNSIGNED_INT , 0 );
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , 0 );

        glDisableClientState( GL_VERTEX_ARRAY );
    }
    else
    {
        draw.bindTexture( tex );
        forLOOPi( brds.size() )
            draw.useTexture( brds[i] , 1.0 );
        draw.unbindTexture();
    }

    glPopMatrix();
}

inline bool
Wall::inside( const Pt3f& pos ) const
{
    Matf tmp = pose->o2w( lims ).limRows();

    if( pos.x >= tmp(0,0) && pos.x <= tmp(1,0) &&
        pos.y >= tmp(0,1) && pos.y <= tmp(1,1) &&
        pos.z >= tmp(0,2) && pos.z <= tmp(1,2) ) return true;

    return false;
}

}
