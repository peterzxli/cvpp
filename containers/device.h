#ifndef DEVICE_H
#define DEVICE_H

#include <arrayfire.h>
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>

#include <cvpp/containers/base.h>
#include <cvpp/auxiliar/definitions/definitions_device.h>

namespace cvpp
{

TPL_T class Matrix;

TPL_T
class Device : public Base<T>
{

protected:

    Pointer< afArray > raw_ptr;
    Pointer< afProxy > arr_ptr;

public:

    // Constructor

    Device();

    Device( const afArray& , const bool& = SHARE );
    Device( const afProxy& , const bool& = SHARE );

    Device( const Device<T>& , const bool& = SHARE );

    Device( const Device<T>& ,
            const int& , const int& ,
            const int& , const int& );

    Device( const Matrix<T>& );

    Device( const Dims& );
    Device( const int& , const int& = 1 );

    Device( const int& , const int& , T* );


    // Initialise

    void initialise( const int& , const int& );
    void initialise( const int& , const int& , T* );
    void initialise( const Device<T>& ,
                     const int& , const int& ,
                     const int& , const int& );

    // Info

    Device<T> clone() const { return Device<T>( *this , COPY ); }

    const int r() const { return arr_ptr->dims(0); }
    const int c() const { return arr_ptr->dims(1); }
    const int s() const { return r() * c(); }

    const bool fits( const afArray& afa ) const { return r() == afa.dims(0) && c() == afa.dims(1); }

    Dims dims() const { return Dims( r() , c() ); }
    Dims tims() const { return Dims( c() , r() ); }

    // Data

    afArray& raw() const { return *raw_ptr.get(); }
    afProxy& arr() const { return *arr_ptr.get(); }

    afProxy operator()( const int& r , const int& c = 1 ) { return (*raw_ptr)(r,c); }
    const afProxy operator()( const int& r , const int& c = 1 ) const { return (*raw_ptr)(r,c); }

    Device<T>& cudaTo( T* ptr , const int& n , const int& off1 = 0 , const int& off2 = 0 ) const
    { cudaMemcpy( ptr + off1 , arr().template device<T>() + off2 , n * sizeof(T) , cudaMemcpyDeviceToDevice ); }

    Device<T>& cudaFrom( const T* ptr , const int& n , const int& off1 = 0 , const int& off2 = 0 )
    { cudaMemcpy( arr().template device<T>() + off1 , ptr + off2 , n * sizeof(T) , cudaMemcpyDeviceToDevice ); }

    Device<T>& cudaTo( T* ptr ) const { cudaTo( ptr , s() , 0 , 0 ); }
    Device<T>& cudaFrom( const T* ptr ) { cudaFrom( ptr , s() , 0 , 0 ); }

    T* ptr() const { return arr().template device<T>(); }

    // afProxy

    afProxy row( const int& r0 ) const { return arr().row( r0 ); }
    afProxy row( const int& r0 , const int& nr ) const { return arr().rows( r0 , r0 + nr - 1 ); }

    afProxy col( const int& c0 ) const { return arr().col( c0 ); }
    afProxy col( const int& c0 , const int& nc ) const { return arr().cols( c0 , c0 + nc - 1 ); }

    // Blocks

    Device<T> r( const int& r0 ) const
    { return Device<T>( *this , r0 , 0 , 1 , c() ); }

    Device<T> c( const int& c0 ) const
    { return Device<T>( *this , 0 , c0 , r() , 1 ); }

    Device<T> r( const int& r0 ,  const int& nr ) const
    { return Device<T>( *this , r0 , 0 , nr , c() ); }

    Device<T> c( const int& c0 ,  const int& nc ) const
    { return Device<T>( *this , 0 , c , r() , nc ); }

    Device<T> b( const int& r0 ,  const int& c0 ,
              const int& nr , const int& nc ) const
    { return Device<T>( *this , r0 , c0 , nr , nc ); }

    // PRINT

    void print() const;
    void info() const;

    // OPERATOR_ATTRIB

    Device<T>& operator>>( const Device<T>& );
    Device<T>& operator= ( const Device<T>& );
    Device<T>& operator<<( const Device<T>& );

    Device<T>& share(  const Device<T>& dev ) { return *this >> dev; }
    Device<T>& assign( const Device<T>& dev ) { return *this =  dev; }
    Device<T>& copy(   const Device<T>& dev ) { return *this << dev; }

    Device<T>& operator>>( const afArray& );
    Device<T>& operator= ( const afArray& );
    Device<T>& operator<<( const afArray& );

    Device<T>& share(  const afArray& afa ) { return *this >> afa; }
    Device<T>& assign( const afArray& afa ) { return *this =  afa; }
    Device<T>& copy(   const afArray& afa ) { return *this << afa; }

    Device<T>& operator>>( const afProxy& );
    Device<T>& operator= ( const afProxy& );
    Device<T>& operator<<( const afProxy& );

    Device<T>& share(  const afProxy& afp ) { return *this >> afp; }
    Device<T>& assign( const afProxy& afp ) { return *this =  afp; }
    Device<T>& copy(   const afProxy& afp ) { return *this << afp; }

    Device<T>& operator<<( const Matrix<T>& );

    Device<T>& copy( const Matrix<T>& mat ) { return *this << mat; }

    // OPERATOR_UNARY

    TPL_U Device<T>& operator+=( const U& );
    TPL_U Device<T>& operator-=( const U& );
    TPL_U Device<T>& operator*=( const U& );
    TPL_U Device<T>& operator/=( const U& );

    Device<T>& operator+=( const Device<T>& );
    Device<T>& operator-=( const Device<T>& );
    Device<T>& operator*=( const Device<T>& );
    Device<T>& operator%=( const Device<T>& );
    Device<T>& operator/=( const Device<T>& );

    // METHOD_SET

    Device<T>& setVal( const T& );

    // METHOD_REDUCTION

    T sum() const { return af::sum<T>( arr() ); }
    T prod() const { return af::mul<T>( arr() ); }

    T det() const { return af::det<T>( arr() ); }

    T min() const { return af::min<T>( arr() ); }
    T max() const { return af::max<T>( arr() ); }

    T mean() const { return af::mean<T>( arr() ); }

    T median() const { return af::median<T>( arr() ); }

    Device<T> minRows() const { return af::min( arr() , 0 ); }
    Device<T> minCols() const { return af::min( arr() , 1 ); }

    Device<T> maxRows() const { return af::max( arr() , 0 ); }
    Device<T> maxCols() const { return af::max( arr() , 1 ); }

    Device<T> meanRows() const { return af::mean( arr() , 0 ); }
    Device<T> meanCols() const { return af::mean( arr() , 1 ); }

    Device<T> varRows() const { return af::var( arr() , false , 0 ); }
    Device<T> varCols() const { return af::var( arr() , false , 1 ); }


    // METHOD_CHOLESKY

    Device<T> chol() const;

    // METHOD_SOLVE

    Device<T> bslash( const Device<T>& ) const;
    Device<T> cbslash( const Device<T>& ) const;

    // METHOD_CALC

    Device<T> inv() const;

};

using Devi = Device<int>;
using Devf = Device<float>;
using Devd = Device<double>;
using Devu = Device<unsigned int>;
using Devc = Device<unsigned char>;

}

#include "device_src.h"

#endif
