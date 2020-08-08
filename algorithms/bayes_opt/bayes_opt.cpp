#include "./bayes_opt.h"

namespace cvpp
{

BayesOpt::BayesOpt()
{
}

BayesOpt&
BayesOpt::query( const Matd& Xev )
{
    model.query( Xev );
    return *this;
}

BayesOpt&
BayesOpt::setBoundaries( const Matd& bnd )
{
    bounds = bnd;
    return *this;
}

BayesOpt&
BayesOpt::prepare( const Matd& Padd ,
                   const Matd& Xadd , const Matd& Yadd )
{
    P = Padd;
    X = Xadd; Y = Yadd;

    model.setXYtr( X , Y );
    return *this;
}

BayesOpt&
BayesOpt::insert( const Matd& Padd ,
                  const Matd& Xadd , const Matd& Yadd )
{
    P.AppD( Padd );
    X.AppD( Xadd ); Y.AppD( Yadd );

    model.setXYtr( X , Y );
    model.solve();

    return *this;
}

BayesOpt&
BayesOpt::start()
{
    optim = new Optimiser( nlopt::LN_COBYLA , d_in() );

    optim->setMaxEval( 20 );
    optim->setFunction( optFunction , this );
    optim->setBounds( bounds );

    model.solve();

    return *this;
}

Matd
BayesOpt::randomise( const int& n )
{
    Matd X( n , d_in() );
    forLOOPmat( X )
        X(r,c) = randd( bounds(0,c) , bounds(1,c) );
    return X;
}

Matd
BayesOpt::search( const int& n )
{
    C = randomise( n );
    model.query( C );

    Matd score = calcAcq( C );
    Vecd best = C.r( score.minIDX() ).t();

    optim->run( best );

    return best.mat().t();
}

Matd
BayesOpt::optimise( const Matd& X )
{
    Vecd best = X.t();
    optim->run( best );
    return best.mat().t();
}

}
