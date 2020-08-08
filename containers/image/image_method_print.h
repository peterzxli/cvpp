#include "../image.h"

namespace cvpp
{

TPL_TC void
Image<T,C>::printCV() const
{
    std::cout << "****************** IMAGE CV\n";
    if( eig_ptr->innerStride() < C )
         std::cout << *cv_ptr << std::endl;
    else std::cout << "------------------" << std::endl;
    std::cout << "****************** "
              << r() << " " << c() << " " << d() << std::endl;
}

TPL_TC void
Image<T,C>::printEIG() const
{
    std::cout << "****************** IMAGE EIG\n";
    DataType<T> type;
    if( type.get() == 4 )
         std::cout <<  eig_ptr->template cast<unsigned>() << std::endl;
    else std::cout << *eig_ptr << std::endl;
    std::cout << "****************** "
              << r() << " " << c() << " " << d() << std::endl;
}

TPL_TC void
Image<T,C>::info() const
{
    std::cout << "****************** IMAGE "
              << r() << " " << c() << " " << d() << std::endl;
}

TPL_TC TPL_U void
Image<T,C>::printCV( const U& str ) const
{
    std::cout << "****************** IMAGE CV" << " ( " << str << " ) " << std::endl;
    if( eig_ptr->innerStride() < C )
         std::cout << *cv_ptr << std::endl;
    else std::cout << "------------------" << std::endl;
    std::cout << "****************** "
              << r() << " " << c() << " " << d() << std::endl;
}

TPL_TC TPL_U void
Image<T,C>::printEIG( const U& str ) const
{
    std::cout << "****************** IMAGE EIG" << " ( " << str << " ) " << std::endl;
    DataType<T> type;
    if( type.get() == 4 )
         std::cout <<  eig_ptr->template cast<unsigned>() << std::endl;
    else std::cout << *eig_ptr << std::endl;
    std::cout << "****************** "
              << r() << " " << c() << " " << d() << std::endl;
}

TPL_TC TPL_U void
Image<T,C>::info( const U& str ) const
{
    std::cout << "****************** IMAGE "
              << r() << " " << c() << " " << d() << " ( " << str << " ) " << std::endl;
}

}
