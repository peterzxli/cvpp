#include "dsgd_original.h"

namespace cvpp
{

// Constructor
DSGDoriginal::DSGDoriginal( RKSfeatBase* feat )
{
    this->feat = feat;
}

// Destructor
DSGDoriginal::~DSGDoriginal()
{
    delete feat;
}

Matd
DSGDoriginal::kernel( const Matd& X , const int& ri ) const
{
    randomise( ridx(ri) );
    Matd Z = MatXXd( d , ff ).setRandn( 0 , sqrt( 2.0 * ls ) );
    return feat->calc( X * Z ) / sqrt( ff );
}

int
DSGDoriginal::ridx( const int& i ) const
{
    return r * n + i * f;
}

DSGDoriginal&
DSGDoriginal::setData( const Matd& Xtr , const Matd& Ytr )
{
    this->Xtr = Xtr ; this->Ytr = Ytr ;

    trainY = Ytr.lblMat() ;
    k = trainY.c() , t = Xtr.r() , d = Xtr.c() ;
}

DSGDoriginal&
DSGDoriginal::setParams( const double& p1 , const double& p2 , const double& p3 , const double& p4 ,
                         const unsigned& p5 , const unsigned& p6 , const unsigned& p7 )
{
    Matd distmat = Xtr.sr( 10 ).vecDistRows();
    double med = distmat.median();

    r = 1 ; ls = 1.0 / pow( p1 * med , 2.0 ) ;
    reg = p2 , step0 = p3 , step1 = p4 , n = p5 , f = p6 , b = p7 ;
    ff = f / feat->mlt();

    nf = std::floor( n / f ) , tb = std::floor( t / b );
    iters = std::max( nf , tb );

    wgt = MatZEROSd( n , k );
    I = MatIDTYd( f , reg + 1e-7 );

    return *this;
}

// Train
DSGDoriginal&
DSGDoriginal::train()
{
    Timer timer;

    double step = step0 / ( 1.0 + step1 );

    forLOOPi( iters )
    {
        int bidx = ( i * b ) % t;
        int widx = ( i * f ) % n;
        int ii = std::min( i , nf );

        Xbt = Xtr.r( bidx , b );

        Matd mf = query( Xbt , ii );
        Matd phi = kernel( Xbt , i % nf );

        Matd max = mf.maxCols();
        Matd softmax = ( mf - max ).exp();
        softmax /= softmax.sumCols();

        Matd K = ( phi.t() * phi ) / b;
        Matd E = softmax - trainY.r( bidx , b );

        wgt.r( widx , f ) += - step * ( ( K + I ).bslash(
                                        ( phi.t() * E ) / b + reg * wgt.r( widx , f ) ) );

        if( reg > 1e-6 )
            wgt.ru( ii * f ) *= ( 1 - step * reg );

        disp( "*****************************************************************" ,
              i , iters , widx , widx + f , n , bidx , bidx + b , t , timer.tick() );
    }

    return *this;
}

// Run
Matd
DSGDoriginal::query( const Matd& X , int iters ) const
{
    if( iters == -1 ) iters = nf;

    Matd mf = MatZEROSd( X.r() , k );
    forLOOPj( iters ) mf += kernel( X , j % nf ) * wgt.r( ( j * f ) % n , f ) ;

    return mf;
}

}

