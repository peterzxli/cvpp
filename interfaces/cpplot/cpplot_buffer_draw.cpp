#include "../cpplot.h"

namespace cvpp
{

// Draw 2D Points (Buffer)
CPPlot&
CPPlot::pts2D( const int& xyz , const int& clr )
{
    return shape( xyz , -1 , clr , buffer(xyz).n , 2 , DRAW_PTS );
}

// Draw 3D Points (Buffer)
CPPlot&
CPPlot::pts3D( const int& xyz , const int& clr )
{
    return shape( xyz , -1 , clr , buffer(xyz).n , 3 , DRAW_PTS );
}

// Draw 2D Line (Buffer)
CPPlot&
CPPlot::line2D( const int& xyz , const int& clr )
{
    return shape( xyz , -1 , clr , buffer(xyz).n , 2 , DRAW_LINE );
}

// Draw 2D Loop (Buffer)
CPPlot&
CPPlot::loop2D( const int& xyz , const int& clr )
{
    return shape( xyz , -1 , clr , buffer(xyz).n , 2 , DRAW_LOOP );
}

// Draw 3D Line (Buffer)
CPPlot&
CPPlot::line3D( const int& xyz , const int& clr )
{
    return shape( xyz , -1 , clr , buffer(xyz).n , 3 , DRAW_LINE );
}

// Draw 3D Loop (Buffer)
CPPlot&
CPPlot::loop3D( const int& xyz , const int& clr )
{
    return shape( xyz , -1 , clr , buffer(xyz).n , 3 , DRAW_LOOP );
}

// Draw 3D Triangs (Buffer)
CPPlot&
CPPlot::triang3D( const int& xyz , const int& clr )
{
    return shape( xyz , -1 , clr , buffer(xyz).n , 3 , DRAW_TRIANG );
}

// Draw 2D Grid (Buffer)
CPPlot&
CPPlot::grid2D( const int& xyz , const int& idx , const int& clr )
{
    return shape( xyz , idx , clr , buffer(idx).n , 2 , DRAW_GRID );
}

// Draw 2D Trid (Buffer)
CPPlot&
CPPlot::trid2D( const int& xyz , const int& idx , const int& clr )
{
    return shape( xyz , idx , clr , buffer(idx).n , 2 , DRAW_TRID );
}

// Draw 2D Grid Wire (Buffer)
CPPlot&
CPPlot::gwire2D( const int& xyz , const int& idx , const int& clr )
{
    return shape( xyz , idx , clr , buffer(idx).n , 2 , DRAW_WGRID );
}

// Draw 2D Trid Wire (Buffer)
CPPlot&
CPPlot::twire2D( const int& xyz , const int& idx , const int& clr )
{
    return shape( xyz , idx , clr , buffer(idx).n , 2 , DRAW_WTRID );
}

// Draw 3D Grid (Buffer)
CPPlot&
CPPlot::grid3D( const int& xyz , const int& idx , const int& clr )
{
    return shape( xyz , idx , clr , buffer(idx).n , 3 , DRAW_GRID );
}

// Draw 3D Trid (Buffer)
CPPlot&
CPPlot::trid3D( const int& xyz , const int& idx , const int& clr )
{
    return shape( xyz , idx , clr , buffer(idx).n , 3 , DRAW_TRID );
}

// Draw 3D Grid Wire (Buffer)
CPPlot&
CPPlot::gwire3D( const int& xyz , const int& idx , const int& clr )
{
    return shape( xyz , idx , clr , buffer(idx).n , 3 , DRAW_WGRID );
}

// Draw 3D Trid Wire (Buffer)
CPPlot&
CPPlot::twire3D( const int& xyz , const int& idx , const int& clr )
{
    return shape( xyz , idx , clr , buffer(idx).n , 3 , DRAW_WTRID );
}

// Draw 2D Surf (Buffer)
CPPlot&
CPPlot::surf2D( const int& xyz , const int& clr )
{
    return shape( xyz , -1 , clr , buffer(xyz).n , 2 , DRAW_SURF2 );
}

// Draw 3D Surf (Buffer)
CPPlot&
CPPlot::surf3D( const int& xyz , const int& clr )
{
    return shape( xyz , -1 , clr , buffer(xyz).n , 3 , DRAW_SURF3 );
}

// Draw 3D Wire Surf (Buffer)
CPPlot&
CPPlot::swire3D( const int& xyz , const int& clr )
{
    return shape( xyz , -1 , clr , buffer(xyz).n , 3 , DRAW_WSURF3 );
}

// Draw Shape
CPPlot&
CPPlot::shape( const int& xyz , const int& idx , const int& clr ,
               const int& n , const int& d , const int& type )
{
    if( !buffer(xyz).filled )
        return *this;

    glPushMatrix();

        glEnableClientState( GL_VERTEX_ARRAY );
        if( clr >= 0 ) glEnableClientState( GL_COLOR_ARRAY );

            bindBuffer( xyz );
            switch( buffer(xyz).type ) {
                case BUFFER_DATA_INT:    glVertexPointer( d , GL_INT    , 0 , 0 ); break;
                case BUFFER_DATA_FLOAT:  glVertexPointer( d , GL_FLOAT  , 0 , 0 ); break;
                case BUFFER_DATA_DOUBLE: glVertexPointer( d , GL_DOUBLE , 0 , 0 ); break;
            } unbindBuffer();

            if( clr >= 0 )
            {
                bindBuffer( clr );
                switch( buffer(clr).type ) {
                    case BUFFER_DATA_FLOAT:  glColorPointer( 3 , GL_FLOAT  , 0 , 0 ); break;
                    case BUFFER_DATA_DOUBLE: glColorPointer( 3 , GL_DOUBLE , 0 , 0 ); break;
                } unbindBuffer();
            }

            switch( type )
            {
                case DRAW_PTS:

                    glDrawArrays( GL_POINTS , 0 , n );
                    break;

                case DRAW_SEGS:

                    glDrawArrays( GL_LINES , 0 , n );
                    break;

                case DRAW_LINE:

                    glDrawArrays( GL_LINE_STRIP , 0 , n );
                    break;

                case DRAW_LOOP:

                    glDrawArrays( GL_LINE_LOOP , 0 , n );
                    break;

                case DRAW_TRIANG:

                    glDrawArrays( GL_TRIANGLES , 0 , n );
                    break;

                case DRAW_GRID:

                    bindBuffer( idx );
                    glDrawElements( GL_QUADS , 4 * n , GL_UNSIGNED_INT , 0 );
                    unbindBuffer();
                    break;

                case DRAW_TRID:

                    bindBuffer( idx );
                    glDrawElements( GL_TRIANGLES , 3 * n , GL_UNSIGNED_INT , 0 );
                    unbindBuffer();
                    break;

                case DRAW_WGRID:

                    glPushMatrix();
                    glTranslated( 0 , 0 , 0.002 );

                        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

                        bindBuffer( idx );
                        glDrawElements( GL_QUADS , 4 * n , GL_UNSIGNED_INT , 0 );
                        unbindBuffer();

                        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

                    glPopMatrix();
                    break;

                case DRAW_WTRID:

                    glPushMatrix();
                    glTranslated( 0 , 0 , 0.002 );

                        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

                        bindBuffer( idx );
                        glDrawElements( GL_TRIANGLES , 3 * n , GL_UNSIGNED_INT , 0 );
                        unbindBuffer();

                        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

                    glPopMatrix();
                    break;

                case DRAW_SURF2:

                    glDrawArrays( GL_LINES , 0 , n );
                    break;

                case DRAW_SURF3:

                    glDrawArrays( GL_TRIANGLES , 0 , n );
                    break;

                case DRAW_WSURF3:

                    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
                    glDrawArrays( GL_TRIANGLES , 0 , n );
                    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
                    break;
            }

        if( clr >= 0 ) glDisableClientState( GL_COLOR_ARRAY );
        glDisableClientState( GL_VERTEX_ARRAY );

    glPopMatrix();

    return *this;
}

}
