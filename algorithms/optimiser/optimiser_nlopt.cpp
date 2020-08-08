
#include <cvpp/algorithms/optimiser/optimiser_nlopt.h>

namespace cvpp
{

Optimiser::Optimiser( const nlopt::algorithm& alg , const unsigned& n )
{
    this->n = n;
    this->optimiser = new NLopt( alg , n );
}

Optimiser::~Optimiser()
{
    delete optimiser;
}

Optimiser&
Optimiser::setFunction( double func( const Seqd& , Seqd& , void* ) , void* data )
{
    optimiser->set_min_objective( func , data );
    return *this;
}

Optimiser&
Optimiser::setBounds( const Matd& bnd )
{
    Vecd lower = bnd.r(0).t();
    Vecd upper = bnd.r(1).t();

    optimiser->set_lower_bounds( lower.seq() );
    optimiser->set_upper_bounds( upper.seq() );

    return *this;
}

Optimiser&
Optimiser::setMaxEval( const unsigned& val )
{
    optimiser->set_maxeval( val ); return *this;
}

Optimiser&
Optimiser::setTolRel( const double& val )
{
    optimiser->set_xtol_rel( val ); return *this;
}

Optimiser&
Optimiser::setTolAbs( const double& val )
{
    optimiser->set_xtol_abs( val ); return *this;
}

double
Optimiser::run(const Vecd& pars )
{
    run( pars.seq() );
}

double
Optimiser::run( Seqd& pars )
{
    double best;

    try {
        optimiser->optimize( pars , best );
    } catch( ... ) {}

    return best;
}

}
