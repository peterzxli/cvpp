#include "object_board.h"

namespace cvpp
{

// Destructor
inline
Board::~Board()
{
}

// Constructor
inline
Board::Board() : Object()
{
}

// Constructor
inline
Board::Board( const int& nx ,
              const int& ny ,
              const int& nz ,
              const float& scale ) : Board()
{
    initialise( nx , ny , nz , scale );
}

// Object Constructor
inline
Board::Board( const Board& obj )
{
    shareBuffer( obj );
}

// Initialise
inline void
Board::initialise( const int& nx ,
                   const int& ny ,
                   const int& nz ,
                   const float& scale )
{
    Pt3f start( - float( nx - 1 ) / 2.0 * scale ,
                - float( ny - 1 ) / 2.0 * scale ,
                - float( nz - 1 ) / 2.0 * scale );

    for( unsigned j = 0 ; j <= ny - 1 ; j++ )
        for( unsigned i = 0 ; i <= nx - 1 ; i++ )
            for( unsigned k = 0 ; k <= nz - 1 ; k++ )
                pts.push( Pt3f( (float)i * scale ,
                                (float)j * scale ,
                                (float)k * scale ) + start );

    startDataBuffer();
}

// Draw
inline void
Board::draw( CPPlot& draw ) const
{
    glPushMatrix();
    glMultMatrixf( pose->Rt().t().eig_data() );

    glEnableClientState( GL_VERTEX_ARRAY );

        glBindBuffer( GL_ARRAY_BUFFER , bufferData.ptr );
        glVertexPointer( 3 , GL_FLOAT , 0 , 0 );
        glBindBuffer( GL_ARRAY_BUFFER , 0 );

        glDrawArrays( GL_POINTS , 0 , bufferData.n );

    glDisableClientState( GL_VERTEX_ARRAY );

    glPopMatrix();
}

}
