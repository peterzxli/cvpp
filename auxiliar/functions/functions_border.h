#ifndef FUNCTIONS_BORDER_H
#define FUNCTIONS_BORDER_H

#include <cvpp/structs/struct_borders2.h>

namespace cvpp
{

Borders2f inline
LUWH( const float& l , const float& u ,
      const float& w , const float& h )
{
    Borders2f borders;
    borders.luwh( l , u , w , h );
    return borders;
}

Borders2f inline
ULHW( const float& u , const float& l ,
      const float& h , const float& w )
{
    Borders2f borders;
    borders.luwh( l , u , w , h );
    return borders;
}

Borders2f inline LUWH( const float& w , const float& h ) { return LUWH( 0 , 0 , w , h ); }
Borders2f inline ULHW( const float& h , const float& w ) { return ULHW( 0 , 0 , h , w ); }

}

#endif
