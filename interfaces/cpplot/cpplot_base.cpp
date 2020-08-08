#include "../cpplot.h"

namespace cvpp
{

CPPlot::CPPlot()
{
    int argc = 1;
    char *argv[] = { NULL };
    glutInit( &argc , argv );

    fontT = GLUT_BITMAP_HELVETICA_10;
    fontS = GLUT_BITMAP_HELVETICA_12;
    fontM = GLUT_BITMAP_HELVETICA_18;

    quad = gluNewQuadric();

    fW = fS = cW = cS = -1;
    idxBuffer = idxTexture = -1;
    selecting = false;

    windows.reserve( 10 );
}

CPPlot::~CPPlot()
{
    for( int i = 0 ; i < buffers.size() ; i++ )
        glDeleteBuffers( 1 , &buffers[i].ptr );
    for( int i = 0 ; i < textures.size() ; i++ )
        glDeleteTextures( 1 , &textures[i].ptr );
}

CPPlot::CPPlot( const String& title , const Borders2f& borders ,
                const int& r , const int& c ) : CPPlot()
{
    addWindow( title, borders , r , c );
}

}
