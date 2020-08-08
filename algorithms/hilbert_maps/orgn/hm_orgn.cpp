#include "./hm_orgn.h"

namespace cvpp
{

// Constructor
HMorgn::HMorgn( HMfeatBase* feat , HMregrBase* reg )
{
    feature = feat , regressor = reg ;
    regressor->start( feat->ndims );

    batch = 1000;
}

// Destructor
HMorgn::~HMorgn()
{
    delete feature;
    delete regressor;
}

// Total Number of Points
unsigned
HMorgn::totalPoints( const Seq<Sprd>& feats ) const
{
    unsigned n = 0;
    forLOOPi( feats.size() ) n += feats[i].r();
    return n;
}

// Make 3D Dataset
const void
HMorgn::make3Ddataset( const Matd& scan , Matd& pts , Mati& prob ,
                       const double& step ) const
{
    std::random_device rd; std::mt19937 gen( 1 );
    std::uniform_real_distribution<> rnd( 0.0 , 1.0 );

    Matd start = scan.c(0,3);
    Matd end = scan.c(3,3);

    Matd delta = end - start;
    Matd magn = ( step * delta.magnCols() ).floor().Floor( 1.0 );

    pts.reset( magn.r() + magn.sum() , start.c() );
    prob.reset( pts.r() );

    unsigned cnt = 0;
    forLOOPi( magn.r() )
    {
        pts.r(cnt) = end.r(i);
        prob(cnt++) = 1;

        forLOOPj( magn(i) )
        {
            pts.r(cnt) = start.r(i) + rnd( gen ) * delta.r(i);
            prob(cnt++) = -1;
        }
    }
}

// Calculate Features
Seq<Sprd>
HMorgn::calcFeatures( const Matd& pts ) const
{
    Timer t;
    unsigned n = std::floor( pts.r() / batch );
    Seq<Sprd> feats( n + 1 );

    #pragma omp parallel for
    forLOOPi( n )
        feats[i] = feature->compute( pts.r( i * batch , batch ) );
    feats.back() = feature->compute( pts.rd( pts.r() - n * batch ) );

    std::cout << "Calculating features " << pts.r() << " : " << t.check() << " msec ( "
              << t.check() / pts.r() << " msec/feature )" << std::endl;

    return feats;
}

// Train Points
const void
HMorgn::train( const Matd& pts , const Mati& prob )
{
    train( calcFeatures( pts ) , prob );
}

// Train Scan
const void
HMorgn::train( const Matd& scan , const double& step )
{
    Matd pts; Mati prob;
    make3Ddataset( scan , pts , prob , step );
    train( pts , prob );
}

// Train Features
const void
HMorgn::train( const Seq<Sprd>& feats , const Mati& prob )
{
    Timer t;
    unsigned n = totalPoints( feats );

    forLOOPi( feats.size() - 1 )
        regressor->train( feats[i] , prob.r( i * batch , batch ) );
    regressor->train( feats.back() , prob.rd( feats.back().r() ) );

    std::cout << "Training " << n << " : " << t.check() << " msec ( "
              << t.check() / n << " msec/feature )" << std::endl;
}

// Query Points
Matd
HMorgn::query( const Matd& pts ) const
{
    return query( calcFeatures( pts ) );
}

// Query Features
Matd
HMorgn::query( const Seq<Sprd>& feats ) const
{
    Timer t;
    unsigned n = totalPoints( feats );
    Matd prob( n );

    #pragma omp parallel for
    forLOOPi( feats.size() - 1 )
        prob.r( i * batch , batch ) = regressor->query( feats[i] );
    prob.rd( feats.back().r() ) = regressor->query( feats.back() );

    std::cout << "Querying " << n << " : " << t.check() << " msec ( "
              << t.check() / n << " msec/feature )" << std::endl;

    return prob;
}

}
