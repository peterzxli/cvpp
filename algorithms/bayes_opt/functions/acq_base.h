#ifndef ACQ_BASE_H
#define ACQ_BASE_H

#include <cvpp/algorithms/gaussian_processes/models/gp_base.h>

namespace cvpp
{

class AcqBase
{

protected:

    Vecd hyps;

public:

    virtual unsigned n_hyps() const { disp( "BASE ACQ N" ); }
    virtual double eval( const Matd& , const Matd& , const double& , const double& )
    { disp( "BASE ACQ EVAL" ); }

    double distLast( const Matd& pts , const Matd& rnd )
    {
        return ( pts.rd(1) - rnd ).rsqsum();
    }

    double distCum( const Matd& pts , const Matd& rnd )
    {
        double d = 0;

        forLOOPi( pts.r() - 1 )
            d += ( pts.r(i) - pts.r(i+1) ).rsqsum();
        d += distLast( pts , rnd );

        return d;
    }

    const void setHyps( const Vecd& hyps )
    {
        this->hyps = hyps;
    }

    virtual Matd calc( const Matd& pts , const Matd& rnds , const BaseGP& model )
    {
        Matd score( model.mf.r() );

        forLOOPi( score.r() )
            score(i) = eval( pts , rnds.r(i) , model.mf(i) , model.vf(i) );

        return score;
    }

};

}

#endif
