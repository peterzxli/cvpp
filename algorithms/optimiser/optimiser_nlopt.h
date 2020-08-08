#ifndef OPTIMIZER_NLOPT_H
#define OPTIMIZER_NLOPT_H

#include <cvpp/containers/vector.h>

namespace cvpp
{

class Optimiser
{

protected:

    unsigned n;
    NLopt* optimiser;

public:

    Optimiser( const nlopt::algorithm& , const unsigned& );
    ~Optimiser();

    Optimiser& setFunction( double func( const Seqd& , Seqd& , void* ) , void* );

    Optimiser& setMaxEval( const unsigned& );

    Optimiser& setTolRel( const double& );
    Optimiser& setTolAbs( const double& );

    Optimiser& setBounds( const Matd& );

    double run( const Vecd& );
    double run( Seqd& );

};

}

#endif
