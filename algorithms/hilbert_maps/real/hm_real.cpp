#include "./hm_real.h"

namespace cvpp
{

// Constructor
HMreal::HMreal( HMfeatBase* feat_ptr , HMregrBase* regr_ptr ,
                const unsigned& btc )
{
    feature = feat_ptr;
    regressor = regr_ptr;

    batch = btc;
}

// Destructor
HMreal::~HMreal()
{
//    delete feature;
//    delete regressor;
}

// Add Weights
HMreal&
HMreal::add( const SeqMatd& clouds , const SeqMatd& means , const SeqMatd& covs )
{
    regressor->add( clouds , means , covs );
    feature->ndims += means.size();

    kdtree.add( regressor->ctrs ); // Added

    return *this;
}

// Query Grid
Matd
HMreal::query( const Matd& Xte )
{
    double r = Xte.gridResolution();
    Mati s = Xte.gridSize();

    Matd Z = regressor->ctrs;
    Matd W = regressor->weights;

    Matd G = MatZEROSd( Xte.r() );
    Matd ZZ = ( ( Z - Xte.minRows() ) / r ).Round();

    for( int n = 0 ; n < Z.r() ; ++n )
    {
        Eig33d iS = regressor->icovs[n].eig();

        int px = std::ceil( 2.5 * sqrt( regressor->vars[n](0,0) ) / r );
        int py = std::ceil( 2.5 * sqrt( regressor->vars[n](1,1) ) / r );
        int pz = std::ceil( 2.5 * sqrt( regressor->vars[n](2,2) ) / r );

        int ist = ZZ(n,0) - px , ifn = ist + 2 * px + 1;
        int jst = ZZ(n,1) - py , jfn = jst + 2 * py + 1;
        int kst = ZZ(n,2) - pz , kfn = kst + 2 * pz + 1;

        #pragma omp parallel for
        forLOOPii( ist , ifn )
        {
            Eig13d d; Eig31d dt;
            int idx1 , idx2;

            idx1 = i * s(1) * s(2);
            d(0) = dt(0) = (double)( i   - ZZ(n,0) ) * r;
            d(1) = dt(1) = (double)( jst - ZZ(n,1) ) * r;

            forLOOPjj( jst , jfn )
            {
                idx2 = idx1 + j * s(2);
                d(2) = dt(2) = (double)( kst - ZZ(n,2) ) * r;

                forLOOPkk( kst , kfn )
                {
                    G( idx2 + k ) += W(n) * std::exp( - ( d * iS * dt )(0) );
                    d(2) += r; dt(2) += r;
                }

                d(1) += r; dt(1) += r;
            }
        }
    }

    return G;
}

// Query Grid
Matd
HMreal::query2( const Matd& Xte , const int& nn )
{    
    Matd res( Xte.r() );
    res.setVal(0);

    Matd &wgts = regressor->weights;
    Matd &ctrs = regressor->ctrs;

    KDtreed kdtree( ctrs ); SSeqi idxs; SSeqd dsts;
    kdtree.knnSearch( Xte , nn , idxs , dsts );

    #pragma omp parallel for
    forLOOPi( idxs.size() )
    {
        forLOOPj( idxs[i].size() )
        {
            int k = idxs[i][j];

            Eig12d d = Xte.row(i) - ctrs.row(k);
            Eig22d iS = regressor->icovs[k].eig();

            res(i) += wgts(k) * std::exp( -0.5 * ( d * iS * d.transpose() )(0) );
        }
    }

    res = 1.0 / ( 1.0 + ( - res ).exp() );
    return res;
}

// Query Grid
Matd
HMreal::query3( const Matd& Xte , const int& nn )
{
    Matd res( Xte.r() );
    res.setVal(0);

    Matd &wgts = regressor->weights;
    Matd &ctrs = regressor->ctrs;

//    KDtreed kdtree( ctrs );
    SSeqi idxs; SSeqd dsts;
    kdtree.knnSearch( Xte , nn , idxs , dsts );

    #pragma omp parallel for
    forLOOPi( idxs.size() )
    {
        forLOOPj( idxs[i].size() )
        {
            int k = idxs[i][j];

            Eig13d d = Xte.row(i) - ctrs.row(k);
            Eig33d iS = regressor->icovs[k].eig();

            res(i) += wgts(k) * std::exp( - ( d * iS * d.transpose() )(0) );
        }
    }

//    res = 1.0 / ( 1.0 + ( - res ).exp() );
    return res;
}

void
HMreal::cluster( const Matd& Xtr ,
                 SeqMatd& clouds , SeqMatd& means , SeqMatd& covs ,
                 const double& r , const int& thr )
{
    KDtreed kd( Xtr );
    Matd cloud , tmp( 1 , Xtr.c() );

    int ii , jj , t = Xtr.r();
    Mati I = MatINCRi( t ) , J = MatINCRi( t );
    Mati N = MatZEROSi( t );

    clouds.reserve( t / 10 );

    SSeqi idx; SSeqd dst;
    while( t > 0 )
    {
        tmp.eig() = Xtr.row( I( randi( 0 , t ) ) );
        kd.radSearch( tmp , r , idx , dst );

        if( idx[0].size() > thr )
        {
            cloud.reset( idx[0].size() , Xtr.c() );

            #pragma omp parallel for
            forLOOPi( cloud.r() ) cloud.row(i) = Xtr.row( idx[0][i] );
            clouds.push_back( cloud );
        }

        forLOOPi( idx[0].size() )
        {
            ii = idx[0][i];
            jj = J( ii );

            if( !N( ii ) )
            {
                N( ii ) = 1;

                I( jj ) = I( --t );
                J( t ) = J( I( jj ) ) = jj;
            }
        }
    }

    means.resize( clouds.size() );
    covs.resize( clouds.size() );

    #pragma omp parallel for
    forLOOPi( clouds.size() ) clouds[i].mcovRows( means[i] , covs[i] );
}

void
HMreal::cluster( const Matd& Xor , const Matd& Xtr ,
                 SeqMatd& clouds , SeqMatd& means , SeqMatd& covs ,
                 const double& r1 , const double& r2 , const int& thr )
{
    KDtreed kd( Xtr );
    Matd cloud , tmp( 1 , Xtr.c() );

    Matd D = ( Xor - Xtr ).sqsumCols().sqrt();

    int ii , jj , t = Xtr.r();
    Mati I = MatINCRi( t ) , J = MatINCRi( t );
    Mati N = MatZEROSi( t );

    clouds.reserve( t / 10 );

    SSeqi idx; SSeqd dst;
    while( t > 0 )
    {
        int rnd = I( randi( 0 , t ) );
        double r = r1 * ( r2 - 1.0 ) * ( Xtr.row(rnd) - Xor.row(rnd) ).norm();

        tmp.eig() = Xtr.row( rnd );
        kd.radSearch( tmp , r , idx , dst );

        if( idx[0].size() > thr )
        {
            cloud.reset( idx[0].size() , Xtr.c() );

            #pragma omp parallel for
            forLOOPi( cloud.r() ) cloud.row(i) = Xtr.row( idx[0][i] );
            clouds.push_back( cloud );
        }

        forLOOPi( idx[0].size() )
        {
            ii = idx[0][i];
            jj = J( ii );

            if( !N( ii ) )
            {
                N( ii ) = 1;

                I( jj ) = I( --t );
                J( t ) = J( I( jj ) ) = jj;
            }
        }
    }

    means.resize( clouds.size() );
    covs.resize( clouds.size() );

    #pragma omp parallel for
    forLOOPi( clouds.size() ) clouds[i].mcovRows( means[i] , covs[i] );
}

}
