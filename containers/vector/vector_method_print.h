#include "../vector.h"

namespace cvpp
{

TPL_DTM inline void
Vector<D,T,M>::print() const
{
    std::cout << "****************** VECTOR\n";
    std::cout << mat_ptr->eig() << std::endl;
    std::cout << "****************** "
              << n() << " " << d() << " : " << s() << " (" << c() << ")" << std::endl;
}

TPL_DTM inline void
Vector<D,T,M>::info() const
{
    std::cout << "****************** VECTOR "
              << n() << " " << d() << " : " << s() << " (" << c() << ")" << std::endl;
}

TPL_DTM inline void
Vector<D,T,M>::print( const String& str ) const
{
    std::cout << "****************** VECTOR " << " ( " << str << " ) " << std::endl;
    std::cout << mat_ptr->eig() << std::endl;
    std::cout << "****************** "
              << n() << " " << d() << " : " << s() << " (" << c() << ")" << std::endl;
}

TPL_DTM inline void
Vector<D,T,M>::info( const String& str ) const
{
    std::cout << "****************** VECTOR "
              << n() << " " << d() << " : " << s() << "/" << c() << " ( " << str << " ) " << std::endl;
}

}
