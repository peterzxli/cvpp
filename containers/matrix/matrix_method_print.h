#include "../matrix.h"

namespace cvpp
{

// Show
TPL_T void
Matrix<T>::show() const
{
    std::cout << *eig_ptr << std::endl;
}

// Print
TPL_T void
Matrix<T>::print() const
{
    std::cout << "****************** MATRIX" << std::endl;
    std::cout << *eig_ptr << std::endl;
    std::cout << "****************** "
              << r() << " " << c() << " : " << s() << std::endl;
}

// Info
TPL_T void
Matrix<T>::info() const
{
    std::cout << "****************** MATRIX "
              << r() << " " << c() << " : " << s() << std::endl;
}

// Print String
TPL_T TPL_U void
Matrix<T>::print( const U& str ) const
{
    std::cout << "****************** MATRIX" << " ( " << str << " ) " << std::endl;
    std::cout << *eig_ptr << std::endl;
    std::cout << "****************** "
              << r() << " " << c() << " : " << s() << std::endl;
}

// Info String
TPL_T TPL_U void
Matrix<T>::info( const U& str ) const
{
    std::cout << "****************** MATRIX "
              << r() << " " << c() << " : " << s() << " ( " << str << " ) " << std::endl;
}

}
