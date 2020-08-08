#ifndef HM_SHAPE_FEATURE_H
#define HM_SHAPE_FEATURE_H

#include <cvpp/auxiliar/macros.h>
#include <cvpp/auxiliar/timer.h>

#include <cvpp/containers/matrix.h>
#include <cvpp/containers/sparse.h>

#include <cvpp/algorithms/kdtree/kdtree.h>

namespace cvpp
{

class HMfeatBase
{

public:

    double rad,thr;
    unsigned ndims;
    Matd type;

public:

    HMfeatBase()
    {
        ndims = 0;
    }

    HMfeatBase( const double& r ) : HMfeatBase()
    {
        rad = r;
    }

    HMfeatBase( const double& r , const double& t ) : HMfeatBase( r )
    {
        thr = t;
    }

    const void setType( const Matd& type )
    {
        this->type = type;
    }

    virtual double kernel( const REIG<double>& , const REIG<double>& ,
                           const Eigd& , const Eigd& , const Eigd& , const Eigd& ,
                           const int& = -1 ) const { disp("BASE HM KERNEL"); }


    // Nearest neighbours
    const  void nearest( const Eigd& X , STDd& N , STDi& I ,
                         const Matd& Z , const SeqMatd& iS ) const
    {
        forLOOPi( N.size() )
            N[i] = 1e12;

        forLOOPi( Z.r() )
        {
            Eigd D = X - Z.row(i);
            double val = ( D * iS[i].eig() * D.transpose() )(0);

            forLOOPj( N.size() )
            {   if( val < N[j] )
                {
                    for( int k = N.size() - 1 ; k > j ; k-- )
                    { N[k] = N[k-1]; I[k] = I[k-1]; }
                    N[j] = val; I[j] = i; break;
                }
            }
        }
    }

    // Nearest neighbours
    const void nearest( const Eigd& X , const double& Y , STDd& N , STDi& I ,
                        const Matd& Z , const Matd& W , const SeqMatd& iS ) const
    {
        forLOOPi( N.size() )
            N[i] = 1e12;

        forLOOPi( Z.r() )
        {
            if( Y == W(i) )
            {
                Eigd D = X - Z.row(i);
                double val = ( D * iS[i].eig() * D.transpose() )(0);

                forLOOPj( N.size() )
                {   if( val < N[j] )
                    {
                        for( int k = N.size() - 1 ; k > j ; k-- )
                        { N[k] = N[k-1]; I[k] = I[k-1]; }
                        N[j] = val; I[j] = i; break;
                    }
                }
            }
        }
    }

    // Compute
    Matd compute( const Matd& X , const Matd& Z , const SeqMatd& iS , const SeqMatd& S ,
                  const SeqMatd& vals , const SeqMatd& vecs , const int& f ) const
    {
        unsigned k;
        Matd F( X.r() , 2 * f );

        STDd N( f ) ; STDi I( f );
        forLOOPi( X.r() )
        {
            nearest( X.row(i) , N , I , Z , iS );

            forLOOPj( f )
            {
                k = I[j];

                F( i , 2*j   ) = k;
                F( i , 2*j+1 ) = kernel( X.row(i) , Z.row(k) , S[k].eig() , iS[k].eig() ,
                                         vals[k].eig() , vecs[k].eig() , type(k) );
            }
        }

        return F;
    }

    // Compute
    Matd compute( const Matd& X , const Matd& Y , const Matd& Z , const Matd& W ,
                  const SeqMatd& iS , const SeqMatd& S , const SeqMatd& vals , const SeqMatd& vecs ,
                  const int& f ) const
    {
        unsigned k;
        Matd F( X.r() , 2 * f );

        STDd N( f ) ; STDi I( f );
        forLOOPi( X.r() )
        {
            nearest( X.row(i) , Y(i) , N , I , Z , W , iS );

            forLOOPj( f )
            {
                k = I[j];

                F( i , 2*j   ) = k;
                F( i , 2*j+1 ) = kernel( X.row(i) , Z.row(k) , S[k].eig() , iS[k].eig() ,
                                         vals[k].eig() , vecs[k].eig() , type(k) );
            }
        }

        return F;
    }

};

}

#endif
