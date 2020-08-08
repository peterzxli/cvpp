#ifndef FUNCTIONS_STRING_H
#define FUNCTIONS_STRING_H

#include <cvpp/auxiliar/definitions/definitions_standard.h>

namespace cvpp
{

inline String
strn( const String& str , const int& n )
{
    if( str.substr( str.length() - 4 , 1 ) == "." )
         return str.substr( 0 , str.length() - 4 ) +
                std::to_string(n) + str.substr( str.length() - 4 , 4 );
    else return  str + std::to_string(n);
}

TPL_T inline String
toString( const T& v )
{
    return std::to_string( v );
}

TPL_T inline String
toString( const T& v , const int& p )
{
    std::ostringstream ss;
    ss << std::setw(p) << std::setfill('0') << v;
    return ss.str();
}

}

#endif
