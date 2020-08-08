#include "../gp_base.h"

namespace cvpp
{

// Grad Likelihood
double
BaseGP::grad_likelihood( const Seqd& hyps ,
                               Seqd& grads , void* data )
{
    prepLikelihood( hyps );
    double lml = gradient( grads );

    postLikelihood( lml );
    return lml;
}

// Numeric Likelihood
double
BaseGP::free_likelihood( const Seqd& hyps ,
                               Seqd& grads , void* data )
{
    prepLikelihood( hyps );
    double lml = likelihood();

    postLikelihood( lml );
    return lml;
}

// Wrapper Gradient Calculation
double
wrapperGPgrad_calc( Vecd& vec , void* data )
{
    BaseGP* obj = static_cast< BaseGP* >(data);
    return obj->gradient( vec );
}

// Wrapper Numeric Calculation
double
wrapperGPfree_calc( Vecd& vec , void* data )
{
    BaseGP* obj = static_cast< BaseGP* >(data);
    return obj->numeric( vec );
}

// Wrapper Gradient Iteration
double
wrapperGPgrad_iter( const Seqd& hyps , Seqd& grads , void* data )
{
    BaseGP* obj = static_cast< BaseGP* >(data);
    return obj->grad_likelihood( hyps , grads , data );
}

// Wrapper Numeric Iteration
double
wrapperGPfree_iter( const Seqd& hyps , Seqd& grads , void* data )
{
    BaseGP* obj = static_cast< BaseGP* >(data);
    return obj->free_likelihood( hyps , grads , data );
}

}
