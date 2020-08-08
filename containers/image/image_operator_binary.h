#include "../image.h"

namespace cvpp
{

// ********************************************************** VALUE

// Image + Value
TPL_TCU inline Image<T,C>
operator+( const Image<T,C>& img , const U& val )
{
    return img.clone() += val;
}

// Image - Value
TPL_TCU inline Image<T,C>
operator-( const Image<T,C>& img , const U& val )
{
    return img.clone() -= val;
}

// Image * Value
TPL_TCU inline Image<T,C>
operator*( const Image<T,C>& img , const U& val )
{
    return img.clone() *= val;
}

// Image / Value
TPL_TCU inline Image<T,C>
operator/( const Image<T,C>& img , const U& val )
{
    return img.clone() /= val;
}

}
