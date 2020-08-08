#ifndef HM_shape_H
#define HM_SHAPE_H

#include <cvpp/modules/algl.h>

#include "./feats/hm_shape_feat_base.h"
#include "./regrs/hm_shape_regr_base.h"

namespace cvpp
{

class HMshape
{

protected:

    unsigned batch;

public:

    HMfeatBase* feature;
    HMregrBase* regressor;

public:

    HMshape( HMfeatBase* , HMregrBase* , const unsigned& = 2000 );
    ~HMshape();

    unsigned totalPoints( const SeqMatd& ) const;
    const Matd& weights() const { return regressor->weights; }

    HMshape& add( const Matd& , const Matd& , const SeqMatd& );
    HMshape& add( const Matd& , const Matd& , const SeqMatd& , const SeqMatd& );
    HMshape& add( const Matd& , const Matd& , const Matd& , const SeqMatd& , const SeqMatd& );

    SeqMatd calcFeatures( const Matd& , const int& ) const;
    SeqMatd calcFeatures( const Matd& , const Matd& , const int& ) const;

    HMshape& train( const SeqMatd& , const Matd& );
    HMshape& train( const Matd& pts , const Matd& prob , const int& f )
    { return train( calcFeatures( pts , prob , f ) , prob ); }

    Matd query( const SeqMatd& ) const;
    Matd query( const Matd& pts , const int& f ) const
    { return query( calcFeatures( pts , f ) ); }

};

// Orientation
inline Matd
orient( const SeqMatd& S )
{
    Matd O( S.size() , S[0].r() );

    Matd x( 1 , O.c() );
    forLOOPi( O.r() )
    {
        Matd val , vec ;
        S[i].eigen( val , vec );
        vec = vec.t();

        if( O.c() == 2 )
        {
            if( val(0) < val(1) ) O.row(i) = vec.row(0) ;
            if( val(1) < val(0) ) O.row(i) = vec.row(1) ;
        }
        if( O.c() == 3 )
        {
            if( val(0) < val(1) && val(0) < val(2) ) O.row(i) = vec.row(0) ;
            if( val(1) < val(0) && val(1) < val(2) ) O.row(i) = vec.row(1) ;
            if( val(2) < val(0) && val(2) < val(1) ) O.row(i) = vec.row(2) ;
        }
    }

    return O;
}

// Linear Distance
inline double
ddist( const Eigd& X1 , const Eigd& S1 ,
       const Eigd& X2 , const Eigd& S2 )
{
    Eigd D = X1 - X2 , S = S1 + S2 ;
    return sqrt( ( D * ( S * S ).inverse() * D.transpose() )(0) );
}

// Linear Distance
inline double
ddist( const Eigd& X1 , const Eigd& S1 ,
       const Eigd& X2 )
{
    Eigd D = X1 - X2;
    return sqrt( ( D * S1.inverse() * D.transpose() )(0) );
}

// Angular Distance
inline double
adist( const Eigd& O1 , const Eigd& O2 )
{
    return acos( O1(0) * O2(0) +
                 O1(1) * O2(1) +
                 O1(2) * O2(2) );
}

// Remove
inline void
remove( Mati& N , Matd& Z , Mati& I ,
        SeqMatd& P , SeqMatd& M , SeqMatd& S , const int& thr )
{
    int cnt = 0;
    forLOOPi( Z.r() )
    {
        if( N(i) > thr )
        {
            cnt++;
        }
        else
        {
            int j = i + 1;
            while( N(j) <= thr && j < Z.r() ) j++;
            if( j < Z.r() )
            {
                Z.r(cnt) = Z.r(j); N.r(cnt) = N.r(j);
                P[cnt] = P[j]; M[cnt] = M[j]; S[cnt] = S[j];
                N(j) = 0; cnt++;
            }
            else
            {
                break;
            }
        }
    }

    Z.KeepU( cnt ); N.KeepU( cnt );
    P.resize( cnt ); M.resize( cnt ); S.resize( cnt );
}

inline const void
filter( const Matd& X , Matd& Z , Mati& I ,
        SeqMatd& P , SeqMatd& M , SeqMatd& S , const int& thr )
{
    int j = Z.r() - 1;

    forLOOPi( Z.r() )
    {
        if( P[i].r() <= thr )
        {
            while( P[j].r() <= thr && j > i ) j--;
            if( j <= i ) break;

            Z.row(i) = Z.row(j);
            P[i] = P[j]; M[i] = M[j]; S[i] = S[j];

            j--;
        }
    }

    j++;

    Z.KeepU(j);
    P.resize(j); M.resize(j); S.resize(j);
    I = X.closestRowsLBL( Z );
}

inline const void
filter2( Matd& X , Matd& Z , Mati& I ,
         SeqMatd& P , SeqMatd& M , SeqMatd& S , const int& thr )
{
    int j = Z.r() - 1;
    Matd idx( X.r() );
    idx.setVal( 1 );

    int cnt = 0 , sum = 0;
    forLOOPi( Z.r() )
    {
        cnt++;
        if( P[i].r() <= thr )
        {
            sum += P[i].r();
            #pragma omp parallel for
            forLOOPj( I.r() ) if( I(j) == i ) idx(j) = 0;

            while( P[j].r() <= thr && j > i ) j--;
            if( j <= i )
            {
                forLOOPkk( i + 1 , Z.r() )
                {
                    if( P[k].r() <= thr )
                    {
                        sum += P[k].r();
                        #pragma omp parallel for
                        forLOOPj( I.r() ) if( I(j) == k ) idx(j) = 0;
                    }
                }
                break;
            }

            Z.row(i) = Z.row(j);
            P[i] = P[j]; M[i] = M[j]; S[i] = S[j];
            j--;
        }
    }

    Z.KeepU(j);
    P.resize(j); M.resize(j); S.resize(j);

    X.SampleRows( idx == 1 );
    I = X.closestRowsLBL( Z );
}


// Recluster_step
inline bool
recluster_step( Matd& X , Matd& Z , Mati& I , SeqMatd& P , SeqMatd& M , SeqMatd& S ,
                Mati& N , const double& lthr , const double& athr )
{
    int m = S.size();

    Matd O = orient( S );
    Matd dA( m , m ) , dD( m , m );

    SeqMatd SS( S.size() );
    forLOOPi( S.size() ) SS[i] = S[i].matsqrt();

    #pragma omp parallel for
    forLOOPi( m ) forLOOPjj( i + 1 , m )
    {
        dA(i,j) = adist( O.row(i) , O.row(j) );
        if( dA(i,j) < athr || dA(i,j) > PI - athr )
             dD(i,j) = ddist( Z.row(i) , SS[i].eig() , Z.row(j) , SS[j].eig() );
        else dD(i,j) = 1e12;
    }

    int cnt = 0;
    Mati C = MatXXi( m ).setVal(-1);
    forLOOPi( m )
    {
        STDi idx;
        forLOOPjj( i + 1 , m )
            if( dD(i,j) < lthr )
                idx.push_back(j);

        int min = C[i];
        forLOOPj( idx.size() )
            if( min < C[idx[j]] & C[idx[j]] > -1 ) min = C[idx[j]];

        if( min == -1 ) min = cnt++;

        C[i] = min;
        forLOOPj( idx.size() )
            C[idx[j]] = C[i];
    }

    #pragma omp parallel for
    forLOOPi( I.r() ) I(i) = C[I(i)];
    X.mcovRows( I , P , M , S );

    Z.reset( M.size() , X.c() );
    forLOOPi( Z.r() ) Z.row(i) = M[i].eig();

    Mati NN( Z.r() ); NN.setVal(0);
    forLOOPi( C.r() ) NN( C(i) ) += N(i);
    N = NN;
}

// Recluster_step
inline bool
recluster_step2( Matd& X , Matd& Z , Mati& I , SeqMatd& P , SeqMatd& M , SeqMatd& S ,
                 Mati& N , const double& lthr , const double& athr )
{
    int m = S.size();

    Matd O = orient( S );
    Matd dA( m , m ) , dD( m , m );

    SeqMatd SS( S.size() );
    forLOOPi( S.size() ) SS[i] = S[i].matsqrt();

    #pragma omp parallel for
    forLOOPi( m ) forLOOPjj( i + 1 , m )
    {
        dA(i,j) = adist( O.row(i) , O.row(j) );
        if( dA(i,j) < athr || dA(i,j) > PI - athr )
             dD(i,j) = ddist( Z.row(i) , SS[i].eig() , Z.row(j) , SS[j].eig() );
        else dD(i,j) = 1e12;
    }

    int cnt = 0;
    Mati C = MatXXi( m ).setVal(-1);
    forLOOPi( m )
    {
        STDi idx;
        forLOOPjj( i + 1 , m )
            if( dD(i,j) < lthr )
                idx.push_back( j );

        if( C[i] != -1 )
        {
            forLOOPj( idx.size() )
                C[idx[j]] = C[i];
        }
        else
        {
            forLOOPj( idx.size() )
                C[i] = C[idx[j]];

            if( C[i] == -1 )
            {
                C[i] = cnt++;
                forLOOPj( idx.size() )
                    C[idx[j]] = C[i];
            }
        }
    }

    #pragma omp parallel for
    forLOOPi( I.r() ) I(i) = C[I(i)];
    X.mcovRows( I , P , M , S );

    Z.reset( M.size() , X.c() );
    forLOOPi( Z.r() ) Z.row(i) = M[i].eig();

    Mati NN( Z.r() ); NN.setVal(0);
    forLOOPi( C.r() ) NN( C(i) ) += N(i);
    N = NN;
}

// Recluster
inline Mati
recluster( Matd& X , Matd& Z , Mati& I , SeqMatd& P , SeqMatd& M , SeqMatd& S ,
           const double& lthr , const double& athr , const int& qty = 5 )
{
    Mati N( Z.r() ); N.setVal(1);
    int cm = Z.r() , pm = cm + 1;

    while( true )
    {
        pm = Z.r(); disp( "pm" , pm );
        recluster_step2( X , Z , I , P , M , S , N , lthr , athr );
        cm = Z.r(); disp( "cm" , cm );

        if( pm == cm )
            break;
    }

    if( qty > 0 )
        remove( N , Z , I , P , M , S , qty );

    return N;
}

// Separate
inline void
separate( Matd& X , Matd& Z , Mati& I ,
          SeqMatd& P , SeqMatd& M , SeqMatd& S , const int& m )
{
    Matd ZZ( 0 , Z.c() );
    forLOOPi( Z.r() )
    {
        Matd Zt ; Mati It; P[i].kmeans( m , Zt , It );
        SeqMatd Pt,Mt,St; P[i].mcovRows( It , Pt,  Mt , St );

        ZZ = ZZ | Zt;
        forLOOPj( Pt.size() ) P.push_back( Pt[j] );
        forLOOPj( Mt.size() ) M.push_back( Mt[j] );
        forLOOPj( St.size() ) S.push_back( St[j] );
    }

    Z = ZZ; I = X.closestRowsLBL( Z );
    X.mcovRows( I , P,  M , S );
}

// Colorize
inline Matd
colorize( const Matd& X , const Matd& Z , const Matd& W ,
          const SeqMatd& S )
{
    Matd color( X.r() , 3 );

    #pragma omp parallel for
    forLOOPi( X.r() )
    {
        double best = PINF;
        forLOOPj( Z.r() )
        {
            if( W(j) == 1 )
            {
                double curr = ddist( Z.row(j) , S[j].eig() , X.row(i) );
                if( curr < best )
                {
                    best = curr; Scalar clr = COLOR(j);
                    color.row(i) << clr(0) , clr(1) , clr(2);
                }
            }
        }
    }

    return color;
}

// Colorize
inline Matd
colorize( const Matd& X , const Matd& Y , const Matd& Z , const Matd& W ,
          const SeqMatd& S )
{
    Matd color( X.r() , 3 );

    #pragma omp parallel for
    forLOOPi( X.r() )
    {
        if( Y(i) > 0.52 )
        {
            double best = PINF;
            forLOOPj( Z.r() )
            {
                if( W(j) == 1 )
                {
                    double curr = ddist( Z.row(j) , S[j].eig() , X.row(i) );
                    if( curr < best )
                    {
                        best = curr; Scalar clr = COLOR(j);
                        color.row(i) << clr(0) , clr(1) , clr(2);
                    }
                }
            }
        }
        else
        {
            color.row(i) << 1.0 , 1.0 , 1.0 ;
        }
    }

    return color;
}

// Align distance
inline double
dist( const Eigd& d , const Eigd& dd ,
      const Eigd& iS , const Eigd& val )
{
    double res;
    res = dd(0) < val(0) && dd(1) < val(1) && dd(2) < val(2) ?
          std::exp( - ( d * iS * d.transpose() )(0) ) : 0.0 ;
    return res;
}

// Align total distance
inline double
totDist( const Matd& D , const Matd& iS , const Matd& W1 , const Matd& W2 ,
         const Matd& val , const Matd& vec , const double& ang = 0 )
{
    Matd tmp = vec * algl::rotationAxis( W1 , W2 , ang );
    Matd DD = ( D * tmp.t() ).Square();

    Matd res = MatZEROSd( D.r() );

    #pragma omp parallel for
    forLOOPi( D.r() )
        res(i) = dist( D.row(i) , DD.row(i) , iS.eig() , val.eig() );

    return res.sum();
}

// Align search
inline bool
search( const Matd& D , const Matd& iS , const Matd& W1 , const Matd& W2 ,
        const Matd& val , const Matd& vec , double& ang , double& best ,
        const double& jmp1 , const double& jmp2 )
{
    double  curr;
    bool flag = false;

    curr = totDist( D , iS , W1 , W2 , val , vec , ang += jmp1 );
    if( curr > best ) flag = true;

    while( curr > best )
    {
        best = curr;
        curr = totDist( D , iS , W1 , W2 , val , vec , ang += jmp1 );
    }

    if( flag )
    {
        curr = totDist( D , iS , W1 , W2 , val , vec , ang += jmp2 );
        while( curr == best )
        {
            best = curr;
            curr = totDist( D , iS , W1 , W2 , val , vec , ang += jmp2 );
        }
        ang -= jmp2;
    }
    else
    {
        ang -= jmp1;
    }

    return flag;
}

// Align bounds
inline const void
bounds( const Matd& D , const Matd& iS , const Matd& W1 , const Matd& W2 ,
        const Matd& val , const Matd& vec , double& ang , double& best ,
        const double& jmp1 , const double& jmp2 )
{
    double  curr;

    curr = totDist( D , iS , W1 , W2 , val , vec , ang += jmp1 );
    while( curr == best )
        curr = totDist( D , iS , W1 , W2 , val , vec , ang += jmp1 );

    curr = totDist( D , iS , W1 , W2, val , vec , ang += jmp2 );
    while( curr != best )
        curr = totDist( D , iS , W1 , W2 , val , vec , ang += jmp2 );
}

// Align center
inline const void
center( const Matd& D , const Matd& iS , const Matd& W1 , const Matd& W2 ,
        const Matd& val , const Matd& vec , double& ang , double& best ,
        const double& jmp = 1.0 )
{
    double ang1 = 0 , ang2 = 0 ;
    best = totDist( D , iS , W1 , W2 , val , vec , ang );

    if( search( D , iS , W1 , W2 , val , vec , ang , best , +2.0 , -0.1 ) )
    {
        ang1 = ang;
        bounds( D , iS , W1 , W2 , val , vec , ang , best , +2.0 , -0.1 );
        ang2 = ang;
    }
    else
    if( search( D , iS , W1 , W2 , val , vec , ang , best , -2.0 , +0.1 ) )
    {
        ang1 = ang;
        bounds( D , iS , W1 , W2 , val , vec , ang , best , -2.0 , +0.1 );
        ang2 = ang;
    }

    ang = ( ang1 + ang2 ) / 2;
}

// Align
inline const void
align( const Matd& D , const Matd& O , Matd& S , Matd& iS ,
       Matd& val , Matd& vec )
{
    iS = ( 2.0 * S ).inverse(); S = 4.0 * S;
    S.eigen( val , vec ) ; vec = vec.t();

    Matd W1,W2;
    algl::rotationAuxMat( O , W1 , W2 );

    double ang = 0 , best = 0;
    center( D , iS , W1 , W2 , val , vec , ang , best );

    vec *= algl::rotationAxis( W1 , W2 , ang );
}

// Align All
inline const void
align( const SeqMatd& P , const Matd& M , SeqMatd& S ,
       SeqMatd& iS , SeqMatd& vals , SeqMatd& vecs )
{
    int n = S.size();

    Matd O = orient( S );
    iS.resize( n ); vals.resize( n ); vecs.resize( n );

    #pragma omp parallel for
    forLOOPi( n )
    {
        Matd D = P[i] - M.r(i);
        align( D , O.r(i) , S[i] , iS[i] , vals[i] , vecs[i] );
        vecs[i] = vecs[i].t();
    }
}

}

#endif
