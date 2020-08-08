#ifndef ARRAY_H
#define ARRAY_H

#include <cvpp/auxiliar/definitions.h>

namespace cvpp
{

TPL_TC
class Array
{

protected:

    T data[ C ];

public:

    Array();

    Array( const T& v0 ) : Array()
    { data[0] = v0; }

    Array( const T& v0 , const T& v1 ) : Array()
    { data[0] = v0; data[1] = v1; }

    Array( const T& v0 , const T& v1 , const T& v2 ) : Array()
    { data[0] = v0; data[1] = v1; data[2] = v2; }

    Array( const T& v0 , const T& v1 , const T& v2 , const T& v3 ) : Array()
    { data[0] = v0; data[1] = v1; data[2] = v2; data[3] = v3; }

    Array( const T& v0 , const T& v1 , const T& v2 , const T& v3 , const T& v4 ) : Array()
    { data[0] = v0; data[1] = v1; data[2] = v2; data[3] = v3; data[4] = v4; }

    Array( const T& v0 , const T& v1 , const T& v2 , const T& v3 , const T& v4 , const T& v5 ) : Array()
    { data[0] = v0; data[1] = v1; data[2] = v2; data[3] = v3; data[4] = v4; data[5] = v5; }

    Array( const T& v0 , const T& v1 , const T& v2 , const T& v3 , const T& v4 , const T& v5 , const T& v6 ) : Array()
    { data[0] = v0; data[1] = v1; data[2] = v2; data[3] = v3; data[4] = v4; data[5] = v5; data[6] = v6; }

    // PRINT

    void print() const;
    void info() const;

    T& operator[]( const int& idx ) { return data[idx]; }
    const T& operator[]( const int& idx ) const { return data[idx]; }

    // SET

    Array<T,C>& setVal( const T& );
    Array<T,C>& setVal() { return setVal(0); }

    Array<T,C>& setIncrease( const T& , const T& );
    Array<T,C>& setIncrease( const T& step ) { return setIncrease( 0 , step ); }
    Array<T,C>& setIncrease() { return setIncrease( 0 , 1 ); }

    // OPERATOR_UNARY

    TPL_U Array<T,C>& operator+=( const U& val );
    TPL_U Array<T,C>& operator-=( const U& val );
    TPL_U Array<T,C>& operator*=( const U& val );
    TPL_U Array<T,C>& operator/=( const U& val );

//    TPL_U Array<T,C>& add( const U& val ) { return *this += val; }
//    TPL_U Array<T,C>& sub( const U& val ) { return *this -= val; }
//    TPL_U Array<T,C>& mlt( const U& val ) { return *this *= val; }
//    TPL_U Array<T,C>& div( const U& val ) { return *this /= val; }


};

TPL_C using Arri = Array<int,C>;
TPL_C using Arrf = Array<float,C>;
TPL_C using Arrd = Array<double,C>;
TPL_C using Arru = Array<unsigned int,C>;
TPL_C using Arrc = Array<unsigned char,C>;

using Arr1i = Arri<1>; using Arr1f = Arrf<1>; using Arr1d = Arrd<1>; using Arr1u = Arru<1>; using Arr1c = Arrc<1>;
using Arr2i = Arri<2>; using Arr2f = Arrf<2>; using Arr2d = Arrd<2>; using Arr2u = Arru<2>; using Arr2c = Arrc<2>;
using Arr3i = Arri<3>; using Arr3f = Arrf<3>; using Arr3d = Arrd<3>; using Arr3u = Arru<3>; using Arr3c = Arrc<3>;
using Arr4i = Arri<4>; using Arr4f = Arrf<4>; using Arr4d = Arrd<4>; using Arr4u = Arru<4>; using Arr4c = Arrc<4>;
using Arr5i = Arri<5>; using Arr5f = Arrf<5>; using Arr5d = Arrd<5>; using Arr5u = Arru<5>; using Arr5c = Arrc<5>;
using Arr6i = Arri<6>; using Arr6f = Arrf<6>; using Arr6d = Arrd<6>; using Arr6u = Arru<6>; using Arr6c = Arrc<6>;
using Arr7i = Arri<7>; using Arr7f = Arrf<7>; using Arr7d = Arrd<7>; using Arr7u = Arru<7>; using Arr7c = Arrc<7>;

}

#include "array_src.h"

#endif
