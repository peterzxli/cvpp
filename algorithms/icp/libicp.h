#ifndef ICP_LIBICP_H
#define ICP_LIBICP_H

#include <cvpp/algorithms/icp/libicp/lib/icpPointToPlane.h>
#include <cvpp/algorithms/icp/libicp/lib/icpPointToPoint.h>

#include  <cvpp/containers/matrix.h>

namespace cvpp
{

TPL_T
Matrix<T> icp_calc( const Matrix<T>& M , const Matrix<T>& R , const Matrix<T>& t )
{
    return M * R.t() + t;
}

TPL_T
void icp_comb( const Matrix<T>& R1 , const Matrix<T>& R2 , Matrix<T>& R12 ,
               const Matrix<T>& t1 , const Matrix<T>& t2 , Matrix<T>& t12 )
{
    R12 = ( R1.t() * R2.t() ).t();
    t12 = t1 * R2.t() + t2;
}

TPL_T
class LibICP
{
protected:

    int d;

//    IcpPointToPlane *icp;
    IcpPointToPoint *icp;

public:

    LibICP( const Matrix<T>& M )
    {
        d = M.c();

//        icp = new IcpPointToPlane( M.raw_data() , M.r() , M.c() );
        icp = new IcpPointToPoint( M.toDouble().raw_data() , M.r() , M.c() );
    }

    ~LibICP()
    {
        delete icp;
    }

    Matrix<T> fit( const Matrix<T>& M , Matrix<T>& R , Matrix<T>& t ,
                   const double& dst = 1.0 )
    {
        if( R.empty() ) R.reset( d , d ).setIdentity();
        if( t.empty() ) t.reset( 1 , d ).setVal(0);

        MatICP RR( d , d , R.toDouble().raw_data() );
        MatICP tt( d , 1 , t.toDouble().raw_data() );

        icp->fit( M.toDouble().raw_data() , M.r() , RR , tt , dst );

        R = Matd( d , d , *RR.val ).convert<T>();
        t = Matd( 1 , d , *tt.val ).convert<T>();

        return icp_calc( M , R , t );
    }

    Matrix<T> fit( const Matrix<T>& M , const double& dst = 1.0 )
    {
        Matrix<T> R , t;
        return fit( M , R , t , dst );
    }

};

using LibICPf = LibICP<float>;
using LibICPd = LibICP<double>;

}

#include "libicp.cpp"

#endif
