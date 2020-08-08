#include "../cpplot.h"

namespace cvpp
{

// Draw Axes
CPPlot&
CPPlot::axesBase()
{
    SStream ss;

    float ntx = cScreen().nTickX;
    float nty = cScreen().nTickY;
    float ntz = cScreen().nTickZ;

    float ix,iy,iz,val;

    float len;
    unsigned prec = 2;

    switch( cScreen().type )
    {
        case PLOT_2D:

            color( BLACK ).lineWidth( 3 );

            ss.str( cScreen().title );
            len = cScreen().title.length() / 2.0;
            text2D( 0.5 - 0.0175 * len , - 0.025 , ss.str() );

            glBegin( GL_LINES );

                vertex( cSres().l() , cSres().u() );
                vertex( cSres().r() , cSres().u() );
                vertex( cSres().l() , cSres().u() );
                vertex( cSres().l() , cSres().d() );

                for( int i = 0 ; i <= ntx ; i++ )
                {
                    vertex2D( float(i) / ntx , - 0.02 );
                    vertex2D( float(i) / ntx , + 0.02 );
                }

                for( int i = 0 ; i <= nty ; i++ )
                {
                    vertex2D( - 0.015 , float(i) / nty );
                    vertex2D( + 0.015 , float(i) / nty );
                }

            glEnd();

            lineWidth( 1 );

            glLineStipple( 1 , 0x00FF );
            glEnable( GL_LINE_STIPPLE );
            glBegin( GL_LINES );

                for( int i = 0 ; i <= ntx ; i++ )
                {
                    vertex2D( float(i) / ntx , 0.0 );
                    vertex2D( float(i) / ntx , 1.0 );
                }

                for( int i = 0 ; i <= nty ; i++ )
                {
                    vertex2D( 0.0 , float(i) / nty );
                    vertex2D( 1.0 , float(i) / nty );
                }

            glEnd();
            glDisable( GL_LINE_STIPPLE );

            for( int i = 0 ; i <= ntx ; i++ )
            {
                val = cSres().l() + cSres().w() * float(i) / ntx;

                ss.str(""); ss << std::setprecision( prec ) << std::fixed << val;
                text( cSres().l() + cSres().w() * ( float(i) / ntx - ss.str().length() * 0.01 ) ,
                      cSres().u() - 0.08 * cSres().h() , ss.str() );
            }

            for( int i = 0 ; i <= nty ; i++ )
            {
                val = cSres().u() + cSres().h() * float(i) / nty;

                ss.str(""); ss << std::setprecision( prec ) << std::fixed << val;
                text2D( - 0.01 - 0.02 * ss.str().length() , 1.00 - float(i) / nty + 0.015 , ss.str() );
            }

            glScissor( cSbrd().l() + 0.155 * cSbrd().w() ,
                       cWbrd().h() - cSbrd().d() + 0.085 * cSbrd().h() ,
                       0.77 * cSbrd().w() , 0.83 * cSbrd().h() );

            break;

        case PLOT_3D:

            color( BLACK ).lineWidth( 3 );

            glBegin( GL_LINES );

                vertex( 0.0 , 0.0 , 0.0 ); vertex( 1.0 , 0.0 , 0.0 );
                vertex( 0.0 , 0.0 , 0.0 ); vertex( 0.0 , 1.0 , 0.0 );
                vertex( 0.0 , 0.0 , 0.0 ); vertex( 0.0 , 0.0 , 1.0 );
                vertex( 1.0 , 0.0 , 0.0 ); vertex( 1.0 , 1.0 , 0.0 );
                vertex( 1.0 , 1.0 , 0.0 ); vertex( 0.0 , 1.0 , 0.0 );
                vertex( 0.0 , 1.0 , 0.0 ); vertex( 0.0 , 1.0 , 1.0 );
                vertex( 0.0 , 1.0 , 1.0 ); vertex( 0.0 , 0.0 , 1.0 );
                vertex( 0.0 , 0.0 , 1.0 ); vertex( 1.0 , 0.0 , 1.0 );
                vertex( 1.0 , 0.0 , 1.0 ); vertex( 1.0 , 0.0 , 0.0 );

                for( int i = 0 ; i <= ntx ; i++ )
                {
                    ix = float(i) / ntx;

                    switch ( cScreen().view )
                    {
                        case 0: case 1: case 2:
                            vertex( ix , 0.95 , 0.00 );
                            vertex( ix , 1.05 , 0.00 );
                            break;
                        case 3:
                            vertex( ix , 0.00 , 0.95 );
                            vertex( ix , 0.00 , 1.05 );
                            break;
                    }
                }

                for( int i = 0 ; i <= nty ; i++ )
                {
                    iy = float(i) / nty;

                    switch ( cScreen().view )
                    {
                        case 0: case 1: case 2:
                            vertex( 0.95 , iy , 0.00 );
                            vertex( 1.05 , iy , 0.00 );
                            break;
                        case 3:
                            vertex( 0.00 , iy , 0.95 );
                            vertex( 0.00 , iy , 1.05 );
                            break;
                    }
                }

                for( int i = 0 ; i <= ntz ; i++ )
                {
                    iz = float(i) / ntz;

                    switch( cScreen().view )
                    {
                        case 0: case 2:
                            vertex( 0.95 , 0.00 , iz );
                            vertex( 1.05 , 0.00 , iz );
                            break;
                        case 1: case 3:
                            vertex( 0.00 , 0.95 , iz );
                            vertex( 0.00 , 1.05 , iz );
                            break;
                    }
                }

            glEnd();

            lineWidth( 1 );

            glLineStipple( 1 , 0x00FF );
            glEnable( GL_LINE_STIPPLE );
            glBegin( GL_LINES );

                for( int i = 0 ; i <= ntx ; i++ )
                {
                    ix = float(i) / ntx;

                    vertex( ix , 0.0 , 0.0 );
                    vertex( ix , 1.0 , 0.0 );

                    vertex( ix , 0.0 , 0.0 );
                    vertex( ix , 0.0 , 1.0 );
                }

                for( int i = 0 ; i <= nty ; i++ )
                {
                    iy = float(i) / nty;

                    vertex( 0.0 , iy , 0.0 );
                    vertex( 1.0 , iy , 0.0 );

                    vertex( 0.0 , iy , 0.0 );
                    vertex( 0.0 , iy , 1.0 );
                }

                for( int i = 0 ; i <= ntz ; i++ )
                {
                    iz = float(i) / ntz;

                    vertex( 0.0 , 0.0 , iz );
                    vertex( 1.0 , 0.0 , iz );

                    vertex( 0.0 , 0.0 , iz );
                    vertex( 0.0 , 1.0 , iz );
                }

            glEnd();
            glDisable( GL_LINE_STIPPLE );

            for( int i = 0 ; i <= ntx ; i++ )
            {
                val = cSres().l() + cSres().w() * float(i) / ntx;
                ss.str(""); ss << std::setprecision( prec ) << std::fixed << val;

                switch( cScreen().view )
                {
                    case 0: text( float(i)/ntx , 1.0 , 0.0 , ss.str() ); break;
                    case 1: text( float(i)/ntx , 1.0 , 0.0 , ss.str() ); break;
                    case 2: text( float(i)/ntx , 1.0 , 0.0 , ss.str() ); break;
                    case 3: text( float(i)/ntx , 0.0 , 1.0 , ss.str() ); break;
                }
            }

            for( int i = 0 ; i <= nty ; i++ )
            {
                val = cSres().u() + cSres().h() * float(i) / nty;
                ss.str(""); ss << std::setprecision( prec ) << std::fixed << val;

                switch( cScreen().view )
                {
                    case 0: text( 1.0 , float(i)/nty , 0.0 , ss.str() ); break;
                    case 1: text( 1.0 , float(i)/nty , 0.0 , ss.str() ); break;
                    case 2: text( 1.0 , float(i)/nty , 0.0 , ss.str() ); break;
                    case 3: text( 0.0 , float(i)/nty , 1.0 , ss.str() ); break;
                }
            }

            for( int i = 0 ; i <= ntz ; i++ )
            {
                val = cSres().b() + cSres().e() * float(i) / ntz;
                ss.str(""); ss << std::setprecision( prec ) << std::fixed << val;

                switch( cScreen().view )
                {
                    case 0: text( 1.0 , 0.0 , float(i)/ntz , ss.str() ); break;
                    case 1: text( 0.0 , 1.0 , float(i)/ntz , ss.str() ); break;
                    case 2: text( 1.0 , 0.0 , float(i)/ntz , ss.str() ); break;
                    case 3: text( 0.0 , 1.0 , float(i)/ntz , ss.str() ); break;
                }
            }

            switch( cScreen().view )
            {
                case 0:
                    text( 0.5 , 1.2 , 0.0 , "X" );
                    text( 1.2 , 0.5 , 0.0 , "Y" );
                    text( 1.2 , 0.0 , 0.5 , "Z" );
                    break;

                case 1:
                    text( 0.5 , 1.2 , 0.0 , "X" );
                    text( 1.2 , 0.5 , 0.0 , "Y" );
                    text( 0.0 , 1.2 , 0.5 , "Z" );
                    break;

                case 2:
                    text( 0.5 , 1.2 , 0.0 , "X" );
                    text( 1.2 , 0.5 , 0.0 , "Y" );
                    text( 1.2 , 0.0 , 0.5 , "Z" );
                    break;

                case 3:
                    text( 0.5 , 0.0 , 1.2 , "X" );
                    text( 0.0 , 0.5 , 1.2 , "Y" );
                    text( 0.0 , 1.2 , 0.5 , "Z" );
                    break;
            }

            break;
    }

    return *this;
}

// Prepare Plot
CPPlot&
CPPlot::preparePlot()
{
    if( cScreen().type == PLOT_3D )
    {
        glScalef( 1.0 / cSres().w() , 1.0 / cSres().h() , 1.0 / cSres().e() );
        glTranslatef( - cSres().l() , - cSres().u() , - cSres().b() );
    }

    return *this;
}

//// Prepare Plot (Buffer)
//CPPlot&
//CPPlot::preparePlot( const int& idx )
//{
//    return preparePlot( buffer(idx).minX , buffer(idx).maxX ,
//                        buffer(idx).minY , buffer(idx).maxY ,
//                        buffer(idx).minZ , buffer(idx).maxZ );
//}

//// Prepare Plot (Matrix)
//TPL_T CPPlot&
//CPPlot::preparePlot( const Matrix<T>& mat )
//{
//    if( mat.c() == 2 )
//        return preparePlot( mat.c(0).min() , mat.c(0).max() ,
//                            mat.c(1).min() , mat.c(1).max() , -1.0 , +1.0 );

//    if( mat.c() == 3 )
//        return preparePlot( mat.c(0).min() , mat.c(0).max() ,
//                            mat.c(1).min() , mat.c(1).max() ,
//                            mat.c(2).min() , mat.c(2).max() );
//}

//template CPPlot& CPPlot::preparePlot<float>( const Matf& );
//template CPPlot& CPPlot::preparePlot<double>( const Matd& );

//// Prepare Plot (Value)
//CPPlot&
//CPPlot::preparePlot( const float& l , const float& r ,
//                     const float& u , const float& d ,
//                     const float& b , const float& t )
//{
//    if( cScreen().type == PLOT_2D ||
//        cScreen().type == PLOT_3D )
//    {
//        if( !cScreen().lockX ) cSres().lr( l , r );
//        if( !cScreen().lockY ) cSres().ud( u , d );
//        if( !cScreen().lockZ ) cSres().bt( b , t );
//    }

//    cSores() = cSres();
//    return preparePlot();
//}

// Free Axes
CPPlot&
CPPlot::freeAxes()
{
    cScreen().lockX = false;
    cScreen().lockY = false;
    cScreen().lockZ = false;

    return *this;
}

// Set Axes (Value)
CPPlot&
CPPlot::setAxes( const float& l , const float& r ,
                 const float& u , const float& d ,
                 const float& b , const float& t )
{
    if( cScreen().changed )
        return *this;

    if( r - l > 0 ) cScreen().lockX = true;
    if( d - u > 0 ) cScreen().lockY = true;
    if( t - b > 0 ) cScreen().lockZ = true;

    cSres().lurd( l , u , r , d ).bt( b , t ); cSores() = cSres();
    return useScreen( cW , cS );
}

// Set Axes (Matrix)
TPL_T CPPlot&
CPPlot::setAxes( const Matrix<T>& mat1 , const Matrix<T>& mat2 ,
                 const float& px , const float& py , const float& pz )
{
    return setAxes( mat1.appR(mat2) , px , py , pz );
}

template CPPlot& CPPlot::setAxes<float>( const Matf& , const Matf&, const float& , const float& , const float& );
template CPPlot& CPPlot::setAxes<double>( const Matd& , const Matd&, const float& , const float& , const float& );

// Set Axes (Buffer)
CPPlot&
CPPlot::setAxes( const int& idx )
{
    float minx = buffers[idx].minX , maxx = buffers[idx].maxX , dx = maxx - minx;
    float miny = buffers[idx].minY , maxy = buffers[idx].maxY , dy = maxy - miny;
    float minz = buffers[idx].minZ , maxz = buffers[idx].maxZ , dz = maxz - minz;

    float px = 0.0;
    float py = ( dz >= 0 ? 0.0 : 0.1 );
    float pz = ( dz >= 0 ? 0.1 : 0.0 );

    dx *= px , dy *= py , dz *= pz;

    if( minx == maxx ) minx = -1 , maxx = +1 , dx = 0;
    if( miny == maxy ) miny = -1 , maxy = +1 , dy = 0;
    if( minz == maxz ) minz = -1 , maxz = +1 , dz = 0;

    return setAxes( minx - dx , maxx + dx ,
                    miny - dy , maxy + dy ,
                    minz - dz , maxz + dz );
}

// Set Axes (Matrix)
TPL_T CPPlot&
CPPlot::setAxes( const Matrix<T>& mat , const float& px , const float& py , const float& pz )
{
    T minx,maxx,miny,maxy,minz,maxz;
    T dx,dy,dz;

    if( cScreen().type == PLOT_2D )
    {
        if( mat.empty() )
        {
            minx = -1 , maxx = +1 , dx = 0;
            miny = -1 , maxy = +1 , dy = 0;
        }
        else
        {
            minx = mat.c(0).min() , maxx = mat.c(0).max() , dx = px * ( maxx - minx );
            miny = mat.c(1).min() , maxy = mat.c(1).max() , dy = py * ( maxy - miny );

            if( minx == maxx ) minx = minx - 0.1 , maxx = maxx + 0.1;
            if( miny == maxy ) miny = miny - 0.1 , maxy = maxy + 0.1;
        }

        return setAxes( minx - dx , maxx + dx ,
                        miny - dy , maxy + dy );
    }

    if( cScreen().type == PLOT_3D )
    {
        if( mat.empty() )
        {
            minx = -1 , maxx = +1;
            miny = -1 , maxy = +1;
            minz = -1 , maxz = +1;
        }
        else
        {
            minx = mat.c(0).min() , maxx = mat.c(0).max() , dx = px * ( maxx - minx );
            miny = mat.c(1).min() , maxy = mat.c(1).max() , dy = py * ( maxy - miny );
            minz = mat.c(2).min() , maxz = mat.c(2).max() , dz = pz * ( maxz - minz );

            if( minx == maxx ) minx = minx - 0.1 , maxx = maxx + 0.1;
            if( miny == maxy ) miny = miny - 0.1 , maxy = maxy + 0.1;
            if( minz == maxz ) minz = minz - 0.1 , maxz = maxz + 0.1;
        }

        return setAxes( minx - dx , maxx + dx ,
                        miny - dy , maxy + dy ,
                        minz - dz , maxz + dz );
    }
}

template CPPlot& CPPlot::setAxes<float>( const Matf& , const float& , const float& , const float& );
template CPPlot& CPPlot::setAxes<double>( const Matd& , const float& , const float& , const float& );

// Set Axis X
TPL_T CPPlot&
CPPlot::setAxisX( const T& l , const T& r )
{
    cScreen().lockX = true;
    cScreen().resolution.lr( l , r );
    return useScreen( cW , cS );
}

template CPPlot& CPPlot::setAxisX<float>( const float& , const float& );
template CPPlot& CPPlot::setAxisX<double>( const double& , const double& );

// Set Axis Y
TPL_T CPPlot&
CPPlot::setAxisY( const T& u , const T& d )
{
    cScreen().lockY = true;
    cScreen().resolution.ud( u , d );
    return useScreen( cW , cS );
}

template CPPlot& CPPlot::setAxisY<float>( const float& , const float& );
template CPPlot& CPPlot::setAxisY<double>( const double& , const double& );

// Set Axis Z
TPL_T CPPlot&
CPPlot::setAxisZ( const T& b , const T& t )
{
    cScreen().lockZ = true;
    cScreen().resolution.bt( b , t );
    return useScreen( cW , cS );
}

template CPPlot& CPPlot::setAxisZ<float>( const float& , const float& );
template CPPlot& CPPlot::setAxisZ<double>( const double& , const double& );

}

