#include "../device.h"

namespace cvpp
{

// Print
TPL_T void
Device<T>::print() const
{
    char* str;
    af::toString( &str , "" , *arr_ptr );

    int i = 0;
    while( str[i] != ']' ) i++;
    i += 2;

    std::cout << "****************** DEVICE" << std::endl;
    while( i < std::strlen( str ) - 1 )
        std::cout << str[i++];
    if( r() == 1 ) std::cout << "\n";
    std::cout << "****************** "
              << r() << " " << c() << " : " << s() << std::endl;
}

// Info
TPL_T void
Device<T>::info() const
{
    std::cout << "****************** DEVICE "
              << r() << " " << c() << " : " << s() << std::endl;
}

}
