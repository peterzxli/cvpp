#include "../cvis.h"

namespace cvpp {
namespace cvis
{

Pt3f triangulate( const Pt3f& x0i , const Pt3f& x0f ,
                  const Pt3f& x1i , const Pt3f& x1f )
{
    Pt3f u = x0f - x0i , v = x1f - x1i , i = x1i - x0i;
    Pt3f w = cross( u , v ); float ww = dot( w , w );

    Pt3f x0c = x0i + dot( cross( i , v ) , w ) / ww * u;
    Pt3f x1c = x1i + dot( cross( i , u ) , w ) / ww * v;

    return 0.5 * ( x0c + x1c );
}

Pts3f triangulate( const Camera& cam1 , const Pts2f& img1 ,
                   const Camera& cam2 , const Pts2f& img2 )
{
    Pts3f pts1 = cam1.u2w( img1 );
    Pts3f pts2 = cam2.u2w( img2 );

    Pt3f xyz1 = cam1.getPosPt();
    Pt3f xyz2 = cam2.getPosPt();

    Pts3f pts( pts1.n() );

    #pragma omp parallel for
    forLOOPi( pts.n() )
            pts[i] = triangulate( xyz1 , pts1[i] , xyz2 , pts2[i] );

    return pts;
}

}}
