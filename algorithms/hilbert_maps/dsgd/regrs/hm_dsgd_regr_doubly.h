#ifndef HM_DSGD_REGRESSOR_DOUBLY_H
#define HM_DSGD_REGRESSOR_DOUBLY_H

#include "./hm_dsgd_regr_base.h"

namespace cvpp
{

class HMregrDoubly : public HMregrBase
{

protected:

public:

    HMregrDoubly() : HMregrBase()
    {
    }

    int ridx( const int& i ) const
    {
        return r * n + i * f;
    }

    Matd kernel( const Matd& X , const int& ri ) const
    {
        randomise( ridx(ri) );
        Matd Z = MatXXd( d , ff ).setRandn( 0 , sqrt( 2.0 * ls ) );
        return feat->calc( X * Z ) / sqrt( ff );
    }

    const void train()
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

            wgt.r( widx , f ) += - step * ( ( K + I ).bslash( ( phi.t() * E ) / b ) );

            if( reg > 1e-6 )
                wgt.ru( ii * f ) *= ( 1 - step * reg );

            disp( "*****************************************************************" ,
                  i , iters , widx , widx + f , n , bidx , bidx + b , t , timer.tick() );
        }
    }

    Matd query( const Matd& X , int iters = -1 ) const
    {
        if( iters == -1 ) iters = nf;

        Matd mf = MatZEROSd( X.r() , k );
        forLOOPj( iters ) mf += kernel( X , j % nf ) * wgt.r( ( j * f ) % n , f ) ;

        return mf;
    }

};

}

#endif



