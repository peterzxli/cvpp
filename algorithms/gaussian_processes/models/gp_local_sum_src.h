#include "./gp_local_sum.h"

namespace cvpp
{

// Constructor
TPL_T
LocalSumGP<T>::LocalSumGP( const unsigned& k ) : BaseGP()
{
    this->k = k;

    options.learn_hyp = true;
}

// Destructor
TPL_T
LocalSumGP<T>::~LocalSumGP()
{
}

// Solve
TPL_T LocalSumGP<T>&
LocalSumGP<T>::solve()
{
    #pragma omp parallel for
    forLOOPi( gpTrain.n() )
    {
        gpTrain[i]->setHyps( all_hyps );
        gpTrain[i]->solve();
    }
}

// Infer
TPL_T const void
LocalSumGP<T>::infer( const Matd& Xs , Matd& mf , Matd& vf ) const
{
    SSeqi idx; SSeqd dst;
    tree.knnSearch( Xs , k , idx , dst );

    gpQuery->setHyps( all_hyps );

    forLOOPi( Xs.r() )
    {
        Mati idxi = idx[i];

        gpQuery->setXYtr( Xt.sr( idxi ) , Yt.sr( idxi ) );
        gpQuery->squery( Xs.r(i) );

        mf.r(i) = gpQuery->mf;
        vf.r(i) = gpQuery->vf;
    }
}

// Likelihood
TPL_T double
LocalSumGP<T>::likelihood() const
{
    double lml = 0;
    forLOOPi( gpTrain.n() ) lml += gpTrain[i]->likelihood();
    return lml;
}

TPL_T const void
LocalSumGP<T>::prepTrain()
{
    tree.add( Xt );

    gpQuery = new T();

    gpQuery->setMean( mean );
    gpQuery->setCov( cov );
    gpQuery->setNoise( noise );
    gpQuery->setClamps( clamps );

    Mati Lt = Xt.closestRowsLBL( Zt );
    gpTrain.resize( n_ind() );

    forLOOPi( gpTrain.n() )
    {
        gpTrain[i] = new T();

        Mati idxi = ( Lt == i );
        gpTrain[i]->setXYtr( Xt.sr( idxi ) , Yt.sr( idxi ) );

        gpTrain[i]->setMean( mean );
        gpTrain[i]->setCov( cov );
        gpTrain[i]->setNoise( noise );

        gpTrain[i]->options = options;
        gpTrain[i]->options.draw_type = NONE;
        gpTrain[i]->options.learn_hyp = true;

        gpTrain[i]->setHyps( all_hyps );
        gpTrain[i]->setClamps( clamps );
    }
}

}



















//#include "./gp_occupancy.h"

//namespace cvpp
//{

//// Constructor
//TPL_T
//LocalSumGP<T>::LocalSumGP( const unsigned& k ) : BaseGP()
//{
//    this->k = k;
//}

//// Destructor
//TPL_T
//LocalSumGP<T>::~LocalSumGP()
//{
//}


//// Train
//TPL_T LocalSumGP<T>&
//LocalSumGP<T>::train()
//{
//    gp = new T();
//    tree.add( Xt );

//    gp->setMean( mean );
//    gp->setCov( cov );
//    gp->setNoise( noise );

//    gp->options = options;
//    gp->options.draw_type = NONE;
//    gp->options.learn_hyp = true;

//    gp->setXYtr( Xt , Yt );
//    if( has_Yev() ) gp->setXYev( Xe , Ye );

//    gp->setHyps( all_hyps );
//    gp->setClamps( clamps );

////    gp->train();
//    query();
//}

//// Infer
//TPL_T const void
//LocalSumGP<T>::infer( const Matd& Xs , Matd& mf , Matd& vf ) const
//{
//    SSeqi idx; SSeqd dst;
//    tree.knnSearch( Xs , k , idx , dst );

//    forLOOPi( Xs.r() )
//    {
//        Mati idxi = idx[i];

//        gp->setXYtr( Xt.sr( idxi ) , Yt.sr( idxi ) );
//        gp->squery( Xs.r(i) );

//        mf.r(i) = gp->mf;
//        vf.r(i) = gp->vf;
//    }
//}

//}


