#include "./gp_local_indep.h"

namespace cvpp
{

// Constructor
TPL_T
LocalIndepGP<T>::LocalIndepGP() : BaseGP()
{
}

// Destructor
TPL_T
LocalIndepGP<T>::~LocalIndepGP()
{
}

// Train
TPL_T LocalIndepGP<T>&
LocalIndepGP<T>::train()
{
    unsigned m = n_ind();

    Timer t;

    Lt = Xt.closestRowsLBL( Zt );
    if( has_Yev() ) Le = Xe.closestRowsLBL( Zt );

    std::cout << "TRAINING " << m << std::endl;
    for( unsigned i = 0 ; i < m ; i++ ) std::cout << "*";
    std::cout << std::endl;

    gp.resize( m );

    #pragma omp parallel for
    for( unsigned i = 0 ; i < m ; i++ )
    {
        Matd Xi = Xt.sampleRows( Lt , i );
        Matd Yi = Yt.sampleRows( Lt , i );

        gp[i] = new T();

        gp[i]->setMean( mean );
        gp[i]->setCov( cov );
        gp[i]->setNoise( noise );

        gp[i]->options = options;
        gp[i]->options.draw_type = NONE;
        gp[i]->options.verbose = false;
        gp[i]->options.learn_hyp = true;

        gp[i]->setXYtr( Xt.sampleRows( Lt , i ) ,
                        Yt.sampleRows( Lt , i ) );

        if( has_Yev() )
            gp[i]->setXYev( Xe.sampleRows( Le , i ) ,
                            Ye.sampleRows( Le , i ) );

        gp[i]->setHyps( all_hyps );
        gp[i]->setClamps( clamps );

        gp[i]->train();
        std::cout << "*" << std::flush;
    }

    std::cout << std::endl;
    std::cout << "COMPLETED : " << t.tick() << " msec";

    if( has_Yev() )
    { 
        setErrorString();
        query(); calcErrors( Ye );
        std::cout << err_str << data.errs[-1].y;
    }

    std::cout << std::endl;

    SeqPts2d lmls( m ) , errs( m );
    for( unsigned i = 0 ; i < m ; i++ )
        lmls[i] >> gp[i]->lmls() , errs[i] >> gp[i]->errs();

    setDraw();
    draw->loopLocal( lmls , errs );
}

// Infer
TPL_T const void
LocalIndepGP<T>::infer( const Matd& Xs , Matd& mf , Matd& vf ) const
{
    unsigned m = n_ind() , k = 3;

    KDtreed tree( Zt );

    SSeqd dst; SSeqi cls;
    tree.knnSearch( Xs , k , cls , dst );

    SeqMatd SXs( m ); Mati qty( m );
    for( unsigned i = 0 ; i < m ; i++ )
        SXs[i].reset( Xs.dims() );

    qty.setVal(0);
    for( unsigned i = 0 ; i < cls.size() ; i++ )
    {
        #pragma omp parallel for
        for( unsigned j = 0 ; j < cls[i].size() ; j++ )
        {
            int k = cls[i][j];
            SXs[k].row( qty[k]++ ) = Xs.row(i);
        }
    }
    #pragma omp parallel for
    for( unsigned i = 0 ; i < m ; i++ )
    {
        SXs[i].KeepU( qty[i] );
        gp[i]->query( SXs[i] );
    }

    mf.setVal( 0 );
    vf.setVal( 0 );

    qty.setVal( 0 );
    for( unsigned i = 0 ; i < cls.size() ; i++ )
    {   for( unsigned j = 0 ; j < cls[i].size() ; j++ )
        {
            int k = cls[i][j];

            mf[i] += gp[k]->mf[ qty[k] ] / gp[k]->vf[ qty[k] ];
            vf[i] += 1.0 / gp[k]->vf[ qty[k] ];

            qty[k]++;
        }
    }

    mf /= vf;
    vf = 1.0 / vf;
}

}


