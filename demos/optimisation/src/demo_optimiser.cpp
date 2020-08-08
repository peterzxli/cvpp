
#include <cvpp/algorithms/optimiser/optimiser_nlopt.h>

using namespace cvpp;

// Struct to hold data
struct Data
{
    double x , y;
    Data( double _x , double _y ) : x( _x ) , y( _y ) {}
};

// Function to optimize
double optFunction( const Seqd& pars , Seqd& grads , void* ptr )
{
    Data* data = static_cast<Data*>( ptr );

    double val = std::fabs( ( pars[0] - data->x )
                          + ( pars[1] - data->y ) );

    return val;
}

// Main function
int main( int argc , char* argv[] )
{
    Data data( 1 , 2 );

    Seqd pars(2);
    pars[0] = 0 ; pars[1] = 1;

    Optimiser opt( nlopt::LN_COBYLA , pars.size() );

    opt.setFunction( optFunction , &data );
    opt.setMaxEval( 100 ).setTolRel( 1e-3 ).setTolAbs( 1e-3 );

    disp( "***** before" , pars[0] , pars[1] );
    double best = opt.run( pars );
    disp( "***** after" , pars[0] , pars[1] , best );

    return 0;
}
