#include "../gp_base.h"

namespace cvpp
{

double
BaseGP::searchBrent( Matd& alpha , const Matd& dalpha ,
                     const Matd& m , const Matd& y , const Matd& K )
{
    double xlow = 0 , xupp = 2 , tol = 1e-4 , eps = 2.2204e-16;
    unsigned Nitmax = 10;

    double fa = calcInf( alpha + xlow * dalpha , m , y , K );
    double fb = calcInf( alpha + xupp * dalpha , m , y , K );
    unsigned funccount = 2;

    double si,fu;

    double a = xlow , b = xupp;
    double c = 0.5 * ( 3.0 - sqrt( 5.0 ) );
    double v = a + c * ( b - a );
    double w = v , xf = v;
    double d = 0.0 , e = 0.0;

    double x = xf;
    double fx = calcInf( alpha + x * dalpha , m , y , K );
    funccount++;

    double seps = sqrt( eps );
    double fv = fx , fw = fx;
    double xm = 0.5 * ( a + b );
    double tol1 = seps * fabs( xf ) + tol / 3.0;
    double tol2 = 2.0 * tol1;

    while( fabs( xf - xm ) > ( tol2 - 0.5 * ( b - a ) ) )
    {
        double gs = true;

        if( fabs(e) > tol1 )
        {
            gs = false;

            double r = ( xf - w ) * ( fx - fv );
            double q = ( xf - v ) * ( fx - fw );
            double p = ( xf - v ) * q - ( xf - w ) * r;

            q = 2.0 * ( q - r );
            if( q > 0 ) p = -p;
            q = fabs(q); r = e; e = d;

            if( fabs(p) < fabs( 0.5 * q * r ) && p > q * ( a - xf ) && p < q * ( b - xf ) )
            {
                d = p / q;
                x = xf + d;

                if( x - a < tol2 || b - x < tol2 )
                {
                    si = sign( xm - xf ) + ( xm - xf == 0 );
                    d = tol1 * si;
                }
            }
        }

        if( gs )
        {
            if( xf >= xm )
                 e = a - xf;
            else e = b - xf;

            d = c * e;
        }

        si = sign(d) + ( d == 0 );
        x = xf + si * std::max( fabs(d) , tol1 );
        fu = calcInf( alpha + x * dalpha , m , y , K );
        funccount++;

        if( fu <= fx )
        {
            if( x >= xf )
                 a = xf;
            else b = xf;

            v  = w  ; fv = fw ;
            w  = xf ; fw = fx ;
            xf = x  ; fx = fu ;
        }
        else
        {
            if( x < xf )
                 a = x;
            else b = x;

            if( fu <= fw || w == xf )
                v = w , fv = fw , w = x , fw = fu;
            else if( fu <= fv || v == xf || v == w )
                v = x , fv = fu;
        }

        xm = 0.5 * ( a + b );
        tol1 = seps * fabs( xf ) + tol / 3.0;
        tol2 = 2.0 * tol1;

        if( funccount >= Nitmax )
            break;
    }

    if( fa < fx && fa <= fb )
        xf = xlow , fx = fa;
    else if( fb < fx )
        xf = xupp , fx = fb;

    alpha += xf * dalpha;
    return fx;
}

}








