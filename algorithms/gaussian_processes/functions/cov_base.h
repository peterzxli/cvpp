#ifndef COV_BASE_H
#define COV_BASE_H

#include "./func_base.h"

namespace cvpp
{

class CovBase : public FuncBase
{

protected:

    unsigned ls_type;

public:

    CovBase( const unsigned& type = ISO );

    virtual Matd gradDense( const Matd& , const Matd& , const Vecd& , const Matd& , const unsigned& ) const { disp("COV_BASE GRAD DENSE"); }
    virtual Matd gindDense( const Matd& , const Matd& , const Vecd& , const Matd& , const unsigned& ) const { disp("COV_BASE GIND DENSE"); }

    virtual Matd gradDiag( const Matd& , const Vecd& , const Matd& , const unsigned& ) const { disp("COV_BASE GRAD DIAG"); }
    virtual Matd gindDiag( const Matd& , const Vecd& , const Matd& , const unsigned& ) const { disp("COV_BASE GIND DIAG"); }

    virtual const unsigned ls_n( const unsigned& ) const;

    virtual Matd calcDiag( const Matd& , const Vecd& ) const;
    virtual Matd calcDiag( const Matd& , const Vecd& , SeqMatd& ) const;

    virtual Matd calcDense( const Matd& , const Matd& , const Vecd& ) const;
    virtual Matd calcDense( const Matd& , const Matd& , const Vecd& , SeqMatd& ) const;

    virtual Matd gradDiag( const Matd& , const Vecd& , const unsigned& ) const;
    virtual Matd gradDiag( const Matd& , const Vecd& , const SeqMatd& , const unsigned& ) const;

    virtual Matd gradDense( const Matd& , const Matd& , const Vecd& , const unsigned& ) const;
    virtual Matd gradDense( const Matd& , const Matd& , const Vecd& , const SeqMatd& , const unsigned& ) const;

    virtual Matd gindDiag( const Matd& , const Vecd& , const unsigned& ) const;
    virtual Matd gindDiag( const Matd& , const Vecd& , const SeqMatd& , const unsigned& ) const;

    virtual Matd gindDense( const Matd& , const Matd& , const Vecd& , const unsigned& ) const;
    virtual Matd gindDense( const Matd& , const Matd& , const Vecd& , const SeqMatd& , const unsigned& i ) const;

    Matd LSeqMat1( const Vecd& , const unsigned& , const unsigned& = 1 ) const;
    Matd LSeqMat2( const Vecd& , const unsigned& , const unsigned& = 1 ) const;

    Matd dist0( const Matd& ) const;

    Matd LS1dist0( const Matd& X , const Vecd& hyps , const unsigned& i , const unsigned& n = 1 ) const
    { Matd S = LSeqMat1( hyps , i , n ); return dist0( X * S ); }

    Matd LS2dist0( const Matd& X , const Vecd& hyps , const unsigned& i , const unsigned& n = 1 ) const
    { Matd S = LSeqMat2( hyps , i , n ); return dist0( X * S ); }

    Matd dist0( const Matd& , const Matd& ) const;

    Matd LS1dist0( const Matd& X1 , const Matd& X2 , const Vecd& hyps , const unsigned& i , const unsigned& n = 1 ) const
    { Matd S = LSeqMat1( hyps , i , n ); return dist0( X1 * S , X2 * S ); }

    Matd LS2dist0( const Matd& X1 , const Matd& X2 , const Vecd& hyps , const unsigned& i , const unsigned& n = 1 ) const
    { Matd S = LSeqMat2( hyps , i , n ); return dist0( X1 * S , X2 * S ); }

    Matd dist1( const Matd& ) const;

    Matd LS1dist1( const Matd& X , const Vecd& hyps , const unsigned& i , const unsigned& n = 1 ) const
    { Matd S = LSeqMat1( hyps , i , n ); return dist1( X * S ); }

    Matd LS2dist1( const Matd& X , const Vecd& hyps , const unsigned& i , const unsigned& n = 1 ) const
    { Matd S = LSeqMat2( hyps , i , n ); return dist1( X * S ); }

    Matd dist1( const Matd& , const Matd& ) const;

    Matd LS1dist1( const Matd& X1 , const Matd& X2 , const Vecd& hyps , const unsigned& i , const unsigned& n = 1 ) const
    { Matd S = LSeqMat1( hyps , i , n ); return dist1( X1 * S , X2 * S ); }

    Matd LS2dist1( const Matd& X1 , const Matd& X2 , const Vecd& hyps , const unsigned& i , const unsigned& n = 1 ) const
    { Matd S = LSeqMat2( hyps , i , n ); return dist1( X1 * S , X2 * S ); }

    Matd dist2( const Matd& ) const;

    Matd LS1dist2( const Matd& X , const Vecd& hyps , const unsigned& i , const unsigned& n = 1 ) const
    { Matd S = LSeqMat1( hyps , i , n ); return dist2( X * S ); }

    Matd LS2dist2( const Matd& X , const Vecd& hyps , const unsigned& i , const unsigned& n = 1 ) const
    { Matd S = LSeqMat2( hyps , i , n ); return dist2( X * S ); }

    Matd dist2( const Matd& , const Matd& ) const;

    Matd LS1dist2( const Matd& X1 , const Matd& X2 , const Vecd& hyps , const unsigned& i , const unsigned& n = 1 ) const
    { Matd S = LSeqMat1( hyps , i , n ); return dist2( X1 * S , X2 * S ); }

    Matd LS2dist2( const Matd& X1 , const Matd& X2 , const Vecd& hyps , const unsigned& i , const unsigned& n = 1 ) const
    { Matd S = LSeqMat2( hyps , i , n ); return dist2( X1 * S , X2 * S ); }

};

}

#endif
