#include "./kmeans.h"

namespace cvpp
{

KMeans::KMeans( KMinit* init , KMopt* opt )
{
    this->init = init;
    this->opt = opt;

    data = new KMdata();
    flag_init = flag_opt = flag_done = flag_loop = false;
}

KMeans::~KMeans()
{
    delete init;
    delete opt;
    delete data;
}

// Initialise Start
const void
KMeans::init_start( const Matd& X , const int& m )
{
    this->X() = X;
    this->n() = X.r() ; this->d() = X.c() ; this->m() = m ;
    this->t() = this->n();

    flag_init = true;
    init->start( data );
}

// Initialise Loop
const bool
KMeans::init_loop()
{
    return init->loop();
}

// Initialise Finish
const void
KMeans::init_finish()
{
    init->finish();
    flag_init = flag_loop = false;
    opt_start();
}

// Optimise Start
const void
KMeans::opt_start()
{
    flag_opt = true;
    opt->start( data );
}

// Optimise Loop
const bool
KMeans::opt_loop()
{
    return opt->loop();
}

// Optimise Finish
const void
KMeans::opt_finish()
{
    opt->finish();
    flag_opt = flag_loop = false ;
    flag_done = true;
}

// Initialise
const void
KMeans::initialise( const Matd& X , const int& m )
{
    init_start( X , m );

    Timer t;
    while( init_loop() );
    timer = t.tick();

    init_finish();
}

// Initialise
const void
KMeans::initialise( const Matd& X , const Matd& Z )
{
    init_start( X , Z.r() );
    this->Z() = Z;
    init_finish();
}

// Optimise
const void
KMeans::optimise( int n )
{
    opt_start();
    while( opt_loop() && n-- > 0 );
    opt_finish();
}

const void
KMeans::start( const Matd& X , const int& m )
{
    init_start( X , m );
}

const void
KMeans::loop()
{
    if( flag_done ) return;

    if( flag_init && flag_loop ) { init_finish(); return; }
    if( flag_opt && flag_loop ) { opt_finish(); return; }

    if( flag_init ) { flag_loop = !init_loop(); return; }
    if( flag_opt ) { flag_loop = !opt_loop(); return ; }
}

const void
KMeans::run( const Matd& X , const int& m , const int& n )
{
    initialise( X , m );
    optimise( n );
}

}
