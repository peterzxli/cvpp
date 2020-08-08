#ifndef DEFINITIONS_LOOPS_H
#define DEFINITIONS_LOOPS_H

#include "definitions_eigen.h"

#define forLOOPi( n ) for( int i = 0 ; i < n ; ++i )
#define forLOOPj( n ) for( int j = 0 ; j < n ; ++j )
#define forLOOPk( n ) for( int k = 0 ; k < n ; ++k )
#define forLOOPu( n ) for( int u = 0 ; u < n ; ++u )
#define forLOOPv( n ) for( int v = 0 ; v < n ; ++v )

#define forLOOPii( s , f ) for( int i = s ; i < f ; ++i )
#define forLOOPjj( s , f ) for( int j = s ; j < f ; ++j )
#define forLOOPkk( s , f ) for( int k = s ; k < f ; ++k )

#define forLOOPiii( s , f , t ) for( int i = s ; i < f ; i += t )
#define forLOOPjjj( s , f , t ) for( int j = s ; j < f ; j += t )
#define forLOOPkkk( s , f , t ) for( int k = s ; k < f ; k += t )

#define forLOOPij( a , b ) forLOOPi( a ) forLOOPj( b )
#define forLOOPjk( a , b ) forLOOPj( a ) forLOOPk( b )
#define forLOOPijk( a , b , c ) forLOOPi( a ) forLOOPj( b ) forLOOPk( c )

#define forLOOPsm( a , b , c ) for( a = b ; a <  c ; ++a )
#define forLOOPeq( a , b , c ) for( a = b ; a <= c ; ++a )
#define forLOOP( a , b , c ) forLOOPsm( a , b , c )

#define forLOOPseq( seq ) for( int n = 0 ; n < seq.size() ; ++n )

#define forLOOPvec( vec ) for( int n = 0 ; n < vec.n() ; ++n )
#define forLOOPvecp for( int n = 0 ; n < this->n() ; ++n )

#define forLOOPmat( mat ) for( int r = 0 ; r < mat.r() ; ++r ) for( int c = 0 ; c < mat.c() ; ++c )
#define forLOOPmatp for( int r = 0 ; r < this->r() ; ++r ) for( int c = 0 ; c < this->c() ; ++c )

#define forLOOPseigout( seig ) for ( int k = 0 ; k < seig.outerSize() ; ++k )
#define forLOOPseigin( seig ) for ( typename SEIG<T>::InnerIterator it( seig , k ) ; it ; ++it )
#define forLOOPseig( seig ) forLOOPseigout( seig ) forLOOPseigin( seig )

#define forLOOPsprout( spr ) for( int k = 0 ; k < spr.o() ; ++k )
#define forLOOPsprin( spr ) for( typename SEIG<T>::InnerIterator it( spr.eig() , k ) ; it ; ++it )
#define forLOOPspr( spr ) forLOOPsprout( spr ) forLOOPsprin( spr )

#define forLOOPsprdout( spr ) for( int k = 0 ; k < spr.o() ; ++k )
#define forLOOPsprdin( spr ) for( typename SEIG<double>::InnerIterator it( spr.eig() , k ) ; it ; ++it )
#define forLOOPsprd( spr ) forLOOPsprdout( spr ) forLOOPsprdin( spr )

#define forLOOPsprfout( spr ) for( int k = 0 ; k < spr.o() ; ++k )
#define forLOOPsprfin( spr ) for( typename SEIG<float>::InnerIterator it( spr.eig() , k ) ; it ; ++it )
#define forLOOPsprf( spr ) forLOOPsprfout( spr ) forLOOPsprfin( spr )

#define forLOOPsprpout for( int k = 0 ; k < this->o() ; ++k )
#define forLOOPsprpin for( typename SEIG<T>::InnerIterator it( this->eig() , k ) ; it ; ++it )
#define forLOOPsprp forLOOPsprpout forLOOPsprpin

#endif
