#include "../cpplot.h"

namespace cvpp
{

// Add Window
const int
CPPlot::addWindow( const String& title , const Borders2f& borders ,
                   const int& r , const int& c )
{
    windows.resize( nWindows() + 1 );
    windows.back().initialise( title , borders );

    cW = nWindows() - 1;

    if( r > 0 && c > 0 )
    {
        unsigned w = borders.w() / c;
        unsigned h = borders.h() / r;

        for( unsigned i = 0 ; i < r ; i++ )
            for( unsigned j = 0 ; j < c ; j++ )
                addScreen( LUWH( j * w , i * h , w , h ) );
    }

    return cW;
}

// Add Screen
const int
CPPlot::addScreen( const Borders2f& borders ,
                   const Scalar& color )
{
    cWindow().screens.resize( ncScreens() + 1 );
    cWindow().screens.back().initialise( borders , color );

    return cS = ncScreens() - 1;
}

// Use Window
CPPlot&
CPPlot::useWindow( const int& idx )
{
    cW = idx;

    SDL_GL_MakeCurrent( cWindow().SDLpointer ,
                        cWindow().SDLcontext );

    return *this;
}

// Use Screen
CPPlot&
CPPlot::useScreen( const int& idx )
{
    cS = idx;

    glViewport( cSbrd().l() , cWbrd().h() - cSbrd().d() ,
                cSbrd().w() , cSbrd().h() );

    glScissor( cSbrd().l() , cWbrd().h() - cSbrd().d() ,
               cSbrd().w() , cSbrd().h() );

    glClearColor( cBack()[0] , cBack()[1] , cBack()[2] , 1.0 );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    switch( cScreen().type )
    {
        case IMAGE_2D:

            glDisable(GL_DEPTH_TEST);

            gluOrtho2D( cSres().l() , cSres().r() ,
                        cSres().d() , cSres().u() );
            break;

        case PLOT_2D:

            glDisable(GL_DEPTH_TEST);

            glOrtho( cSres().l() - 0.20 * cSres().w() ,
                     cSres().r() + 0.10 * cSres().w() ,
                     cSres().u() - 0.10 * cSres().h() ,
                     cSres().d() + 0.10 * cSres().h() , cSbrd().b() ,
                                                        cSbrd().t() );
            break;

        case PLOT_3D:

            glEnable(GL_DEPTH_TEST);

            gluPerspective( cScreen().fov ,
                            cSbrd().w() / cSbrd().h() , 0.001 , 100000.0 );

            gluLookAt( cViewer().px() , cViewer().py() , cViewer().pz() ,
                       cViewer().lx() , cViewer().ly() , cViewer().lz() ,
                       cViewer().ux() , cViewer().uy() , cViewer().uz() );
            break;

        case WORLD_3D:

            glEnable(GL_DEPTH_TEST);

            if( cScreen().isCalibrated )
                 glMultMatrixd( cScreen().perspective );
            else gluPerspective( cScreen().fov ,
                                 cSbrd().w() / cSbrd().h() , 0.001 , 100000.0 );

            gluLookAt( cViewer().px() , cViewer().py() , cViewer().pz() ,
                       cViewer().lx() , cViewer().ly() , cViewer().lz() ,
                       cViewer().ux() , cViewer().uy() , cViewer().uz() );
            break;
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    return *this;
}

// Use Window + Screen
CPPlot&
CPPlot::useScreen( const int& i ,
                   const int& j )
{
    useWindow( i );
    useScreen( j );

    return *this;
}

// Flatten
CPPlot&
CPPlot::flatten()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);

    gluOrtho2D( cSbrd().l() , cSbrd().w() ,
                              cSbrd().h() , cSbrd().u() );

    glScissor( cSbrd().l() ,cWbrd().h() - cSbrd().d() ,
               cSbrd().w() , cSbrd().h() );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    return *this;
}

CPPlot&
CPPlot::enableScissor( const float& x , const float& y ,
                       const float& w , const float& h )
{
    glScissor( x , y , w , h );

    glEnable( GL_SCISSOR_TEST );
}

CPPlot&
CPPlot::disableScissor()
{
    glDisable( GL_SCISSOR_TEST );
}

// Use all screens
CPPlot&
CPPlot::allScreens()
{
    glViewport( 0.0 , 0.0 , cWbrd().w() , cWbrd().h() );
    glScissor( 0.0 , 0.0 , cWbrd().w() , cWbrd().h() );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D( 0.0 , cWbrd().w() ,
                      cWbrd().h() , 0.0 );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    return *this;
}

// Set Screen 2D
CPPlot&
CPPlot::set2Dimage()
{
    cScreen().type = IMAGE_2D;
    cScreen().background = WHITE;
    setResolution( cSbrd().h() , cSbrd().w() );
    cSores() = cSres();

    return useScreen( cW , cS );
}

// Set Screen 3D
CPPlot&
CPPlot::set3Dworld()
{
    cScreen().type = WORLD_3D;
    cScreen().background = BLACK;
    setResolution( cSbrd().h() , cSbrd().w() );
    cOViewer() = cViewer();

    return useScreen( cW , cS );
}

// Set Plot 2D
CPPlot&
CPPlot::set2Dplot()
{
    cScreen().type = PLOT_2D;
    cScreen().background = WHITE;
    cScreen().borders.bt( -1e6 , 1e6 );

    return useScreen( cW , cS );
}

// Set Plot 3D
CPPlot&
CPPlot::set3Dplot()
{
    cScreen().type = PLOT_3D;
    cScreen().background = WHITE;
    cViewer().setPos(1.8,1.8,1.8).setLook(0,0,-0.2);

    return useScreen( cW , cS );
}

CPPlot&
CPPlot::calibrate( const Matf& K , const float& h , const float& w ,
                   const float& n , const float& f )
{
    cScreen().w = w; cScreen().h = h;
    cScreen().near = n; cScreen().far = f;
    cScreen().fx = K(0,0); cScreen().fy = K(1,1);
    cScreen().cx = K(0,2); cScreen().cy = K(1,2);
    cScreen().calibrate();

    return *this;
}

}
