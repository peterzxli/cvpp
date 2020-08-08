#ifndef COV_Random_H
#define COV_Random_H

#include "../cov_base.h"
#include <cvpp/algorithms/random_kitchen_sinks/feats/rks_feat_gaussian.h>

namespace cvpp
{

Matd Zcov;

class CovRandom : public CovBase
{

protected:

    RKSfeatBase* feat;

public:

    // Constructor
    CovRandom( const unsigned& type = CST ) : CovBase( type )
    {
        Zcov.reset();
        feat = new RKSfeatGaussian();
    }

    // Hyp Number
    const unsigned n() const
    {
        return 3;
    }

    // Calculate Diagonal
    Matd calcDiag( const Matd& X ,
                   const Vecd& hyps ) const
    {
        return calcDense( X , X , hyps ).diagonal();
    }

    // Calculate Dense
    Matd calcDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps ) const
    {
        int f = (int)round( hyps[0] ) / feat->mlt();

        if( Zcov.c() != f )
        {
            randomise(1);
            Zcov = MatXXd( X1.c() , f ).setRandn( 0 , exp( hyps[1] ) );
            Zcov = Zcov.sin() & Zcov.cos();
        }

        if( X1.r() == X2.r() )
        {
            Matd phi = feat->calc( X1 * Zcov );

            return exp( hyps[-1] ) * ( phi * phi.t() );
        }
        else
        {
            Matd phi1 = feat->calc( X1 * Zcov );
            Matd phi2 = feat->calc( X2 * Zcov );

            return exp( hyps[-1] ) * ( phi1 * phi2.t() );
        }
    }

    // Hyp Gradient Dense
    Matd gradDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps , const Matd& K , const unsigned& i ) const
    {
        switch( ls_type )
        {
        case CST:

            return K;
        }
    }

};

}

#endif
