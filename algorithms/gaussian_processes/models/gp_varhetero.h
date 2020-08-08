#ifndef GP_VARHETERO_H
#define GP_VARHETERO_H

#include "./gp_base.h"
#include "../functions/draw/draw_regressionMS.h"

namespace cvpp
{

class VarHeteroGP : public BaseGP
{

protected:

    double p;

    Matd Kf,Kg;
    Matd Ls,Lys,mu,mu0,cinvB,cinvBs,hBLK2,R;
    Matd alpha,alphascale,scale,Rscale,beta,sigma,lambda,sqlambda;

    SeqMatd KKf,KKg,NNg;

    BaseGP fgp,ggp;

public:

    VarHeteroGP();
    ~VarHeteroGP();

    const void setDraw() { draw = new DrawRegressionMS( this ); }
    virtual unsigned d_gp() const { return 2; }

    VarHeteroGP& solve();
    double likelihood() const;
    const void infer( const Matd& , Matd& , Matd& ) const;
    double gradient( Seqd& ) const;

    Dims d_mvar() const { return Dims( 1 , 1 ); }
    Dims d_svar() const { return Dims( n_tr() , 1 ); }

    unsigned n_fhyps() const { return fgp.n_hyps( d_in() ); }
    unsigned n_ghyps() const { return ggp.n_hyps( d_in() ); }
    unsigned n_hyps()  const { return n_fhyps() + n_ghyps(); }

    VarHeteroGP& setFMean( MeanBase* mean ) { fgp.setMean( mean ); return *this; }
    VarHeteroGP& setGMean( MeanBase* mean ) { ggp.setMean( mean ); return *this; }

    VarHeteroGP& setFCov( CovBase* cov ) { fgp.setCov( cov ); return *this; }
    VarHeteroGP& setGCov( CovBase* cov ) { ggp.setCov( cov ); return *this; }

    VarHeteroGP& setFNoise( NoiseBase* noise ) { fgp.setNoise( noise ); return *this; }
    VarHeteroGP& setGNoise( NoiseBase* noise ) { ggp.setNoise( noise ); return *this; }

    InfoGP& setXtr( const Matd& X ) { fgp.setInputDim( X.c() ); ggp.setInputDim( X.c() ); return InfoGP::setXtr( X ); }
    InfoGP& setYtr( const Matd& Y ) { fgp.setOutputDim( Y.c() ); ggp.setOutputDim( Y.c() ); return InfoGP::setYtr( Y ); }

    VarHeteroGP& setHyps( const Vecd& hyps )
    {
        BaseGP::setHyps( hyps );

        fgp.setHyps( hyps( 0 , n_fhyps() ) );
        ggp.setHyps( hyps( n_fhyps() , n_ghyps() ) );

        return *this;
    }

    VarHeteroGP& setClamps( const Veci& clamps )
    {
        BaseGP::setClamps( clamps );

        fgp.setClamps( clamps( 0 , n_fhyps() ) );
        ggp.setClamps( clamps( n_fhyps() , n_ghyps() ) );

        return *this;
    }

    VarHeteroGP& prepHyps()
    {
        if( clamps.empty() )
        {
            clamps.resize( all_hyps.n() );
            clamps.setVal(0);
        }
        updateTrainHyps();

        return *this;
    }

    VarHeteroGP& updateTrainHyps()
    {
        BaseGP::updateTrainHyps();

        fgp.updateTrainHyps();
        ggp.updateTrainHyps();

        return *this;
    }

    VarHeteroGP& updateAllHyps( const Seqd& hyps )
    {
        BaseGP::updateAllHyps( hyps );

        Seqd fhyps( fgp.n_train() );
        for( unsigned i = 0 ; i < fhyps.size() ; i++ )
            fhyps[i] = hyps[ i ];
        fgp.updateAllHyps( fhyps );

        Seqd ghyps( ggp.n_train() );
        for( unsigned i = 0 ; i < ghyps.size() ; i++ )
            ghyps[i] = hyps[ fgp.n_train() + i ];
        ggp.updateAllHyps( ghyps );

        return *this;
    }


};

}

#endif
