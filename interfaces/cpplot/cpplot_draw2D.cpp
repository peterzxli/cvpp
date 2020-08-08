#include "../cpplot.h"

namespace cvpp
{

// 2D Point
TPL_T CPPlot&
CPPlot::pt2D( const Pt2<T>& pt )
{
    glPushMatrix();
        glBegin( GL_POINTS );
            vertex( pt );
        glEnd();
    glPopMatrix();

    return *this;
}

template CPPlot& CPPlot::pt2D<float>(  const Pt2f& );
template CPPlot& CPPlot::pt2D<double>( const Pt2d& );

// 2D Point
TPL_T CPPlot&
CPPlot::pt2D( const Pt3<T>& pt )
{
    glPushMatrix();
        glBegin( GL_POINTS );
            vertex( pt );
        glEnd();
    glPopMatrix();

    return *this;
}

template CPPlot& CPPlot::pt2D<float>(  const Pt3f& );
template CPPlot& CPPlot::pt2D<double>( const Pt3d& );

// 2D Line
TPL_T CPPlot&
CPPlot::line2D( const Pt2<T>& pt1 ,
                const Pt2<T>& pt2 )
{
    glPushMatrix();
        glBegin( GL_LINES );
            vertex( pt1 );
            vertex( pt2 );
        glEnd();
    glPopMatrix();

    return *this;
}

template CPPlot& CPPlot::line2D<float>(  const Pt2f& , const Pt2f& );
template CPPlot& CPPlot::line2D<double>( const Pt2d& , const Pt2d& );

// 2D Quad
TPL_T CPPlot&
CPPlot::quad2D( const Pt2<T>& pt1 ,
                const Pt2<T>& pt2 )
{
    Pt2<T> pt3( pt1.x , pt2.y );
    Pt2<T> pt4( pt2.x , pt1.y );

    glPushMatrix();
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        glBegin( GL_QUADS );
            vertex( pt1 ); vertex( pt3 );
            vertex( pt2 ); vertex( pt4 );
        glEnd();
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    glPopMatrix();

    return *this;
}

template CPPlot& CPPlot::quad2D<int>(    const Pt2i& , const Pt2i& );
template CPPlot& CPPlot::quad2D<float>(  const Pt2f& , const Pt2f& );
template CPPlot& CPPlot::quad2D<double>( const Pt2d& , const Pt2d& );

// 2D Points
TPL_T CPPlot&
CPPlot::pts2D( const Matrix<T>& mat )
{
    glEnableClientState( GL_VERTEX_ARRAY ); DataType<T> type;
    glVertexPointer( 2 , type.gl() , 0 , &mat.eig_data()[0] );
    glDrawArrays( GL_POINTS , 0 , mat.r() );
    glDisableClientState( GL_VERTEX_ARRAY );

    return *this;
}

template CPPlot& CPPlot::pts2D<float>(  const Matf& );
template CPPlot& CPPlot::pts2D<double>( const Matd& );

// 2D Points
TPL_T CPPlot&
CPPlot::pts2Dc( const Matrix<T>& pts , const Matrix<float>& clr )
{
    glEnableClientState( GL_VERTEX_ARRAY ); DataType<T> type;
    glEnableClientState( GL_COLOR_ARRAY );

    glVertexPointer( 2 , type.gl() , 0 , &pts.eig_data()[0] );
    glColorPointer( 3 , GL_FLOAT , 0 , &clr.eig_data()[0] );
    glDrawArrays( GL_POINTS , 0 , pts.r() );

    glDisableClientState( GL_COLOR_ARRAY );
    glDisableClientState( GL_VERTEX_ARRAY );

    return *this;
}

template CPPlot& CPPlot::pts2Dc<float>(  const Matf& , const Matf& );
template CPPlot& CPPlot::pts2Dc<double>( const Matd& , const Matf& );

// 2D Line
TPL_T CPPlot&
CPPlot::line2D( const Matrix<T>& mat )
{
    glEnableClientState( GL_VERTEX_ARRAY ); DataType<T> type;
    glVertexPointer( 2 , type.gl() , 0 , &mat.eig_data()[0] );
    glDrawArrays( GL_LINE_STRIP , 0 , mat.r() );
    glDisableClientState( GL_VERTEX_ARRAY );

    return *this;
}

template CPPlot& CPPlot::line2D<float>(  const Matf& );
template CPPlot& CPPlot::line2D<double>( const Matd& );

// 2D Loop
TPL_T CPPlot&
CPPlot::loop2D( const Matrix<T>& mat )
{
    glEnableClientState( GL_VERTEX_ARRAY ); DataType<T> type;
    glVertexPointer( 2 , type.gl() , 0 , &mat.eig_data()[0] );
    glDrawArrays( GL_LINE_LOOP , 0 , mat.r() );
    glDisableClientState( GL_VERTEX_ARRAY );

    return *this;
}

template CPPlot& CPPlot::loop2D<float>(  const Matf& );
template CPPlot& CPPlot::loop2D<double>( const Matd& );

// 2D Connect (BASE)
TPL_T CPPlot&
CPPlot::cct2D( const Pts2<T>& pts1 ,
               const Pts2<T>& pts2 )
{
    glPushMatrix();
        glBegin( GL_LINES );
            for( unsigned i = 0 ; i < pts1.n() ; i++ )
            {
                vertex( pts1[i] );
                vertex( pts2[i] );
            }
        glEnd();
    glPopMatrix();

    return *this;
}

template CPPlot& CPPlot::cct2D<float>(  const Pts2f& , const Pts2f& );
template CPPlot& CPPlot::cct2D<double>( const Pts2d& , const Pts2d& );

// 2D Connect (SCREEN)
TPL_T CPPlot&
CPPlot::cct2D( const int& scr1 , const Pts2<T>& pts1 ,
               const int& scr2 , const Pts2<T>& pts2 )
{
    Pts2<T> tmp1 = pts1.clone();
    Pts2<T> tmp2 = pts2.clone();

    unsigned k = 0;
    forLOOPi( tmp1.n() )
    {
        if( res( scr1 ).inside( tmp1[i] ) &&
            res( scr2 ).inside( tmp2[i] ) )
        {
            tmp1[k] = tmp1[i];
            tmp2[k] = tmp2[i];

            k++;
        }
    }

    tmp1.keepFront( k ); screen( scr1 ).remOffset( &tmp1 );
    tmp2.keepFront( k ); screen( scr2 ).remOffset( &tmp2 );

    return cct2D( tmp1 , tmp2 );
}

template CPPlot& CPPlot::cct2D<float>(  const int& , const Pts2f& , const int& , const Pts2f& );
template CPPlot& CPPlot::cct2D<double>( const int& , const Pts2d& , const int& , const Pts2d& );

TPL_T CPPlot&
CPPlot::rect2D( const Rect2<T>& rect )
{
    line2D( Pt2f( rect.x              , rect.y               ) , Pt2f( rect.x              , rect.y + rect.height ) );
    line2D( Pt2f( rect.x              , rect.y + rect.height ) , Pt2f( rect.x + rect.width , rect.y + rect.height ) );
    line2D( Pt2f( rect.x + rect.width , rect.y + rect.height ) , Pt2f( rect.x + rect.width , rect.y               ) );
    line2D( Pt2f( rect.x + rect.width , rect.y               ) , Pt2f( rect.x              , rect.y               ) );

    return *this;
}

template CPPlot& CPPlot::rect2D<int>(    const Rect2i& );
template CPPlot& CPPlot::rect2D<float>(  const Rect2f& );
template CPPlot& CPPlot::rect2D<double>( const Rect2d& );

// 2D Ellipse (FLOAT)
CPPlot&
CPPlot::ellipse2D( const Matrix<float>& mean ,
                   const Matrix<float>& cov )
{
    Matrix<float> val,vec;
    Matrix<float> Rt(4,4); Rt.setIdentity();

    cov.eigen( val , vec );
    Rt.blu(2) = vec; Rt.b(0,3,2,1) = mean.t();

    float radx = 2.0 * sqrt( val(0) );
    float rady = 2.0 * sqrt( val(1) );

    glPushMatrix();
    glMultMatrixf( Rt.t().eig_data() );
    glBegin(GL_LINE_LOOP);
    for( int i = 0 ; i < 360 ; i += 10 )
        glVertex2f( cos( i * PI180 ) * radx , sin( i * PI180 ) * rady );
    glEnd();
    glBegin(GL_LINES);
        glVertex2f( - radx , 0 ); glVertex2f( + radx , 0 );
        glVertex2f( 0 , - rady ); glVertex2f( 0 , + rady );
    glEnd();
    glPopMatrix();

    return *this;
}

// 2D Ellipse (DOUBLE)
CPPlot&
CPPlot::ellipse2D( const Matrix<double>& mean ,
                   const Matrix<double>& cov )
{
    Matrix<double> val,vec;
    Matrix<double> Rt(4,4); Rt.setIdentity();

    cov.eigen( val , vec );
    Rt.blu(2) = vec; Rt.b(0,3,2,1) = mean.t();

    double radx = 2.0 * sqrt( val(0) );
    double rady = 2.0 * sqrt( val(1) );

    glPushMatrix();
    glMultMatrixd( Rt.t().eig_data() );
    glBegin(GL_LINE_LOOP);
    for( int i = 0 ; i < 360 ; i += 10 )
        glVertex2d( cos( i * PI180 ) * radx , sin( i * PI180 ) * rady );
    glEnd();
    glBegin(GL_LINES);
        glVertex2d( - radx , 0 ); glVertex2d( + radx , 0 );
        glVertex2d( 0 , - rady ); glVertex2d( 0 , + rady );
    glEnd();
    glPopMatrix();

    return *this;
}

// 2D Ellipses
TPL_T CPPlot&
CPPlot::ellipse2D( const Matrix<T>& mean ,
                   const Seq<Matrix<T>>& cov )
{
    forLOOPi( mean.r() )
        ellipse2D( mean.r(i) , cov[i] );
    return *this;
}

template CPPlot& CPPlot::ellipse2D<float>(  const Matf& , const SeqMatf& );
template CPPlot& CPPlot::ellipse2D<double>( const Matd& , const SeqMatd& );

// 2D Ellipses
TPL_T CPPlot&
CPPlot::ellipse2D( const Seq<Matrix<T>>& mean ,
                   const Seq<Matrix<T>>& cov )
{
    forLOOPi( mean.size() )
        ellipse2D( mean[i] , cov[i] );
    return *this;
}

template CPPlot& CPPlot::ellipse2D<float>(  const SeqMatf& , const SeqMatf& );
template CPPlot& CPPlot::ellipse2D<double>( const SeqMatd& , const SeqMatd& );

// 2D Epipoles
CPPlot&
CPPlot::epip2D( const CV& epips )
{
    Pts2f xi,xf;
    forLOOPi( epips.rows )
    {
        xi.push( Pt2f( ( - epips.at<float>(i,1) * cSres().u() - epips.at<float>(i,2) ) / epips.at<float>(i,0) , cSres().u() ) );
        xf.push( Pt2f( ( - epips.at<float>(i,1) * cSres().d() - epips.at<float>(i,2) ) / epips.at<float>(i,0) , cSres().d() ) );
    }
    cct2D( xi , xf );
}

}

