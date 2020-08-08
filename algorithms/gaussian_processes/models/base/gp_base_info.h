#ifndef GP_INFO_H
#define GP_INFO_H

#include <cvpp/auxiliar/definitions.h>
#include <cvpp/auxiliar/macros.h>

#include <cvpp/containers/matrix.h>
#include <cvpp/containers/vector.h>

#include <cvpp/structs/struct_gp.h>

namespace cvpp
{

class InfoGP
{

protected:

    Matd Xt,Yt,Zt,Xb,Yb;
    Matd Xe,Ye,Mv,Sv,th1,th2;
    Mati Lt,Le;

    Vecd all_hyps,train_hyps;
    Vecd mean_hyps,cov_hyps,noise_hyps,lik_hyps;
    Veci rands,clamps;

public:

    Matd mf,vf,lp;

    GPdata data;
    GPoptions options;

public:

    const Matd& Xtr() const { return Xt; }
    const Matd& Ytr() const { return Yt; }
    const Matd& Ztr() const { return Zt; }

    const Matd& Xev() const { return Xe; }
    const Matd& Yev() const { return Ye; }

    const Matd& Xbt() const { return Xb; }
    const Matd& Ybt() const { return Yb; }

    const Mati& Ltr() const { return Lt; }
    const Mati& Lev() const { return Le; }

    Matd uvf() const { return mf + 2.0 * vf.sqrt(); }
    Matd lvf() const { return mf - 2.0 * vf.sqrt(); }

    double uvf( const int& i ) const { return mf(i) + 2.0 * sqrt( vf(i) ); }
    double lvf( const int& i ) const { return mf(i) - 2.0 * sqrt( vf(i) ); }

    const Pts2d& lmls() const { return data.lmls; }
    const Pts2d& errs() const { return data.errs; }

    unsigned n_tr() const { return Xt.r(); }
    unsigned n_ev() const { return Xe.r(); }

    unsigned n_ind() const { return Zt.r(); }
    unsigned n_btc() const { return Xb.r(); }

    unsigned n_clamped() const { return clamps.n(); }
    unsigned n_unclamped() const { return clamps.n() - clamps.sum(); }

    unsigned n_freehyp() const { return options.learn_hyp ? n_unclamped()   : 0 ; }
    unsigned n_freeind() const { return options.learn_ind ? Zt.s()          : 0 ; }
    unsigned n_freevar() const { return options.learn_var ? Mv.s() + Sv.s() : 0 ; }

    unsigned d_in()  const { return Xt.c(); }
    unsigned d_out() const { return Yt.c(); }

    virtual unsigned d_gp() const { return 1; }

    bool has_tr()  const { return Xt.r() > 0; }
    bool has_bt()  const { return Xb.r() > 0; }

    bool has_Xev() const { return Xe.r() > 0; }
    bool has_Yev() const { return Ye.r() > 0; }
    bool has_Ztr() const { return Zt.r() > 0; }

    virtual InfoGP& setXtr( const Matd& X ) { Xt = X; return *this; }
    virtual InfoGP& setYtr( const Matd& Y ) { Yt = Y; return *this; }
    virtual InfoGP& setZtr( const Matd& Z ) { Zt = Z; return *this; }

    virtual InfoGP& setXev( const Matd& X ) { Xe = X; return *this; }
    virtual InfoGP& setYev( const Matd& Y ) { Ye = Y; return *this; }

    virtual InfoGP& setXYtr( const Matd& X , const Matd& Y ) { return setXtr( X ).setYtr( Y ); }
    virtual InfoGP& setXYev( const Matd& X , const Matd& Y ) { return setXev( X ).setYev( Y ); }

    virtual InfoGP& setXYZtr( const Matd& X , const Matd& Y , const Matd& Z ) { return setXtr( X ).setYtr( Y ).setZtr( Z ); }

    InfoGP& setBatchSize( const unsigned& n ) { Xb.reset( n , d_in() ); Yb.reset( n , d_out() ); return *this; }
    InfoGP& setInducingSize( const unsigned& n ) { Zt.reset( n , d_in() ); return *this; }

    InfoGP& setInputDim( const unsigned& d ) { Xt.reset( Dims( 0 , d ) ); return *this; }
    InfoGP& setOutputDim( const unsigned& d ) { Yt.reset( Dims( 0 , d ) ); return *this; }

};

}

#endif
