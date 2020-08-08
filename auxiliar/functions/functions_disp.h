#ifndef FUNCTIONS_DISP_H
#define FUNCTIONS_DISP_H

#include <iostream>

namespace cvpp
{

inline void disp()
{ std::cout << std::endl; }

template< class A >
inline void disp( const A& a )
{ std::cout << a << std::endl; }

template< class A , class B >
inline void disp( const A& a , const B& b )
{ std::cout << a << " : " << b << std::endl; }

template< class A , class B , class C >
inline void disp( const A& a , const B& b , const C& c )
{ std::cout << a << " : " << b << " : " << c << std::endl; }

template< class A , class B , class C , class D >
inline void disp( const A& a , const B& b , const C& c , const D& d )
{ std::cout << a << " : " << b << " : " << c << " : " << d << std::endl; }

template< class A , class B , class C , class D , class E >
inline void disp( const A& a , const B& b , const C& c , const D& d , const E& e )
{ std::cout << a << " : " << b << " : " << c << " : " << d << " : " << e << std::endl; }

template< class A , class B , class C , class D , class E , class F >
inline void disp( const A& a , const B& b , const C& c , const D& d , const E& e , const F& f )
{ std::cout << a << " : " << b << " : " << c << " : " << d << " : " << e << " : " << f << std::endl; }

template< class A , class B , class C , class D , class E , class F , class G >
inline void disp( const A& a , const B& b , const C& c , const D& d , const E& e , const F& f , const G& g )
{ std::cout << a << " : " << b << " : " << c << " : " << d << " : " << e << " : " << f << " : " << g << std::endl; }

template< class A , class B , class C , class D , class E , class F , class G , class H >
inline void disp( const A& a , const B& b , const C& c , const D& d , const E& e , const F& f , const G& g ,const H& h )
{ std::cout << a << " : " << b << " : " << c << " : " << d << " : " << e << " : " << f << " : " << g << " : " << h << std::endl; }

template< class A , class B , class C , class D , class E , class F , class G , class H , class I >
inline void disp( const A& a , const B& b , const C& c , const D& d , const E& e , const F& f , const G& g ,const H& h , const I& i )
{ std::cout << a << " : " << b << " : " << c << " : " << d << " : " << e << " : " << f << " : " << g << " : " << h << " : " << i << std::endl; }

template< class A , class B , class C , class D , class E , class F , class G , class H , class I , class J >
inline void disp( const A& a , const B& b , const C& c , const D& d , const E& e , const F& f , const G& g ,const H& h , const I& i , const J& j )
{ std::cout << a << " : " << b << " : " << c << " : " << d << " : " << e << " : " << f << " : " << g << " : " << h << " : " << i << " : " << j << std::endl; }

}

#endif
