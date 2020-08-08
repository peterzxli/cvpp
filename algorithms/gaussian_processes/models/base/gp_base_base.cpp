#include "../gp_base.h"

namespace cvpp
{

// Destructor
BaseGP::~BaseGP()
{
}

// Constructor
BaseGP::BaseGP()
{
    mean = nullptr; cov = nullptr; noise = nullptr;
    lik = nullptr; inf = nullptr; draw = nullptr;
}

// Prepare Hyps
BaseGP&
BaseGP::prepHyps()
{
    unsigned m = n_mean();
    unsigned k = n_cov();
    unsigned n = n_noise();
    unsigned l = n_lik();

    mean_hyps  >> all_hyps( 0 , m );
    cov_hyps   >> all_hyps( m , k );
    noise_hyps >> all_hyps( m + k , n );
    lik_hyps   >> all_hyps( m + k + n , l );

    if( clamps.empty() )
    {
        clamps.resize( all_hyps.n() );
        clamps.setVal(0);
    }
    updateTrainHyps();

    return *this;
}

// Prepare Clamps
BaseGP&
BaseGP::updateTrainHyps()
{
    train_hyps.reset();

    if( options.learn_hyp )
        for( unsigned i = 0 ; i < all_hyps.n() ; i++ )
            if( !clamps[i] ) train_hyps.push( all_hyps[i] );

    if( options.learn_ind )
        for( unsigned i = 0 ; i < Zt.r() ; i++ )
            for( unsigned j = 0 ; j < Zt.c() ; j++ )
                train_hyps.push( Zt(i,j) );

    if( options.learn_var )
    {
        for( unsigned i = 0 ; i < Mv.r() ; i++ )
            for( unsigned j = 0 ; j < Mv.c() ; j++ )
                train_hyps.push( Mv(i,j) );

        for( unsigned i = 0 ; i < Sv.r() ; i++ )
            for( unsigned j = 0 ; j < Sv.c() ; j++ )
                train_hyps.push( Sv(i,j) );
    }

    return *this;
}

// Update Hyps
BaseGP&
BaseGP::updateAllHyps( const Seqd& hyps )
{
    train_hyps = hyps;
    unsigned cnt = 0;

    if( options.learn_hyp )
        for( unsigned i = 0 ; i < clamps.n() ; i++ )
            if( !clamps[i] ) all_hyps[i] = hyps[cnt++];

    if( options.learn_ind )
        for( unsigned i = 0 ; i < Zt.r() ; i++ )
            for( unsigned j = 0 ; j < Zt.c() ; j++ )
                Zt(i,j) = hyps[cnt++];

    if( options.learn_var )
    {
        for( unsigned i = 0 ; i < Mv.r() ; i++ )
            for( unsigned j = 0 ; j < Mv.c() ; j++ )
                Mv(i,j) = hyps[cnt++];

        for( unsigned i = 0 ; i < Sv.r() ; i++ )
            for( unsigned j = 0 ; j < Sv.c() ; j++ )
                Sv(i,j) = hyps[cnt++];
    }

    return *this;
}

// Save
const void
BaseGP::save( const String& str ) const
{
    Xt.save( str + "_Xt" );
    Yt.save( str + "_Yt" );
    all_hyps.save( str + "_hyps" );
    clamps.save( str + "_clamps" );

    if( has_Xev() ) Xe.save( str + "_Xe" );
    if( has_Yev() ) Ye.save( str + "_Ye" );
}

// Load
const void
BaseGP::load( const String& str )
{
    Matd Xtr( str + "_Xt" );
    Matd Ytr( str + "_Yt" );

    setXYtr( Xtr , Ytr );

    Vecd hyps( str + "_hyps" );
    Veci clamps( str + "_clamps" );

    setHyps( hyps ).setClamps( clamps );
}

// Train
BaseGP&
BaseGP::train()
{
    prepTrain();
    setErrorString();

    data.lmls.reset();
    data.errs.reset();

    if( options.draw_type )
    {
        setDraw();
        draw->prepScreens();
        draw->prepBuffers();
    }

    data.training = TRAINING;

    thread_train = Thread( &BaseGP::runTrain , this );
    if( draw ) runDraw();

    thread_train.join();

    data.training = ENDED;

    if( options.verbose )
    {
        std::cout << "***** END : LML " << data.blml;
        if( has_Yev() ) std::cout << err_str << data.errs[-1].y;
        std::cout << std::endl;
    }

    if( draw && options.draw_loop )
        while( draw->input() )
            draw->drawScreens();

    return *this;
}

// Run Train
const void
BaseGP::runTrain()
{
    better = false;
    data.cnt_eval = data.cnt_loop = 0;

    timer.tick();
    switch( options.optimizer )
    {
        case NL_COBYLA: trainNLOPT();   break;
        case NL_LBFGS:  trainNLOPT();   break;

        case NUMERIC:  trainNUMERIC();  break;
        case GRADIENT: trainGRADIENT(); break;

        case MIN_NUMERIC:  trainMIN_NUM();  break;
        case MIN_GRADIENT: trainMIN_GRAD(); break;

        case STOCHASTIC: trainSTOCHASTIC(); break;
    }

    data.training = ENDED;
}

// Run Draw
const void
BaseGP::runDraw()
{
    improving = false;

    while( data.training == TRAINING ||
           data.training == ENDING )
    {
        if( !draw->input() )
            data.training = ENDING;

        draw->updateBuffers();
        if( improving )
        {
            draw->improveBuffers();
            improving = false;
        }

        draw->drawScreens();
        halt( 30 );
    }
}

// Prepare NLOPT
const void
BaseGP::prepNLOPT()
{
    switch( options.optimizer )
    {
        case NL_MMA:

            optimizer = new NLopt( nlopt::LD_MMA , n_train() );
            optimizer->set_min_objective( wrapperGPgrad_iter , this );
            break;

        case NL_LBFGS:

            optimizer = new NLopt( nlopt::LD_LBFGS , n_train() );
            optimizer->set_min_objective( wrapperGPgrad_iter , this );
            break;

        case NL_COBYLA:

            optimizer = new NLopt( nlopt::LN_COBYLA , n_train() );
            optimizer->set_min_objective( wrapperGPfree_iter , this );
            break;
    }

    optimizer->set_maxeval( options.max_evaluation );

    optimizer->set_xtol_rel( options.tolerance_rel );
    optimizer->set_xtol_abs( options.tolerance_abs );

    Vecd lower( n_train() ); lower.setVal( options.hyp_lower_bound );
    optimizer->set_lower_bounds( lower.seq() );

    Vecd upper( n_train() ); upper.setVal( options.hyp_upper_bound );
    optimizer->set_upper_bounds( upper.seq() );
}

// Train NLOPT
const void
BaseGP::trainNLOPT()
{
    prepNLOPT();

    Seqd hyps = train_hyps.seq();
    try { optimizer->optimize( hyps , lml );
    } catch( ... ) {}

    solve( hyps );
}

// Train CVPP_NUMERIC
const void
BaseGP::trainNUMERIC()
{
    try { minimizeCVPP( wrapperGPfree_calc );
    } catch( ... ) {}

    solve();
}

// Train CVPP_GRADIENT
const void
BaseGP::trainGRADIENT()
{
    try { minimizeCVPP( wrapperGPgrad_calc );
    } catch( ... ) {}

    solve();
}

// Train MINIMIZE_NUMERIC
const void
BaseGP::trainMIN_NUM()
{
    try { minimizeMATLAB( wrapperGPfree_calc );
    } catch( ... ) {}
}

// Train MINIMIZE_GRADIENT
const void
BaseGP::trainMIN_GRAD()
{
    try { minimizeMATLAB( wrapperGPgrad_calc );
    } catch( ... ) {}
}

// Train STOCHASTIC
const void
BaseGP::trainSTOCHASTIC()
{
    try { minimizeSGD();
    } catch( ... ) {}
}

// Prepare Likelihood
const void
BaseGP::prepLikelihood()
{
    if( data.training == ENDING )
        throw( 0 );

    if( options.verbose )
    {
        if( options.optimizer == STOCHASTIC )
             std::cout << "***** " << data.cnt_loop << "/" << data.cnt_eval;
        else std::cout << "***** " << data.cnt_eval;
    }
}

// Post Likelihood
const void
BaseGP::postLikelihood( const double& lml )
{
    if( isImproving( lml ) || options.optimizer == STOCHASTIC )
    {
        if( has_Xev() && ( ( has_Yev() ) ||
                           ( options.draw_type == OUTPUT ) ||
                           ( options.draw_type == INPUT && Xe.c() < 3 ) ) ) squery( Xe );
        if( has_Yev() ) calcErrors( Ye );

        data.lmls.push( Pt2d( data.lmls.n() , lml ) );
        data.blml = lml;

        improving = better = true;
        while( improving && draw )
            halt( 30 );
    }
    else
    {
        data.lmls.push( Pt2d( data.lmls.n() , data.lmls[-1].y ) );
        if( has_Yev() ) data.errs.push( Pt2d( data.errs.n() , data.errs[-1].y ) );
    }

    if( options.verbose )
    {
        std::cout << std::fixed << std::setprecision(5);
        std::cout << " : LML " << lml << " / " << data.blml;

        if( has_Yev() ) std::cout << err_str << data.errs[-1].y;

        std::cout << std::setprecision(0) << " : " << timer.tick() << " msec";
        if( better ) std::cout << " **IMPROVING**";
        std::cout << std::fixed << std::setprecision(5) << std::endl;
    }

    if( data.training != ENDING ) data.cnt_eval++;
    improving = better = false;
}

// Select Batch
const void
BaseGP::selectBatch()
{
    if( rands.empty() || rands.n() < n_btc() )
    {
        rands.reset( Xt.r() ).setIncrease( 0 , 1 ).Shuffle();
        lrate_step = ( 1.0 / ( 1.0 + (double)data.cnt_loop++ / (double)n_btc() ) );
    }

    for( unsigned i = 0 ; i < Xb.r() ; i++ )
    {
        Xb.row(i) = Xt.row( rands[i] );
        Yb.row(i) = Yt.row( rands[i] );
    }

    rands.trimFront( Xb.r() );
}

// Select Batch
const void
BaseGP::selectSingleBatch()
{
    Veci rands( n_tr() );
    rands.setIncrease().Shuffle().keepFront( n_btc() );

    for( unsigned i = 0 ; i < n_btc() ; i++ )
    {
        Xb.row(i) = Xt.row( rands[i] );
        Yb.row(i) = Yt.row( rands[i] );
    }
}

// Calculate Errors
const void
BaseGP::setErrorString()
{
    switch( options.error_metric )
    {
        case RMSE: err_str = " : RMSE "; break;
        case NLPD: err_str = " : NLPD "; break;
    }
}

// Calculate Errors
const void
BaseGP::calcErrors( const Matd& Ys )
{
    switch( options.error_metric )
    {
        case RMSE:

            data.errs.push( Pt2d( data.errs.n() ,
                                  sqrt( ( mf.c(0) - Ys.c(0) ).square().mean() ) ) );
            break;

        case NLPD:

            data.errs.push( Pt2d( data.errs.n() ,
                                  0.5 * ( vf.c(0).log() + ( mf.c(0) - Ys.c(0) ).square() / vf.c(0) ).mean() ) );
            break;
    }
}

// Query
Matd&
BaseGP::query( const Matd& X , Matd& mf , Matd& vf )
{
    mf.Resize( X.r() , d_gp() );
    vf.Resize( X.r() , d_gp() );

    Matd Xi,mfi,vfi;

    unsigned i = 0 , n ;
    while( i < X.r() )
    {
        n = std::min( options.query_batch , X.r() - i );

        Xi  >> X.r(  i , n );
        mfi >> mf.r( i , n );
        vfi >> vf.r( i , n );

        infer( Xi , mfi , vfi );
        i += n;
    }

    if( lik ) lp = calcLik( mf );

    return this->mf;
}

}
