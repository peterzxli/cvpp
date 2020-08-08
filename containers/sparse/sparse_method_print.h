#include "../sparse.h"

namespace cvpp
{

// Print
TPL_T void
Sparse<T>::print() const
{
    std::cout << "****************** SPARSE\n";
    std::cout << *eig_ptr;
    std::cout << "****************** "
              << r() << " " << c() << " : " << nz() << "/" << s()
              << " : " << (double)nz() / (double)s() << std::endl;
}

// Info
TPL_T void
Sparse<T>::info() const
{
    std::cout << "****************** SPARSE "
              << r() << " " << c() << " : " << nz() << "/" << s()
              << " : " << (double)nz() / (double)s() << std::endl;
}

// Print String
TPL_T TPL_U void
Sparse<T>::print( const U& str ) const
{
    std::cout << "****************** SPARSE" << " ( " << str << " ) " << std::endl;
    std::cout << *eig_ptr;
    std::cout << "****************** "
              << r() << " " << c() << " : " << nz() << "/" << s()
              << " : " << (double)nz() / (double)s() << " ( " << str << " ) " << std::endl;
}

// Info String
TPL_T TPL_U void
Sparse<T>::info( const U& str ) const
{
    std::cout << "****************** SPARSE "
              << r() << " " << c() << " : " << nz() << "/" << s()
              << " : " << (double)nz() / (double)s() << " ( " << str << " ) " << std::endl;
}

}
