#ifndef DSGD_COMPARE_H
#define DSGD_COMPARE_H

#include <cvpp/containers/matrix.h>

namespace cvpp
{

class DSGDcompare
{

protected:

    Matd Xtr , Ytr , Xte , Yte , Xbt , trainY ;
    Mati bt_idx ;

    Matd mftr , mfte ;
    Mati mftr_idx , mfte_idx ;

    Mati lbl , prm ;

    Matd W , I ;
    Mati W_idx , Wj_idx ;

    int k , d , n , b , r ;
    int ntr , nte , nbt , iters ;
    double len_scale , reg_param , step_size0 , step_size1 ;

public:

    DSGDcompare();
    ~DSGDcompare();

    int ridx( const int& ) const;
    const Matd& weights() const { return W; }

    Matd kernel( const Matd& , const int& ) const;

    DSGDcompare& setData( const Matd& , const Matd& ,
                           const Matd& , const Matd& );
    DSGDcompare& setParams( const double& , const double& , const double& , const double& ,
                             const unsigned& , const unsigned& , const unsigned& );

    DSGDcompare& train();
    Matd query( const Matd& ) const;

};

}

#endif

































//    Matd Xtr; Xtr.loadBIN( "../../data/doubly/m8_Xtr_01.bin" ); Xtr = Xtr.t();
//    Matd Ytr; Ytr.loadBIN( "../../data/doubly/m8_Ytr_01.bin" );
//    Matd Xte; Xte.loadBIN( "../../data/doubly/m8_Xte_02.bin" ); Xte = Xte.t();
//    Matd Yte; Yte.loadBIN( "../../data/doubly/m8_Yte_02.bin" );

//    Xtr.NormCols();
//    Xte.NormCols();

//    Matd trainY = Ytr.lblMat();
//    int k = trainY.c();

//    Matd lbld( "../../data/doubly/subsample" ) , prmd( "../../data/doubly/rperm" );
//    Mati lbl = lbld.toInt() - 1 , prm = prmd.toInt() - 1 ;

////    Matd pca = Xtr.sampleRows( lbl ).pca( 100 );
//    Matd pca( "../../data/doubly/v" );

//    Xtr = Xtr * pca; Xte = Xte * pca;

//    Matd distmat = Xtr.sampleRows( prm.ru(4000) ).vecDistRows();
//    double med = distmat.median();

//    double s_coeff = 1.0 , s = 1.0 / pow( s_coeff * med , 2.0 );
//    double reg_param = 0 , step_size0 = 1 , step_size1 = 1e-4;

//    int n = pow( 2 , 20 ) , b = 4096 , r = 1;
//    int ntr = Xtr.r() , nte = Xte.r();
//    int nbt = 2000;

//    int blockno = floor( n / b );
//    int iters = blockno / 2;

//    Matd W( 2 * n , k ); W.setVal(0);
//    Mati W_idx( 2 * b ) , Wj_idx( 2 * b );

//    Matd mftr( nbt , k ); mftr.setVal(0);
//    Matd mfte( nte , k ); mfte.setVal(0);
//    Mati mftr_idx , mfte_idx;

//    Matd Xbt;
//    Mati bt_idx( nbt );
//    bt_idx.setIncrease();

//    Matd I( 2.0 * b , 2.0 * b );
//    I.setIdentity( reg_param + 1e-7 );

//    for( int i = 0 ; i < iters ; i++ )
//    {
//        disp( "*****************************************************************" , i );

//        bt_idx = ( bt_idx + nbt ).mod( ntr );
//        Xbt = Xtr.sampleRows( bt_idx );

//        W_idx.setIncrease( 2 * i * b , 1 );

//        Matd Xtrf = rbf( Xbt , s , b , r * n + i * b );
//        Matd Xtef = rbf( Xte , s , b , r * n + i * b );

//        mftr.setVal(0);
//        for( int j = 0 ; j < i ; j++ )
//        {
//            Wj_idx.setIncrease( 2 * j * b , 1 );
//            mftr += rbf( Xbt , s , b , r * n + j * b ) * W.sampleRows( Wj_idx );
//        }

//        Matd max = mftr.maxCols();
//        Matd softmax = ( mftr - max ).exp();
//        softmax /= softmax.sumCols();

//        Matd residue = softmax - trainY.sampleRows( bt_idx );
//        Matd covx = ( Xtrf.t() * Xtrf ) / nbt;

//        Matd preconditioner = covx + I;
//        double step_size = step_size0 / ( 1.0 + step_size1 * ( i + 1 ) );

//        Matd updateW = - step_size * ( preconditioner.t().bslash(
//                                     ( Xtrf.t() * residue ) / nbt + reg_param * W.sampleRows( W_idx ) ) );

//        for( int i = 0 ; i < W_idx.r() ; i++ )
//            W.row( W_idx(i) ) += updateW.row(i);

//        mftr += Xtrf * updateW; mftr_idx = mftr.maxColsIDX();
//        mfte += Xtef * updateW; mfte_idx = mfte.maxColsIDX();

//        double train_error = mftr_idx.findDiffPerc( Ytr.sampleRows( bt_idx ) );
//        double test_error  = mfte_idx.findDiffPerc( Yte );

//        disp(train_error,test_error);

//        halt();
//    }
