#include "../cpplot.h"

namespace cvpp
{

// 3D Point
TPL_T CPPlot&
CPPlot::pt3D( const Pt2<T>& pt )
{
    glPushMatrix();
        glBegin( GL_POINTS );
            vertex( pt );
        glEnd();
    glPopMatrix();

    return *this;
}

template CPPlot& CPPlot::pt3D<float>(  const Pt2f& );
template CPPlot& CPPlot::pt3D<double>( const Pt2d& );

// 3D Point
TPL_T CPPlot&
CPPlot::pt3D( const Pt3<T>& pt )
{
    glPushMatrix();
        glBegin( GL_POINTS );
            vertex( pt );
        glEnd();
    glPopMatrix();

    return *this;
}

template CPPlot& CPPlot::pt3D<float>(  const Pt3f& );
template CPPlot& CPPlot::pt3D<double>( const Pt3d& );

// 3D Line
TPL_T CPPlot&
CPPlot::line3D( const Pt3<T>& pt1 ,
                const Pt3<T>& pt2 )
{
    glPushMatrix();
        glBegin( GL_LINES );
            vertex( pt1 );
            vertex( pt2 );
        glEnd();
    glPopMatrix();

    return *this;
}

template CPPlot& CPPlot::line3D<float>(  const Pt3f& , const Pt3f& );
template CPPlot& CPPlot::line3D<double>( const Pt3d& , const Pt3d& );

// 3D Points
TPL_T CPPlot&
CPPlot::pts3D( const Matrix<T>& mat )
{
    glEnableClientState( GL_VERTEX_ARRAY ); DataType<T> type;
    glVertexPointer( 3 , type.gl() , 0 , &mat.eig_data()[0] );
    glDrawArrays( GL_POINTS , 0 , mat.r() );
    glDisableClientState( GL_VERTEX_ARRAY );

    return *this;
}

template CPPlot& CPPlot::pts3D<float>(  const Matf& );
template CPPlot& CPPlot::pts3D<double>( const Matd& );

// 3D Line
TPL_T CPPlot&
CPPlot::line3D( const Matrix<T>& mat )
{
    glEnableClientState( GL_VERTEX_ARRAY ); DataType<T> type;
    glVertexPointer( 3 , type.gl() , 0 , &mat.eig_data()[0] );
    glDrawArrays( GL_LINE_STRIP , 0 , mat.r() );
    glDisableClientState( GL_VERTEX_ARRAY );

    return *this;
}

template CPPlot& CPPlot::line3D<float>(  const Matf& );
template CPPlot& CPPlot::line3D<double>( const Matd& );

// 3D Loop
TPL_T CPPlot&
CPPlot::loop3D( const Matrix<T>& mat )
{
    glEnableClientState( GL_VERTEX_ARRAY ); DataType<T> type;
    glVertexPointer( 3 , type.gl() , 0 , &mat.eig_data()[0] );
    glDrawArrays( GL_LINE_LOOP , 0 , mat.r() );
    glDisableClientState( GL_VERTEX_ARRAY );

    return *this;
}

template CPPlot& CPPlot::loop3D<float>(  const Matf& );
template CPPlot& CPPlot::loop3D<double>( const Matd& );

// 3D Connect
TPL_T CPPlot&
CPPlot::cct3D( const Pt3<T>& origin ,
               const Pts3<T>& pts )
{
    glPushMatrix();
        glBegin( GL_LINES );
            for( unsigned i = 0 ; i < pts.n() ; i++ )
            {
                vertex( origin );
                vertex( pts[i] );
            }
        glEnd();
    glPopMatrix();

    return *this;
}

template CPPlot& CPPlot::cct3D<float>( const Pt3f& , const Pts3f& );
template CPPlot& CPPlot::cct3D<double>( const Pt3d& , const Pts3d& );

// 3D Connect
TPL_T CPPlot&
CPPlot::cct3D( const Pts3<T>& pts1 ,
               const Pts3<T>& pts2 )
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

template CPPlot& CPPlot::cct3D<float>(  const Pts3f& , const Pts3f& );
template CPPlot& CPPlot::cct3D<double>( const Pts3d& , const Pts3d& );

// 3D Ellipse (FLOAT)
CPPlot&
CPPlot::ellipse3D( const Matrix<float>& mean ,
                   const Matrix<float>& cov )
{
    Matrix<float> val,vec;
    Matrix<float> Rt(4,4); Rt.setIdentity();

    cov.eigen( val , vec );
    Rt.blu(3) = vec; Rt.b(0,3,3,1) = mean.t();

    glPushMatrix();
    glMultMatrixf( Rt.t().eig_data() );
        glScalef( 2.0 * sqrt(val(0)) , 2.0 * sqrt(val(1)) , 2.0 * sqrt(val(2)) );
        gluSphere(quad,1.00,100,20);
    glPopMatrix();

    return *this;
}

// 3D Ellipse (DOUBLE)
CPPlot&
CPPlot::ellipse3D( const Matrix<double>& mean ,
                   const Matrix<double>& cov )
{
    Matrix<double> val,vec;
    Matrix<double> Rt(4,4); Rt.setIdentity();

    cov.eigen( val , vec );
    Rt.blu(3) = vec; Rt.b(0,3,3,1) = mean.t();

    glPushMatrix();
    glMultMatrixd( Rt.t().eig_data() );
        glScaled( 2.0 * sqrt(val(0)) , 2.0 * sqrt(val(1)) , 2.0 * sqrt(val(2)) );
        gluSphere(quad,1.00,100,20);
    glPopMatrix();

    return *this;
}

// 3D Ellipses
TPL_T CPPlot&
CPPlot::ellipse3D( const SeqMatrix<T>& mean ,
                   const SeqMatrix<T>& cov )
{
    for( unsigned i = 0 ; i < mean.size() ; i++ )
        ellipse3D( mean[i] , cov[i] );
    return *this;
}

template CPPlot& CPPlot::ellipse3D<float>(  const SeqMatf& , const SeqMatf& );
template CPPlot& CPPlot::ellipse3D<double>( const SeqMatd& , const SeqMatd& );

}
