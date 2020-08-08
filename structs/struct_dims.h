#ifndef STRUCT_DIMS_H
#define STRUCT_DIMS_H

namespace cvpp
{

// Dimensions
struct Dims
{
    unsigned r,c;

    Dims( const int& rr , const int& cc = 1 )
    {
        r = rr;
        c = cc;
    }

    unsigned s() { return r * c ; }
};

}

#endif
