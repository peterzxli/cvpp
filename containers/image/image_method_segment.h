#include "../image.h"

namespace cvpp
{

TPL_TC inline Image<unsigned char,1>
Image<T,C>::pixelSLIC( const int& region ,
                       const int& minRegion,
                       const float& regularizer ) const
{
    Image<unsigned char,1> labels( r() , c() );

    float* image = toFloat().VLfeat();

    vl_slic_segment( labels.cv_data() ,
                     image , c() , r() , d() ,
                     region , regularizer , minRegion );

    return labels.toUChar();
}

TPL_TC inline Seq<Pt2f>
Image<T,C>::getContour() const
{
    Seq<Pt2f> pts;
    pts.reserve( this->r() * this->c() );

    unsigned label;
    for( unsigned i = 1 ; i < this->r() - 1 ; i++ )
    {   for( unsigned j = 1 ; j < this->c() - 1 ; j++ )
        {
            label = at( i , j );

            if( label != at( i + 1 , j ) || label != at( i - 1 , j ) ||
                label != at( i , j + 1 ) || label != at( i , j - 1 ) )
            {
                pts.push_back( Pt2f( j , i ) );
            }
        }
    }

    return pts;
}

}
