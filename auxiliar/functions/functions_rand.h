#ifndef FUNCTIONS_RAND_H
#define FUNCTIONS_RAND_H

#include <cvpp/auxiliar/definitions/definitions_constants.h>

#include <stdlib.h>

namespace cvpp
{

inline void randomise()
{ srand( time(NULL) ); }

inline void randomise( const int& n )
{ srand( n ); }

inline int randi( const int& st , const int& fn )
{ return st + (int)rand() % ( fn - st ); }

inline double randf( const float& st , const float& fn )
{ return st + ( fn - st ) * (float)rand() / ( RAND_MAX + 1.0 ); }

inline double randd( const double& st , const double& fn )
{ return st + ( fn - st ) * (double)rand() / ( RAND_MAX + 1.0 ); }

inline int randi( const int& fn ) { return randi(-fn,fn); }
inline float randf( const float& fn ) { return randf(-fn,fn); }
inline double randd( const double& fn ) { return randd(-fn,fn); }

inline int randi() { return randi(0,1); }
inline float randf() { return randf(0,1); }
inline double randd() { return randd(0,1); }

inline int randni( const int& m , const int& v )
{ return m + sqrt( - 2.0 * v * log( randf() ) ) * cos ( PI2 * randf() ); }

inline double randnf( const float& m , const float& v )
{ return m + sqrt( - 2.0 * v * log( randf() ) ) * cos ( PI2 * randf() ); }

inline double randnd( const double& m , const double& v )
{ return m + sqrt( - 2.0 * v * log( randd() ) ) * cos ( PI2 * randd() ); }

inline int randni() { return randni(0,1); }
inline float randnf() { return randnf(0,1); }
inline double randnd() { return randnd(0,1); }

}

#endif
