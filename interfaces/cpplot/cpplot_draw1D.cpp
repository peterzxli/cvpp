#include "../cpplot.h"

namespace cvpp
{

// 1D Ellipse (Mean/Cov)
TPL_T CPPlot&
CPPlot::ellipse1D( const T& m , const T& v , const T& y )
{
    T s = 2.0 * sqrt( v );
    T p = s / 50;

    lineWidth(10);
    line2D( Pt2<T>( m - s - p , y ) , Pt2<T>( m - s + p , y ) );
    line2D( Pt2<T>( m + s - p , y ) , Pt2<T>( m + s + p , y ) );

    lineWidth(3);
    line2D( Pt2<T>( m - s , y ) , Pt2<T>( m + s , y ) );

    return *this;
}

template CPPlot& CPPlot::ellipse1D<float>( const float& , const float& , const float& );
template CPPlot& CPPlot::ellipse1D<double>( const double& , const double& , const double& );

// 1D Ellipse (Mean/Cov)
TPL_T CPPlot&
CPPlot::ellipse1D( const Matrix<T>& m , const Matrix<T>& s , const Matrix<T>& y )
{
    forLOOPi( m.r() )
        ellipse1D( m(i) , s(i) , y(i) );
    return *this;
}

template CPPlot& CPPlot::ellipse1D<float>( const Matf& , const Matf& , const Matf& );
template CPPlot& CPPlot::ellipse1D<double>( const Matd& , const Matd& , const Matd& );

}
