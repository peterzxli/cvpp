#include "../device.h"

namespace cvpp
{

// Device >> Device
TPL_T Device<T>&
Device<T>::operator>>( const Device<T>& dev )
{
    this->raw_ptr = dev.raw_ptr;
    this->arr_ptr = dev.arr_ptr;

    return *this;
}

// Device = Device
TPL_T Device<T>&
Device<T>::operator=( const Device<T>& dev )
{
    if( !this->raw_ptr )
        return *this << dev;

    *arr_ptr.get() = dev.arr_ptr.get()->copy();
    return *this;
}

// Device << Device
TPL_T Device<T>&
Device<T>::operator<<( const Device<T>& dev )
{
    raw_ptr = std::make_shared< afArray >( dev.r() , dev.c() );
    *raw_ptr.get() = dev.arr_ptr.get()->copy();

    if( dev.r() == 1 )
         arr_ptr = std::make_shared< afProxy >( raw_ptr->cols( 0 , dev.c() - 1 ) );
    else arr_ptr = std::make_shared< afProxy >( raw_ptr->rows( 0 , dev.r() - 1 ) );

    return *this;
}

// Device >> afArray
TPL_T Device<T>&
Device<T>::operator>>( const afArray& afa )
{
    raw_ptr = std::make_shared< afArray >( afa.dims(0) , afa.dims(1) ,
                                           afa.template device<T>() , afDevice );

    if( afa.dims(0) == 1 )
         arr_ptr = std::make_shared< afProxy >( raw_ptr->cols( 0 , afa.dims(1) - 1 ) );
    else arr_ptr = std::make_shared< afProxy >( raw_ptr->rows( 0 , afa.dims(0) - 1 ) );

    return *this;
}

// Device = afArray
TPL_T Device<T>&
Device<T>::operator=( const afArray& afa )
{
    if( !fits( afa ) )
        initialise( afa.dims(0) , afa.dims(1) );
    arr() = afa.copy();

    return *this;
}

// Device << afArray
TPL_T Device<T>&
Device<T>::operator<<( const afArray& afa )
{
    initialise( afa.dims(0) , afa.dims(1) );
    arr() = afa.copy();

    return *this;
}

// Device >> afProxy
TPL_T Device<T>&
Device<T>::operator>>( const afProxy& afp )
{
    this->raw_ptr = std::make_shared< afArray >( afp );
    this->arr_ptr = std::make_shared< afProxy >( afp );

    return *this;
}

// Device = afProxy
TPL_T Device<T>&
Device<T>::operator=( const afProxy& afp )
{
    if( !this->raw_ptr )
        return *this << afp;

    *this->arr_ptr.get() = afp;
    return *this;
}

// Device << afProxy
TPL_T Device<T>&
Device<T>::operator<<( const afProxy& afp )
{
    raw_ptr = std::make_shared< afArray >( afp.dims(0) , afp.dims(1) );

    if( afp.dims(0) == 1 )
         arr_ptr = std::make_shared< afProxy >( raw_ptr->cols( 0 , afp.dims(1) - 1 ) );
    else arr_ptr = std::make_shared< afProxy >( raw_ptr->rows( 0 , afp.dims(0) - 1 ) );

    *raw_ptr.get() = afp;

    return *this;
}

// Device << Matrix
TPL_T Device<T>&
Device<T>::operator<<( const Matrix<T>& mat )
{
    initialise( mat.r() , mat.c() , mat.t().eig_data() );
    return *this;
}

}
