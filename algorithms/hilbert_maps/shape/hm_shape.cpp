#include "./hm_shape.h"

namespace cvpp
{

// Constructor
HMshape::HMshape( HMfeatBase* feat_ptr , HMregrBase* regr_ptr ,
                const unsigned& btc )
{
    feature = feat_ptr;
    regressor = regr_ptr;

    batch = btc;
}

// Destructor
HMshape::~HMshape()
{
    delete feature;
    delete regressor;
}

// Total Number of Points
unsigned
HMshape::totalPoints( const SeqMatd& feats ) const
{
    unsigned n = 0;
    forLOOPi( feats.size() ) n += feats[i].r();
    return n;
}

// Add Weights
HMshape&
HMshape::add( const Matd& means , const Matd& types ,
              const SeqMatd& covs )
{
    feature->setType( types );
    feature->ndims += means.r();

    regressor->add( means , covs );

    return *this;
}

// Add Weights
HMshape&
HMshape::add( const Matd& means , const Matd& types ,
              const SeqMatd& clouds , const SeqMatd& S )
{
    feature->setType( types );
    feature->ndims += means.r();

    SeqMatd covs( S.size() ) , icovs , vals , vecs;
    forLOOPi( S.size() ) covs[i] = S[i].clone();

    align( clouds , means , covs , icovs , vals , vecs );
    regressor->add( means , covs , icovs , vals , vecs );

    return *this;
}

// Add Weights
HMshape&
HMshape::add( const Matd& means , const Matd& modes , const Matd& types ,
              const SeqMatd& clouds , const SeqMatd& S )
{
    feature->setType( types );
    feature->ndims += means.r();

    SeqMatd covs( S.size() ) , icovs , vals , vecs;
    forLOOPi( S.size() ) covs[i] = S[i].clone();

    align( clouds , means , covs , icovs , vals , vecs );
    regressor->add( means , modes , covs , icovs , vals , vecs );

    return *this;
}

// Calculate Features
SeqMatd
HMshape::calcFeatures( const Matd& pts , const int& f ) const
{
    Timer t;
    unsigned n = std::floor( pts.r() / batch );
    SeqMatd feats( n + 1 );

    #pragma omp parallel for
    forLOOPi( n )
        feats[i] = feature->compute( pts.r( i * batch , batch ) , regressor->ctrs , regressor->icovs ,
                                     regressor->covs , regressor->vals , regressor->vecs , f );
    feats.back() = feature->compute( pts.rd( pts.r() - n * batch ) , regressor->ctrs , regressor->icovs ,
                                     regressor->covs , regressor->vals , regressor->vecs , f );

    std::cout << "Calculating features " << pts.r() << " : " << t.check() << " msec ( "
              << t.check() / pts.r() << " msec/feature )" << std::endl;

    return feats;
}

// Calculate Features
SeqMatd
HMshape::calcFeatures( const Matd& pts , const Matd& prob , const int& f ) const
{
    Timer t;
    unsigned n = std::floor( pts.r() / batch );
    SeqMatd feats( n + 1 );

    #pragma omp parallel for
    forLOOPi( n )
        feats[i] = feature->compute( pts.r( i * batch , batch ) , prob.r( i * batch , batch ) ,
                                     regressor->ctrs , regressor->modes , regressor->icovs ,
                                     regressor->covs , regressor->vals , regressor->vecs , f );
    feats.back() = feature->compute( pts.rd( pts.r() - n * batch ) , prob.rd( prob.r() - n * batch ) ,
                                     regressor->ctrs , regressor->modes , regressor->icovs ,
                                     regressor->covs , regressor->vals , regressor->vecs , f );

    std::cout << "Calculating features " << pts.r() << " : " << t.check() << " msec ( "
              << t.check() / pts.r() << " msec/feature )" << std::endl;

    return feats;
}

// Train Features
HMshape&
HMshape::train( const SeqMatd& feats , const Matd& prob )
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

// Query Features
Matd
HMshape::query( const SeqMatd& feats ) const
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

}
