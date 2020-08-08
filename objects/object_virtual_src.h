#include "object_virtual.h"

namespace cvpp
{

// Destructor
inline
Virtual::~Virtual()
{
}

// Constructor
inline
Virtual::Virtual() : Object()
{
}

// Constructor
inline
Virtual::Virtual( const String& str ,
                  const Scalar& clr1 , const Scalar& clr2 , const float& s ) : Virtual()
{
    initialise( str , clr1 , clr2 , s );
}

// Object Constructor
inline
Virtual::Virtual( const Virtual& obj )
{
    shareBuffer( obj );
}

// Initialise
inline void
Virtual::initialise( const String& str ,
                     const Scalar& clr1 , const Scalar& clr2 , const float& s )
{
    IFile file( str );
    if( file.is_open() )
    {
        this->clr1 = clr1;
        this->clr2 = clr2;

        String title;
        file >> title;

        int n , m , l ;
        file >> n >> m >> l ;

        float x , y , z ;
        forLOOPi( n )
        {
            file >> x >> y >> z;
            pts.insert( Pt3f( x , y , z ) );
        }
        pts.update();

        int u , v , w , t;
        forLOOPi( m )
        {
            file >> t >> u >> v >> w ;
            idx.insert( u ).insert( v ).insert( w );
        }
        idx.update();

        pts.mat().SubMeanRows().mlt( s );
        pts.mat().c(2) -= pts.mat().c(2).min();

        Matf tmp = pts.limRows();
        lims.push( Pt3f( tmp(0,0) , tmp(0,1) , tmp(0,2) ) );
        lims.push( Pt3f( tmp(1,0) , tmp(1,1) , tmp(1,2) ) );

        file.close();

        startDataBuffer();
        startIndexBuffer();
    }
    else
    {
        disp( "FILE " + str + " NOT FOUND!" );
    }

}

// Draw
inline void
Virtual::draw( CPPlot& draw ) const
{
    glPushMatrix();
    glMultMatrixf( pose->Rt().t().eig_data() );

    glEnableClientState( GL_VERTEX_ARRAY );

        glBindBuffer( GL_ARRAY_BUFFER , bufferData.ptr );
        glVertexPointer( 3 , GL_FLOAT , 0 , 0 );
        glBindBuffer( GL_ARRAY_BUFFER , 0 );

        draw.clr( clr2 );
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , bufferIndex.ptr );
        glDrawElements( GL_TRIANGLES , bufferIndex.n , GL_UNSIGNED_INT , 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , 0 );

        draw.clr( clr1 );
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , bufferIndex.ptr );
        glDrawElements( GL_TRIANGLES , bufferIndex.n , GL_UNSIGNED_INT , 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , 0 );

    glDisableClientState( GL_VERTEX_ARRAY );

    glPopMatrix();
}

inline bool
Virtual::inside( const Pt3f& pos ) const
{
    Matf tmp = pose->o2w( lims ).limRows();

    if( pos.x >= tmp(0,0) && pos.x <= tmp(1,0) &&
        pos.y >= tmp(0,1) && pos.y <= tmp(1,1) &&
        pos.z >= tmp(0,2) && pos.z <= tmp(1,2) ) return true;

    return false;
}

}



//    int in = 0 , out = 0;

//    forLOOPij( pts.n() , ctr.n() )
//    {
//        if( dot( pts[i] - ctr[j] , nrm[j] ) <= 0 )
//             in++;
//        else out++;
//    }

//    disp( in , out );

