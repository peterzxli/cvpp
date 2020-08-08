#ifndef HM_ORGN_FEATURE_H
#define HM_ORGN_FEATURE_H

#include <cvpp/containers/matrix.h>
#include <cvpp/containers/sparse.h>

#include <cvpp/auxiliar/timer.h>

namespace cvpp
{

struct FeatureParams
{
    unsigned ndims;
    double gamma,radius,resolution;
    Matd limits,dims;

    FeatureParams()
    {
    }

    FeatureParams( const Matd& lim ,
                   const double& gam = 1.0 ,
                   const double& rad = 2.0 ,
                   const double& res = 0.5 )
    {
        limits = lim , gamma = gam , radius = rad , resolution = res ;

        dims = ( ( limits.r(1) - limits.r(0) ) / resolution ).floor();
        ndims = ( dims + 1.0 ).prod();
    }

};

class HMfeatBase
{

protected:

public:

    unsigned ndims;
    double radius,resolution;
    Matd limits,dims;

public:

    virtual double kernel( const Matd& , const Matd& ) const {}

    Sprd compute( const Matd& X )
    {
        radius = 2.0 , resolution = 0.5 ;

        unsigned nnz = std::ceil( std::pow( 2.0 * std::ceil(
                       radius / resolution + 0.5 ) , 3.0 ) );

        Matd xr( 1 , 3 ), xg( 1 , 3 ) , org = limits.r(0) ;
        Matd roi( 2 , 3 ) , xyz ( 1 , 3 ) , delta( 1 , 3 ) ;

        TriListd list;
        list.reserve( X.r() * nnz );

        forLOOPi( X.r() )
        {
            xr = X.r(i);
            delta.eig() = xr.eig() - org.eig();

            roi.r(0) = ( ( delta - radius ) / resolution ).floor();
            roi.r(1) = ( ( delta + radius ) / resolution ).ceil();

            roi.c(0).Limits( 0 , dims(0) );
            roi.c(1).Limits( 0 , dims(1) );
            roi.c(2).Limits( 0 , dims(2) );

            forLOOPsm( xyz(2) , roi(0,2) , roi(1,2) )
            {   forLOOPeq( xyz(1) , roi(0,1) , roi(1,1) )
                {   forLOOPeq( xyz(0) , roi(0,0) , roi(1,0) )
                    {
                        xg.eig() = org.eig() + xyz.eig() * resolution;

                        list.push_back(
                            Trid( i , dims(0) * ( dims(1) * xyz(2) + xyz(1) ) + xyz(0) ,
                                  kernel( xg , xr ) ) );
                    }
                }
            }
        }

        return Sprd( X.r() , ndims , list );
    }

};

}

#endif
