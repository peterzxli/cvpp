#ifndef MACROS_BASE_H
#define MACROS_BASE_H

#include "functions/functions_color.h"
#include "functions/functions_disp.h"
#include "functions/functions_halt.h"
#include "functions/functions_nums.h"
#include "functions/functions_rand.h"
#include "functions/functions_split.h"
#include "functions/functions_string.h"

#include <cvpp/auxiliar/definitions.h>

namespace cvpp
{

// CHECK

// Token
inline int
tokenFloat( const char* arr ,
            float* vec , const char& lim = ',' )
{
    String str = arr; int len = str.length();
    int n = 0 , st = 0 , fn = 0 ;

    while( arr[ st + fn ] != lim ) fn++;
    st = st + fn + 1; fn = 0;

    while( st < len )
    {
        while( arr[ st + fn ] != lim && st + fn < len ) fn++;
        vec[n++] = std::stof( str.substr( st , fn ) );
        st = st + fn + 1; fn = 0;
    }

    return n;
}

}

#endif
