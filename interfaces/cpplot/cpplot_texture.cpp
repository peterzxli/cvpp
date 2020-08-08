#include "../cpplot.h"

namespace cvpp
{

CPPlot&
CPPlot::bindTexture( const int& idx )
{
    idxTexture = idx;
    glBindTexture( GL_TEXTURE_2D , textures[idx].ptr );
    return *this;
}

CPPlot&
CPPlot::unbindTexture()
{
    idxTexture = -1;
    glBindTexture( GL_TEXTURE_2D , 0 );
    return *this;
}

// Add Texture
const int
CPPlot::addTexture()
{
    textures.resize( textures.size() + 1 );
    glGenTextures( 1 , &textures.back().ptr );

    glBindTexture( GL_TEXTURE_2D , textures.back().ptr );

    glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR );

//    glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_CLAMP );
//    glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_WRAP_T , GL_CLAMP );

    glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_WRAP_T , GL_REPEAT );

    glBindTexture( GL_TEXTURE_2D , 0 );
    return textures.size() - 1;
}

// Add Texture (1U)
const int
CPPlot::addTexture1U( const int& h ,
                      const int& w )
{
    bindTexture( addTexture() );
    glTexImage2D( GL_TEXTURE_2D , 0 , GL_LUMINANCE , w , h ,
                  0 , GL_LUMINANCE , GL_UNSIGNED_BYTE , nullptr );
    unbindTexture(); return textures.size() - 1;
}

// Add Texture (3U)
const int
CPPlot::addTexture3U( const int& h ,
                      const int& w )
{
    bindTexture( addTexture() );
    glTexImage2D( GL_TEXTURE_2D , 0 , GL_RGB , w , h ,
                  0 , GL_BGR , GL_UNSIGNED_BYTE , nullptr );
    unbindTexture(); return textures.size() - 1;
}

// Set Texture
CPPlot&
CPPlot::setTexture( const int& idx ,
                    const CV& frame )
{
    bindTexture( idx );
    setTexture( frame );
    return *this;
}

// Set Texture
CPPlot&
CPPlot::setTexture( const CV& frame )
{
    cTexture().filled = true;

    cTexture().r = frame.rows;
    cTexture().c = frame.cols;

    if( frame.type() == CV_8UC1 )
        glTexImage2D( GL_TEXTURE_2D , 0 , GL_LUMINANCE , frame.cols , frame.rows ,
                      0 , GL_LUMINANCE , GL_UNSIGNED_BYTE , frame.ptr() );
    else
    if( frame.type() == CV_32FC1 )
        glTexImage2D( GL_TEXTURE_2D , 0 , GL_LUMINANCE , frame.cols , frame.rows ,
                      0 , GL_LUMINANCE , GL_FLOAT , frame.ptr() );
    else
    if( frame.type() == CV_8UC3 )
        glTexImage2D( GL_TEXTURE_2D , 0 , GL_RGB , frame.cols , frame.rows ,
                      0 , GL_BGR , GL_UNSIGNED_BYTE , frame.ptr() );
    else
    if( frame.type() == CV_32FC3 )
        glTexImage2D( GL_TEXTURE_2D , 0 , GL_RGB , frame.cols , frame.rows ,
                      0 , GL_BGR , GL_FLOAT , frame.ptr() );
    else
    if( frame.type() == CV_8UC4 )
        glTexImage2D( GL_TEXTURE_2D , 0 , GL_RGBA , frame.cols , frame.rows ,
                      0 , GL_BGRA , GL_UNSIGNED_BYTE , frame.ptr() );
    else
    {
        cTexture().filled = false;
        std::cout << "TEXTURE TYPE NOT SUPPORTED" << std::endl;
    }

    return *this;
}

// Update Texture
CPPlot&
CPPlot::updTexture( const int& idx ,
                    const CV& frame )
{
    bindTexture( idx );
    updTexture( frame );
    return *this;
}

// Update Texture
CPPlot&
CPPlot::updTexture( const CV& frame )
{
    if( frame.type() == CV_8UC1 )
        glTexSubImage2D( GL_TEXTURE_2D , 0 , 0 , 0 , frame.cols , frame.rows ,
                         GL_LUMINANCE , GL_UNSIGNED_BYTE , frame.ptr() );
    else
    if( frame.type() == CV_32FC1 )
        glTexSubImage2D( GL_TEXTURE_2D , 0 , 0 , 0 , frame.cols , frame.rows ,
                         GL_LUMINANCE , GL_FLOAT , frame.ptr() );
    else
    if( frame.type() == CV_8UC3 )
        glTexSubImage2D( GL_TEXTURE_2D , 0 , 0 , 0 , frame.cols , frame.rows ,
                         GL_BGR , GL_UNSIGNED_BYTE , frame.ptr() );
    else
    if( frame.type() == CV_32FC3 )
        glTexSubImage2D( GL_TEXTURE_2D , 0 , 0 , 0 , frame.cols , frame.rows ,
                         GL_BGR , GL_FLOAT , frame.ptr() );
    else
        std::cout << "TEXTURE TYPE NOT SUPPORTED" << std::endl;

    return *this;
}

// Use Texture
CPPlot&
CPPlot::useTexture()
{
    return useTexture( cSores() );
}

// Use Texture
CPPlot&
CPPlot::useTexture( const int& tex , const CV& cv )
{
    if( cTexture().filled )
    {
         updTexture( tex , cv );
    }
    else
    {
        setTexture( tex , cv );
        setResolution( cv.rows , cv.cols );
    }

    return useTexture();
}

// Use Texture (Borders2)
CPPlot&
CPPlot::useTexture( const Borders2f& borders , const float& repeat )
{
    glColor3d( 1.0 , 1.0 , 1.0 );

    glEnable( GL_TEXTURE_2D );
        glBegin( GL_QUADS );
            glTexCoord2d( 0.0 , 0.0 ); vertex( borders.lu() );
            glTexCoord2d( 1.0 , 0.0 ); vertex( borders.ru() );
            glTexCoord2d( 1.0 , 1.0 ); vertex( borders.rd() );
            glTexCoord2d( 0.0 , 1.0 ); vertex( borders.ld() );
        glEnd();
    glDisable( GL_TEXTURE_2D );

    return *this;
}

// Use Texture (Borders3)
CPPlot&
CPPlot::useTexture( const Borders3f& borders , const float& repeat )
{
    glColor3d( 1.0 , 1.0 , 1.0 );

    float x , y;
    if( repeat > 0 )
    {
        y = len( borders.lu() , borders.ru() ) / repeat;
        x = len( borders.lu() , borders.ld() ) / repeat;

        float r = float( cTexture().c ) / float( cTexture().r );
        if( r > 1.0 ) x *= r; else y /= r;
    }
    else
    {
        x = 1.0;
        y = 1.0;
    }

    glEnable( GL_TEXTURE_2D );
        glBegin( GL_QUADS );
            glTexCoord2d( 0.0 , 0.0 ); vertex( borders.lu() );
            glTexCoord2d(  y  , 0.0 ); vertex( borders.ru() );
            glTexCoord2d(  y  ,  x  ); vertex( borders.rd() );
            glTexCoord2d( 0.0 ,  x  ); vertex( borders.ld() );
        glEnd();
    glDisable( GL_TEXTURE_2D );

    return *this;
}

}
