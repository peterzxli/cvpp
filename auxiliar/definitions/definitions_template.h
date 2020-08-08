#ifndef DEFINITIONS_TEMPLATE_H
#define DEFINITIONS_TEMPLATE_H

#define TPL_T template< typename T >
#define TPL_U template< typename U >
#define TPL_V template< typename V >

#define TPL_AB template< typename A , typename B >

#define TPL_D template< typename D >
#define TPL_E template< typename E >

#define TPL_C template< unsigned C >
#define TPL_M template< unsigned M >

#define TPL_F template< int NR , int NC , int MR , int MC >
#define TPL_TF template< typename T , int NR , int NC , int MR , int MC >

#define TPL_B template< int NR , int NC , int BR , int BC , int MR , int MC , bool FL >
#define TPL_TB template< typename T , int NR , int NC , int BR , int BC , int MR , int MC , bool FL >

#define TPL_TU template< typename T , typename U >
#define TPL_TC template< typename T , unsigned C >
#define TPL_SB template< typename S , unsigned B >
#define TPL_DT template< typename D , typename T >
#define TPL_DM template< typename D , unsigned M >
#define TPL_TM template< typename T , unsigned M >
#define TPL_EN template< typename E , unsigned N >

#define TPL_TCU template< typename T , unsigned C , typename U >
#define TPL_TUV template< typename T , typename U , typename V >

#define TPL_DTM template< typename D , typename T , unsigned M >
#define TPL_DUM template< typename D , typename U , unsigned M >
#define TPL_EUN template< typename E , typename U , unsigned N >

#define TPL_TCSB template< typename T , unsigned C , typename S , unsigned B >

#define TPL_DTME   template< typename D , typename T , unsigned M , typename E >
#define TPL_DTMEN  template< typename D , typename T , unsigned M , typename E , unsigned N >
#define TPL_DTMEUN template< typename D , typename T , unsigned M , typename E , typename U , unsigned N >

#endif
