#include "./rks_original.h"

namespace cvpp
{

RKSoriginal&
RKSoriginal::train( const Matd& X , const Matd& Y ,
                    const int& f , const double& l , const double& n )
{
    Z = MatXXd( X.c() , f/2 ).setRandn( 0 , l );
    I = MatIDTYd( f , n );

    phi = feat->calc( X * Z );
    wgt = ( phi.t() * phi + I ).bslash( phi.t() * Y );

    return *this;
}

RKSoriginal&
RKSoriginal::update( const Matd& X , const Matd& Y )
{
    phi = feat->calc( X * Z );
    wgt = ( phi.t() * phi + I ).bslash( phi.t() * Y );

    return *this;
}

Matd
RKSoriginal::query( const Matd& X ) const
{
    return feat->calc( X * Z ) * wgt;
}

}
