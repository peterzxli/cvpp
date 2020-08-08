#include "../gp_base.h"

namespace cvpp
{

// Prepare Learning
const void
BaseGP::prepLearning( Vecd& lrate , Vecd& mom ) const
{
    lrate.resize( n_train() );
    mom.resize( n_train() );

    unsigned idx = 0;
    if( options.learn_hyp )
    {
        lrate( idx , n_freehyp() ) = options.lrate_hyp;
        mom( idx , n_freehyp() ) = options.mom_hyp;
        idx += n_freehyp();
    }
    if( options.learn_ind )
    {
        lrate( idx , n_freeind() ) = options.lrate_ind;
        mom( idx , n_freeind() ) = options.mom_ind;
        idx += n_freeind();
    }
    if( options.learn_var )
    {
        lrate( idx , n_freevar() ) = options.lrate_var;
        mom( idx , n_freevar() ) = options.mom_var;
        idx += n_freevar();
    }
}

// Minimize CVPP
const void
BaseGP::minimizeCVPP( double (*func)( Vecd& , void* ) )
{
    Vecd prev_hyps = train_hyps.clone();
    Vecd grads( n_train() ) , prev_grads( n_train() );
    prev_grads = 0;

    prepLikelihood();
    double lml , plml = slikelihood();
    postLikelihood( plml );

    Vecd lrate,mom;
    prepLearning( lrate , mom );

    for( unsigned i = 0 ; i < options.max_evaluation ; i++ )
    {
        prepLikelihood();

        (*func)( grads , this ); checkDerivatives( grads );
        grads = ( 1.0 - mom ) % grads + mom % prev_grads;

        train_hyps -= lrate % grads;
        lml = slikelihood( train_hyps );

        if( lml < plml )
        {
            if( fabs( plml - lml ) < options.tolerance_abs )
            {
                postLikelihood( lml );
                break;
            }

            lrate *= 1.1;
            plml = lml;

            prev_hyps = train_hyps;
            prev_grads = grads;
        }
        else
        {
            lrate /= 2.0;
            train_hyps = ( train_hyps + prev_hyps ) / 2.0;
            prev_grads = 0;

            solve( train_hyps );
        }

        postLikelihood( lml );
    }
}

const void
BaseGP::minimizeMATLAB( double (*func)( Vecd& , void* ) )
{
    double thr =  0.1;
    double ext =  3.0;
    double rat = 10.0;
    double sig =  0.1;

    double rho = sig / 2.0;

    unsigned max_iter = options.max_evaluation;
    unsigned max_loop = options.max_searches;

    Vecd X = train_hyps.clone();
    Vecd df0( X.n() );

    prepLikelihood(); solve( X );
    double f4 , f3 , f2 , f1 , f0 = (*func)( df0 , this );
    postLikelihood( f0 );

    Vecd s = - df0;
    double d4 , d3 , d2 , d1 , d0 = - df0.norm2();

    double red = 1.0;
    double x4 , x1 , x2 , x3 = red / ( 1.0 - d0 );

    double F0;
    Vecd dF0( df0.n() ) , X0( X.n() );

    F0 = f0 ; dF0 = df0 ; X0 = X ;

    Vecd df3 = df0.clone();
    Vecd fX(0); fX.push( f0 );

    data.cnt_loop = 0;
    for( unsigned iter = 0 ; iter < max_iter &&
                             data.cnt_loop < max_loop ; iter++ )
    {
        data.cnt_loop = 0;
        prepLikelihood();

        while( true )
        {
            data.cnt_loop++;

            x2 = 0 ; f2 = f0 ; f3 = f0 ; d2 = d0 ; df3 = df0 ;

            solve( X + x3 * s );
            f3 = (*func)( df3 , this );
            d3 = df3.norm2( s );

            if( f3 < f0 )
                F0 = f3 , dF0 = df3 , X0 = hyps() ;

            if( d3 > sig * d0 || f3 > f0 + x3 * rho * d0 || data.cnt_loop == max_loop )
                break;

            x1 = x2 ; f1 = f2 ; d1 = d2 ;
            x2 = x3 ; f2 = f3 ; d2 = d3 ;

            double A = 6.0 * ( f1 - f2 ) + 3.0 * ( d2 + d1 ) * ( x2 - x1 );
            double B = 3.0 * ( f2 - f1 ) - ( 2.0 * d1 + d2 ) * ( x2 - x1 );

            x3 = ( x1 - d1 * pow( x2 - x1 , 2.0 ) ) /
                    ( B + sqrt( B * B - A * d1 * ( x2 - x1 ) ) );

            if( std::isnan( x3 ) )
            {
                x3 = ext * x2;
            }
            else
            {
                x3 = std::min( x3 , ext * x2 );
                x3 = std::max( x3 , x2 + thr * ( x2 - x1 ) );
            }
        }

        while( ( fabs( d3 ) > -sig * d0 || f3 > f0 + x3 * rho * d0 ) && data.cnt_loop < max_loop )
        {
            data.cnt_loop++;

            if( d3 > 0 || f3 > f0 + x3 * rho * d0 )
                 x4 = x3 , f4 = f3 , d4 = d3;
            else x2 = x3 , f2 = f3 , d2 = d3;

            if( f4 > f0 )
            {
                x3 = x2 - ( 0.5 * d2 * pow( x4 - x2 , 2.0 ) ) /
                          ( f4 - f2 - d2 * ( x4 - x2 ) );
            }
            else
            {
                double A = 6.0 * ( f2 - f4 ) / ( x4 - x2 ) + 3.0 * ( d4 + d2 );
                double B = 3.0 * ( f4 - f2 ) - ( 2.0 * d2 + d4 ) * ( x4 - x2 );

                x3 = x2 + ( sqrt( B * B - A * d2 * pow( x4 - x2 , 2.0 ) ) - B ) / A;
            }

            if( std::isnan( x3 ) )
                x3 = ( x2 + x4 ) / 2.0;

            x3 = std::max( std::min( x3 , x4 - thr * ( x4 - x2 ) ) ,
                                          x2 + thr * ( x4 - x2 ) ) ;

            solve( X + x3 * s );
            f3 = (*func)( df3 , this );
            d3 = df3.norm2( s );

            if( f3 < f0 )
                F0 = f3 , dF0 = df3 , X0 = hyps() ;
        }

        if( fabs( d3 ) < - sig * d0 && f3 < f0 + x3 * rho * d0 )
        {
            X = X + x3 * s ; f0 = f3 ;
            postLikelihood( f0 );
            fX.push( f0 );

            s = ( ( df3.norm2() - df0.norm2( df3 ) ) /
                  ( df0.norm2() ) ) * s.mat() - df3.mat();

            df0 = df3;
            d3 = d0 ; d0 = df0.norm2( s );

            if( d0 > 0 )
                s = - df0 , d0 = - s.norm2() ;

            x3 = x3 * std::min( rat , d3 / ( d0 - DBL_MIN ) );
        }
        else
        {
            X = X0 , f0 = F0 , df0 = dF0;

            s = -df0 , d0 = - s.norm2();
            x3 = 1.0 / ( 1.0 - d0 );
        }
    }
}

// Minimize SGD
const void
BaseGP::minimizeSGD()
{
    Vecd ghyps( n_train() ) , pghyps( n_train() );
    Matd ginds( Zt.dims() ) , pginds( Zt.dims() );

    Matd gth1( Mv.dims() ) , pgth1( Mv.dims() );
    Matd gth2( Sv.dims() ) , pgth2( Sv.dims() );

    pgth1 = pgth2 = 0;
    pghyps = 0; pginds = 0;

    double lml;
    double lrate_var = options.lrate_var , lrate_hyp = options.lrate_hyp , lrate_ind = options.lrate_ind ;
    double mom_var   = options.mom_var   , mom_hyp   = options.mom_hyp   , mom_ind   = options.mom_ind   ;

    selectSingleBatch();
    sgradient( ghyps , ginds , gth1 , gth2 ); checkAllDerivatives( ghyps , ginds , gth1 , gth2 );
    updateSGDvar( lrate_var , mom_var , gth1 , gth2 , pgth1 , pgth2 );

    for( unsigned i = 0 ; i < options.max_evaluation ; i++ )
    {
        selectBatch();
//        Xb.load( "../../data/svi/x" + std::to_string( i % 10 ) );
//        Yb.load( "../../data/svi/y" + std::to_string( i % 10 ) );

        lrate_hyp = lrate_step * options.lrate_hyp;
        lrate_ind = lrate_step * options.lrate_ind;
        lrate_var = lrate_step * options.lrate_var;

        prepLikelihood();

        lml = slikelihood( train_hyps );
        gradient( ghyps , ginds , gth1 , gth2 );
        checkAllDerivatives( ghyps , ginds , gth1 , gth2 );

        if( data.cnt_loop > options.epoch_hyp && options.epoch_hyp >= 0 )
            updateSGDhyp( lrate_hyp , mom_hyp , ghyps , pghyps );
        if( data.cnt_loop > options.epoch_ind && options.epoch_ind >= 0  )
            updateSGDind( lrate_ind , mom_ind , ginds , pginds );
        if( data.cnt_loop > options.epoch_var && options.epoch_var >= 0  )
            updateSGDvar( lrate_var , mom_var , gth1 , gth2 , pgth1 , pgth2 );

        postLikelihood( lml );
    }
}

const void
BaseGP::updateSGDhyp( const double& lrate , const double& mom ,
                      Vecd& ghyps , Vecd& pghyps )
{
    ghyps = lrate * ghyps + mom * pghyps;
    train_hyps -= ghyps;

    pghyps = ghyps;
}

const void
BaseGP::updateSGDind( const double& lrate , const double& mom ,
                      Matd& ginds , Matd& pginds )
{
    ginds = lrate * ginds + mom * pginds;
    Zt -= ginds;

    pginds = ginds;
}

const void
BaseGP::updateSGDvar( const double& lrate , const double& mom ,
                      Matd& gth1 , Matd& gth2 , Matd& pgth1 , Matd& pgth2 )
{
    gth1 = ( 1.0 - mom ) * gth1 + mom * pgth1;
    th1 += lrate * gth1;

    gth2 = ( 1.0 - mom ) * gth2 + mom * pgth2;
    th2 += lrate * gth2;

    th2.eigen( values , vectors );
    Sv = ( vectors * ( - 0.5 / values ).diag() ).slash( vectors );
    Mv = Sv * th1;

    pgth1 = gth1;
    pgth2 = gth2;
}

}








