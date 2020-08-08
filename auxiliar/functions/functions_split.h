#ifndef FUNCTIONS_SPLIT_H
#define FUNCTIONS_SPLIT_H

#include <cvpp/auxiliar/definitions/definitions_standard.h>

namespace cvpp
{

inline Seq<String>&
splitString( const char* s , char delim , Seq<String>& elems )
{
    SStream ss( s ); String item;
    while( std::getline( ss , item , delim ) )
        elems.push_back( item );
    return elems;
}

inline Seq<String>
splitString( const char* s , char delim )
{
    Seq<String> elems;
    splitString( s , delim , elems );
    return elems;
}

inline Seq<float>&
splitFloat( const char* s , char delim , Seq<float>& elems )
{
    SStream ss( s ); String item;
    while( std::getline( ss , item , delim ) )
        elems.push_back( std::stof( item ) );
    return elems;
}

inline Seq<float>
splitFloat( const char* s , char delim )
{
    Seq<float> elems;
    splitFloat( s , delim , elems );
    return elems;
}

}

#endif
