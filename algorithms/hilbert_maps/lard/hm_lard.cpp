#include "./hm_lard.h"

namespace cvpp
{

// Constructor
HMlard::HMlard( HMfeatBase* feat_ptr , HMregrBase* regr_ptr ,
                const unsigned& btc )
{
    feature = feat_ptr;
    regressor = regr_ptr;

    batch = btc;
}

// Destructor
HMlard::~HMlard()
{
    delete feature;
    delete regressor;
}

// Total Number of Points
unsigned
HMlard::totalPoints( const SeqSprd& feats ) const
{
    unsigned n = 0;
    forLOOPi( feats.size() ) n += feats[i].r();
    return n;
}

// Add Weights
HMlard&
HMlard::add( const Matd& ctr )
{
    regressor->add( ctr );
    feature->ndims += ctr.r();

    return *this;
}

// Add Weights
HMlard&
HMlard::add( const Matd& means , const SeqMatd& covs )
{
    regressor->add( means , covs );
    feature->ndims += means.r();

    return *this;
}

// Make 3D Dataset
const void
HMlard::makeDataset( const Matd& scan , Matd& pts , Matd& prob ,
                     const double& step ) const
{
    std::random_device rd; std::mt19937 gen( 1 );
    std::uniform_real_distribution<> rnd( 0.0 , 1.0 );

    Matd start = scan.cl( scan.c() / 2 );
    Matd end = scan.cr( scan.c() / 2 );

    Matd delta = end - start;
    Matd magn = ( step * delta.magnCols() ).Floor().Floor( 1.0 );

    pts.reset( magn.r() + magn.sum() , start.c() );
    prob.reset( pts.r() );

    int cnt = 0;
    forLOOPi( magn.r() )
    {
        pts.row(cnt) = end.row(i);
        prob(cnt++) = 1;

        forLOOPj( magn(i) )
        {
            pts.row(cnt) = start.row(i) + rnd( gen ) * delta.row(i);
            prob(cnt++) = 0;
        }
    }
}

// Calculate Features
SeqSprd
HMlard::calcFeatures( const Matd& pts ) const
{
    Timer t;
    unsigned n = std::floor( pts.r() / batch );
    SeqSprd feats( n + 1 );

    #pragma omp parallel for
    forLOOPi( n )
        feats[i] = feature->compute( pts.r( i * batch , batch ) , regressor->kdtree , regressor->orientations );
    feats.back() = feature->compute( pts.rd( pts.r() - n * batch ) , regressor->kdtree , regressor->orientations );

    std::cout << "Calculating features " << pts.r() << " : " << t.check() << " msec ( "
              << t.check() / pts.r() << " msec/feature )" << std::endl;

    return feats;
}

// Train Scan
HMlard&
HMlard::train( const Matd& scan , const double& step )
{
    Matd pts; Matd prob;
    makeDataset( scan , pts , prob , step );
    return train( pts , prob );
}

// Train Points
HMlard&
HMlard::train( const Matd& pts , const Matd& prob )
{
    return train( calcFeatures( pts ) , prob );
}

// Train Features
HMlard&
HMlard::train( const SeqSprd& feats , const Matd& prob )
{
    Timer t;
    unsigned n = totalPoints( feats );

    forLOOPi( feats.size() - 1 )
        regressor->train( feats[i] , prob.r( i * batch , batch ) );
    regressor->train( feats.back() , prob.rd( feats.back().r() ) );

    std::cout << "Training " << n << " : " << t.check() << " msec ( "
              << t.check() / n << " msec/feature )" << std::endl;

    return *this;
}

// Train Features
HMlard&
HMlard::train( const Sprd& feats , const Matd& prob )
{
    Timer t;
    unsigned n = feats.r();

    regressor->train( feats , prob );

    std::cout << "Training " << n << " : " << t.check() << " msec ( "
              << t.check() / n << " msec/feature )" << std::endl;

    return *this;
}

// Query Points
Matd
HMlard::query( const Matd& pts ) const
{
    return query( calcFeatures( pts ) );
}

// Query Points
const void
HMlard::query( const Matd& pts , Matd& mf , Matd& vf ) const
{
    query( calcFeatures( pts ) , mf , vf );
}

// Query Features
Matd
HMlard::query( const SeqSprd& feats ) const
{
    Timer t;
    unsigned n = totalPoints( feats );
    Matd mf( n );

    #pragma omp parallel for
    forLOOPi( feats.size() - 1 )
        mf.r( i * batch , batch ) = regressor->query( feats[i] );
    mf.rd( feats.back().r() ) = regressor->query( feats.back() );

    std::cout << "Querying " << n << " : " << t.check() << " msec ( "
              << t.check() / n << " msec/feature )" << std::endl;

    return mf;
}

// Query Features
const void
HMlard::query( const SeqSprd& feats , Matd& mf , Matd& vf ) const
{
    Timer t;
    unsigned n = totalPoints( feats );
    mf.reset( n ); vf.reset( n );

    #pragma omp parallel for
    forLOOPi( feats.size() - 1 )
    {
        Matd mfi = mf.r( i * batch , batch ) , vfi = vf.r( i * batch , batch );
        regressor->query( feats[i] , mfi , vfi );
    }

    Matd mfi = mf.rd( feats.back().r() ) , vfi = vf.rd( feats.back().r() );
    regressor->query( feats.back() , mfi , vfi );

    std::cout << "Querying " << n << " : " << t.check() << " msec ( "
              << t.check() / n << " msec/feature )" << std::endl;
}

// Query Features
Matd
HMlard::query( const Sprd& feats ) const
{
    Timer t;
    unsigned n = feats.r();

    Matd mf = regressor->query( feats );

    std::cout << "Querying " << n << " : " << t.check() << " msec ( "
              << t.check() / n << " msec/feature )" << std::endl;

    return mf;
}

// Query Features
const void
HMlard::query( const Sprd& feats , Matd& mf , Matd& vf ) const
{
    Timer t;
    unsigned n = feats.r();
    mf.reset( n ); vf.reset( n );

    regressor->query( feats , mf , vf );

    std::cout << "Querying " << n << " : " << t.check() << " msec ( "
              << t.check() / n << " msec/feature )" << std::endl;
}

}
