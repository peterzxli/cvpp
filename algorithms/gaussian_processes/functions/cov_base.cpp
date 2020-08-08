#include "./cov_base.h"

namespace cvpp
{

// Constructor
CovBase::CovBase( const unsigned& type )
{
    ls_type = type;
}

// Number of Hyperparameters
const unsigned
CovBase::ls_n( const unsigned& d ) const
{
    return n() + ( ls_type == ARD ? d : ls_type == ISO ? 1 : 0 );
}

// Calculate Diagonal (0 KK)
Matd
CovBase::calcDiag( const Matd& X ,
                   const Vecd& hyps ) const
{
    SeqMatd KK;
    return calcDiag( X , hyps , KK );
}

// Calculate Diagonal (1 KK)
Matd
CovBase::calcDiag( const Matd& X ,
                   const Vecd& hyps , SeqMatd& KK ) const
{
    KK.resize(1);
    KK[0] = calcDiag( X , hyps );
    return KK[0];
}

// Calculate Dense (0 KK)
Matd
CovBase::calcDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps ) const
{
    SeqMatd KK;
    return calcDense( X1 , X2 , hyps , KK );
}

// Calculate Dense (1 KK)
Matd
CovBase::calcDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps , SeqMatd& KK ) const
{
    KK.resize(1);
    KK[0] = calcDense( X1 , X2 , hyps );
    return KK[0];
}

// Hyp Gradient Diag (0 KK)
Matd
CovBase::gradDiag( const Matd& X ,
                   const Vecd& hyps , const unsigned& i ) const
{
    SeqMatd KK; calcDiag( X , hyps , KK );
    return gradDiag( X , hyps , KK , i );
}

// Hyp Gradient Diag (1 KK)
Matd
CovBase::gradDiag( const Matd& X ,
                   const Vecd& hyps , const SeqMatd& KK , const unsigned& i ) const
{
    return gradDiag( X , hyps , KK[0] , i );
}

// Hyp Gradient Dense (0 KK)
Matd
CovBase::gradDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps , const unsigned& i ) const
{
    SeqMatd KK; calcDense( X1 , X2 , hyps , KK );
    return gradDense( X1 , X2 , hyps , KK , i );
}

// Hyp Gradient Dense (1 KK)
Matd
CovBase::gradDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps , const SeqMatd& KK , const unsigned& i ) const
{
    return gradDense( X1 , X2 , hyps , KK[0] , i );
}

// Ind Gradient Diag (0 KK)
Matd
CovBase::gindDiag( const Matd& X ,
                   const Vecd& hyps , const unsigned& i ) const
{
    SeqMatd KK; calcDiag( X , hyps , KK );
    return gindDiag( X , hyps , KK , i );
}

// Ind Gradient Diag (1 KK)
Matd
CovBase::gindDiag( const Matd& X ,
                   const Vecd& hyps , const SeqMatd& KK , const unsigned& i ) const
{
    return gindDiag( X , hyps , KK[0] , i );
}

// Ind Gradient Dense (0 KK)
Matd
CovBase::gindDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps , const unsigned& i ) const
{
    SeqMatd KK; calcDense( X1 , X2 , hyps , KK );
    return gindDense( X1 , X2 , hyps , KK , i );
}

// Ind Gradient Dense (1 KK)
Matd
CovBase::gindDense( const Matd& X1 , const Matd& X2 ,
                    const Vecd& hyps , const SeqMatd& KK , const unsigned& i ) const
{
    return gindDense( X1 , X2 , hyps , KK[0] , i );
}

// Length-Scale Matrix 1
Matd
CovBase::LSeqMat1( const Vecd& hyps ,
                 const unsigned& i , const unsigned& n ) const
{
    if( ls_type == ARD )
        return ( - 1.0 * hyps( i , n ).mat() ).exp().diag();
    if( ls_type == ISO )
        return ( - 1.0 * hyps( i , 1 ).mat().repRows( n ) ).exp().diag();
}

// Length-Scale Matrix 2
Matd
CovBase::LSeqMat2( const Vecd& hyps ,
                 const unsigned& i , const unsigned& n ) const
{
    if( ls_type == ARD )
        return ( - 2.0 * hyps( i , n ).mat() ).exp().diag();
    if( ls_type == ISO )
        return ( - 2.0 * hyps( i , 1 ).mat().repRows( n ) ).exp().diag();
}

// Distance Matrix 0
Matd
CovBase::dist0( const Matd& X ) const
{
    Matd XX1 = X.repCols( X.r() );
    Matd XX2 = XX1.t();

    return XX1 - XX2;
}

// Distance Matrix 0
Matd
CovBase::dist0( const Matd& X1 , const Matd& X2 ) const
{
    Matd XX1 = X1.repCols( X2.r() );
    Matd XX2 = X2.t().repRows( X1.r() );

    return XX1 - XX2;
}

// Distance Matrix 1
Matd
CovBase::dist1( const Matd& X ) const
{
    return dist2( X ).Sqrt();
}

// Distance Matrix 1
Matd
CovBase::dist1( const Matd& X1 , const Matd& X2 ) const
{
    return dist2( X1 , X2 ).Sqrt();
}

// Distance Matrix 2
Matd
CovBase::dist2( const Matd& X ) const
{
    return dist2( X , X );
}

// Distance Matrix 2
Matd
CovBase::dist2( const Matd& X1 , const Matd& X2 ) const
{
    Matd D( X1.r() , X2.r() );
    D.setVal(0);

    for( unsigned k = 0 ; k < X1.c() ; k++ )
        D += ( X1.c(k).repCols( X2.r() )
             - X2.c(k).t().repRows( X1.r() ) ).Square();

    return D;
}

}









//// Distance Matrix 0
//Matd
//CovBase::dist0( const Matd& X ) const
//{
//    Matd XX1 = X.repCols( X.r() );
//    Matd XX2 = XX1.t();

//    return XX1 - XX2;
//}

//// Distance Matrix 0
//Matd
//CovBase::dist0( const Matd& X1 , const Matd& X2 ) const
//{
//}

//// Distance Matrix 1
//Matd
//CovBase::dist1( const Matd& X ) const
//{
//    return dist2( X ).sqrt();
//}

//// Distance Matrix 1
//Matd
//CovBase::dist1( const Matd& X1 , const Matd& X2 ) const
//{
//    return dist2( X1 , X2 ).sqrt();
//}

//// Distance Matrix 2
//Matd
//CovBase::dist2( const Matd& X ) const
//{
//    Matd XX1 = ( X % X ).sumCols().repCols( X.r() );
//    Matd X11 = X * X.t();

//    return ( XX1 + XX1.t() - 2.0 * X11 ).abs();
//}

//// Distance Matrix 2
//Matd
//CovBase::dist2( const Matd& X1 , const Matd& X2 ) const
//{
//    Matd XX1 = ( X1 % X1 ).sumCols().repCols( X2.r() );
//    Matd XX2 = ( X2 % X2 ).sumCols().repCols( X1.r() );
//    Matd X12 = X1 * X2.t();

//    return ( XX1 + XX2.t() - 2.0 * X12 ).abs();
//}
