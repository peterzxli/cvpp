#include "../cpplot.h"

namespace cvpp
{

// Store Color
void
CPPlot::storeColor( Img3c& img ) const
{
    img.initialise( cSbrd().h() , cSbrd().w() );

    glReadPixels( cSbrd().l() , cWbrd().h() - cSbrd().d() ,
                  cSbrd().w() , cSbrd().h() , GL_BGR , GL_UNSIGNED_BYTE ,
                  img.cv_data() );

    cv::flip( img.cv() , img.cv() , 0 );
}

// Store Color
void
CPPlot::storeColor( Img1c& img ) const
{
    Img3c tmp = storeColor3C();
    img.initialise( cSbrd().h() , cSbrd().w() );
    cv::cvtColor( tmp.cv() , img.cv() , CV_BGR2GRAY );
}

// Store Color
void
CPPlot::storeColor( Matf& mat ) const
{
//    mat.Resize( cSbrd().h() , 3 * cSbrd().w() );

    glReadPixels( cSbrd().l() , cWbrd().h() - cSbrd().d() ,
                  cSbrd().w() , cSbrd().h() , GL_RGB , GL_FLOAT ,
                  mat.eig_data() );
}

// Store Depth
void
CPPlot::storeDepth( Matf& mat ) const
{
//    mat.Resize( cSbrd().h() , cSbrd().w() );

    glReadPixels( cSbrd().l() , cWbrd().h() - cSbrd().d() ,
                  cSbrd().w() , cSbrd().h() , GL_DEPTH_COMPONENT , GL_FLOAT ,
                  mat.eig_data() );
}

// Prepare Text
void
CPPlot::prepareText()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); glLoadIdentity();

    gluOrtho2D( 0.0 , cScreen().borders.w() ,
                0.0 , cScreen().borders.h() );

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix(); glLoadIdentity();
}

// Write text (2D)
void
CPPlot::text( const double& x , const double& y ,
              String str , const int& align ) const
{
    glRasterPos2d( x , y );

    char character;
    for ( String::iterator i = str.begin() ; i != str.end() ; ++i )
    {
        character = *i;
        glutBitmapCharacter( fontM , character );
    }
}

// Write text (2D)
void
CPPlot::text2D( const double& x , const double& y ,
                String str , const int& align ) const
{
    text( cSres().l() + cSres().w() * x ,
          cSres().d() - cSres().h() * y , str , align );
}

// Write Text (3D)
void
CPPlot::text( const double& x , const double& y , const double& z ,
              String str , const int& align ) const
{
    glRasterPos3d( x , y , z );

    char character;
    for ( String::iterator i = str.begin() ; i != str.end() ; ++i )
    {
        character = *i;
        glutBitmapCharacter( fontM , character );
    }
}

// Write Text (Flatten)
void
CPPlot::textFlat( const double& x , const double& y ,
                  String str , const int& align ) const
{
    text( cSbrd().w() * x ,
          cSbrd().h() * y , str , align );
}

}
