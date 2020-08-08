#include "dsgd_compare.h"

namespace cvpp
{

// Constructor
DSGDcompare::DSGDcompare()
{
}

// Destructor
DSGDcompare::~DSGDcompare()
{
}

// Kernel // r = sqrt( 2 * len_scale ) * randn( dimno , b );
Matd
DSGDcompare::kernel( const Matd& x , const int& ri ) const
{
//    randomise( ridx(ri) );
//    Matd r( b , x.c()  );
//    r.setRandn( 0 , sqrt( 2 * len_scale ) );

//    Matd tmp = x * r.t();
//    Matd phix = tmp.cos().AppR( tmp.sin() ) / sqrt( b );

    Matd r( "../../data/doubly/r_" , ridx(ri) );
    r = r.t();

    Matd tmp = x * r.t();
    Matd phix = tmp.cos().AppR( tmp.sin() ) / sqrt( b );

    return phix;
}

int
DSGDcompare::ridx( const int& i ) const
{
    return r * n + i * b;
}

DSGDcompare&
DSGDcompare::setData( const Matd& Xtr , const Matd& Ytr ,
                       const Matd& Xte , const Matd& Yte )
{
    this->Xtr = Xtr; this->Ytr = Ytr;
    this->Xte = Xte; this->Yte = Yte;

    trainY = Ytr.lblMat();
    k = trainY.c() , d = Xtr.c();

    ntr = Xtr.r() , nte = Xte.r() ;
}

DSGDcompare&
DSGDcompare::setParams( const double& p1 , const double& p2 , const double& p3 , const double& p4 ,
                         const unsigned& p5 , const unsigned& p6 , const unsigned& p7 )
{
    Matd prm( "../../data/doubly/rperm" );
    Matd distmat = Xtr.sampleRows( prm.ru(4000).toInt() - 1 ).vecDistRows();
    double med = distmat.median();

//    Matd distmat = Xtr.sampleRows( 10 ).vecDistRows();
//    double med = distmat.median();

    len_scale = 1.0 / pow( p1 * med , 2.0 );
    reg_param = p2 , step_size0 = p3 , step_size1 = p4 ;
    n = p5 , b = p6 , nbt = p7 ;

    r = 1 ;
    int blockno = floor( n / b );
    iters = blockno / 2;

    W.reset( 2 * n , k ).setVal(0);
    W_idx.reset( 2 * b ) , Wj_idx.reset( 2 * b );

    mftr.reset( nbt , k ).setVal(0);
    mfte.reset( nte , k ).setVal(0);

    bt_idx.reset( nbt ).setIncrease();

    I.reset( 2.0 * b , 2.0 * b );
    I.setIdentity( reg_param + 1e-7 );

    iters = 5;

    return *this;
}

// Run
DSGDcompare&
DSGDcompare::train()
{
    for( int i = 0 ; i < iters ; i++ )
    {
//        if( i > 0 ) bt_idx = ( bt_idx + nbt ).mod( ntr );
        bt_idx = ( bt_idx + nbt ).mod( ntr );
        Xbt = Xtr.sampleRows( bt_idx );

        disp( "*****************************************************************" , i , iters , bt_idx(0) , bt_idx(-1) , Xtr.r() );

        W_idx.setIncrease( 2 * i * b , 1 );

        Matd Xtrf = kernel( Xbt , i );
        Matd Xtef = kernel( Xte , i );

        mftr.setVal(0);
        for( int j = 0 ; j < i ; j++ )
        {
            Wj_idx.setIncrease( 2 * j * b , 1 );
            mftr += kernel( Xbt , j ) * W.sampleRows( Wj_idx );
        }

        Matd max = mftr.maxCols();
        Matd softmax = ( mftr - max ).exp();
        softmax /= softmax.sumCols();

        Matd covmat = ( Xtrf.t() * Xtrf ) / nbt;
        Matd residue = softmax - trainY.sampleRows( bt_idx );

        Matd preconditioner = covmat + I;
        double step_size = step_size0 / ( 1.0 + step_size1 * ( i + 1 ) );
//        double step_size = step_size0 / ( 1.0 + step_size1 );

        Matd updateW = - step_size * ( preconditioner.t().bslash(
                                     ( Xtrf.t() * residue ) / nbt + reg_param * W.sampleRows( W_idx ) ) );

        for( int k = 0 ; k < W_idx.r() ; k++ )
            W.row( W_idx(k) ) += updateW.row(k);

        if( reg_param > 1e-6 )
        {
            for( int j = 0 ; j < i ; j++ )
            {
                Wj_idx.setIncrease( 2 * j * b , 1 );
                for( int k = 0 ; k < Wj_idx.r() ; k++ )
                    W.row( Wj_idx(k) ) = ( 1 - step_size * reg_param ) * W.row( Wj_idx(k) );
            }
        }

        mftr += Xtrf * updateW; mftr_idx = mftr.maxColsIDX();
        mfte += Xtef * updateW; mfte_idx = mfte.maxColsIDX();

        double train_error = mftr_idx.findDiffPerc( Ytr.sampleRows( bt_idx ) );
        double test_error  = mfte_idx.findDiffPerc( Yte );

        disp(train_error,test_error);
    }

    return *this;
}

// Run
Matd
DSGDcompare::query( const Matd& X ) const
{
    Matd mf( X.r() , k ); mf.setVal(0);
    Mati W_idx( 2 * b );

    for( int i = 0 ; i < iters ; i++ )
    {
        W_idx.setIncrease( 2 * i * b , 1 );
        mf += kernel( X , i ) * W.sampleRows( W_idx );
    }

    return mf;
}

}

