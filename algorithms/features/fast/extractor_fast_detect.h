#ifndef EXTRACTOR_FAST_DETECT
#define EXTRACTOR_FAST_DETECT

#include <cvpp/containers/image.h>
#include <cvpp/projects/features/src/fast-C-src/fast.h>

namespace cvpp
{

static void
makeOffsets( int pixel[] , int ns )
{
        pixel[ 0] =  0 + ns *  3;
        pixel[ 1] =  1 + ns *  3;
        pixel[ 2] =  2 + ns *  2;
        pixel[ 3] =  3 + ns *  1;
        pixel[ 4] =  3 + ns *  0;
        pixel[ 5] =  3 + ns * -1;
        pixel[ 6] =  2 + ns * -2;
        pixel[ 7] =  1 + ns * -3;
        pixel[ 8] =  0 + ns * -3;
        pixel[ 9] = -1 + ns * -3;
        pixel[10] = -2 + ns * -2;
        pixel[11] = -3 + ns * -1;
        pixel[12] = -3 + ns *  0;
        pixel[13] = -3 + ns *  1;
        pixel[14] = -2 + ns *  2;
        pixel[15] = -1 + ns *  3;
}

xy*
extractFASTdetect( const unsigned char* data , const int& nr , const int& nc , const int& ns ,
                   int thr , int* ret_num_corners )
{
    int pixel[16];
    makeOffsets( pixel , ns );

    int max_num = std::pow( 2 , 12 );
    xy* ret_corners = (xy*)malloc( sizeof(xy) * max_num );

    int x , y , num_corners = 0 ;
    for( y = 3 ; y < nr - 3 ; ++y )
        for( x = 3 ; x < nc - 3 ; ++x )
        {
            const unsigned char* p = data + y * ns + x ;

            int valp = *p + thr;
            int valm = *p - thr;

            if( p[pixel[0]] > valp )
                if( p[pixel[1]] > valp )
                    if( p[pixel[2]] > valp )
                        if( p[pixel[3]] > valp )
                            if( p[pixel[4]] > valp )
                                if( p[pixel[5]] > valp )
                                    if( p[pixel[6]] > valp )
                                        if( p[pixel[7]] > valp )
                                            if( p[pixel[8]] > valp )
                                            {}
                                            else
                                                if( p[pixel[15]] > valp )
                                                {}
                                                else
                                                    continue;
                                        else if( p[pixel[7]] < valm )
                                            if( p[pixel[14]] > valp )
                                                if( p[pixel[15]] > valp )
                                                {}
                                                else
                                                    continue;
                                            else if( p[pixel[14]] < valm )
                                                if( p[pixel[8]] < valm )
                                                    if( p[pixel[9]] < valm )
                                                        if( p[pixel[10]] < valm )
                                                            if( p[pixel[11]] < valm )
                                                                if( p[pixel[12]] < valm )
                                                                    if( p[pixel[13]] < valm )
                                                                        if( p[pixel[15]] < valm )
                                                                        {}
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            if( p[pixel[14]] > valp )
                                                if( p[pixel[15]] > valp )
                                                {}
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else if( p[pixel[6]] < valm )
                                        if( p[pixel[15]] > valp )
                                            if( p[pixel[13]] > valp )
                                                if( p[pixel[14]] > valp )
                                                {}
                                                else
                                                    continue;
                                            else if( p[pixel[13]] < valm )
                                                if( p[pixel[7]] < valm )
                                                    if( p[pixel[8]] < valm )
                                                        if( p[pixel[9]] < valm )
                                                            if( p[pixel[10]] < valm )
                                                                if( p[pixel[11]] < valm )
                                                                    if( p[pixel[12]] < valm )
                                                                        if( p[pixel[14]] < valm )
                                                                        {}
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            if( p[pixel[7]] < valm )
                                                if( p[pixel[8]] < valm )
                                                    if( p[pixel[9]] < valm )
                                                        if( p[pixel[10]] < valm )
                                                            if( p[pixel[11]] < valm )
                                                                if( p[pixel[12]] < valm )
                                                                    if( p[pixel[13]] < valm )
                                                                        if( p[pixel[14]] < valm )
                                                                        {}
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        if( p[pixel[13]] > valp )
                                            if( p[pixel[14]] > valp )
                                                if( p[pixel[15]] > valp )
                                                {}
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else if( p[pixel[13]] < valm )
                                            if( p[pixel[7]] < valm )
                                                if( p[pixel[8]] < valm )
                                                    if( p[pixel[9]] < valm )
                                                        if( p[pixel[10]] < valm )
                                                            if( p[pixel[11]] < valm )
                                                                if( p[pixel[12]] < valm )
                                                                    if( p[pixel[14]] < valm )
                                                                        if( p[pixel[15]] < valm )
                                                                        {}
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                else if( p[pixel[5]] < valm )
                                    if( p[pixel[14]] > valp )
                                        if( p[pixel[12]] > valp )
                                            if( p[pixel[13]] > valp )
                                                if( p[pixel[15]] > valp )
                                                {}
                                                else
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                            if( p[pixel[8]] > valp )
                                                                if( p[pixel[9]] > valp )
                                                                    if( p[pixel[10]] > valp )
                                                                        if( p[pixel[11]] > valp )
                                                                        {}
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                continue;
                                        else if( p[pixel[12]] < valm )
                                            if( p[pixel[6]] < valm )
                                                if( p[pixel[7]] < valm )
                                                    if( p[pixel[8]] < valm )
                                                        if( p[pixel[9]] < valm )
                                                            if( p[pixel[10]] < valm )
                                                                if( p[pixel[11]] < valm )
                                                                    if( p[pixel[13]] < valm )
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else if( p[pixel[14]] < valm )
                                        if( p[pixel[7]] < valm )
                                            if( p[pixel[8]] < valm )
                                                if( p[pixel[9]] < valm )
                                                    if( p[pixel[10]] < valm )
                                                        if( p[pixel[11]] < valm )
                                                            if( p[pixel[12]] < valm )
                                                                if( p[pixel[13]] < valm )
                                                                    if( p[pixel[6]] < valm )
                                                                    {}
                                                                    else
                                                                        if( p[pixel[15]] < valm )
                                                                        {}
                                                                        else
                                                                            continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        if( p[pixel[6]] < valm )
                                            if( p[pixel[7]] < valm )
                                                if( p[pixel[8]] < valm )
                                                    if( p[pixel[9]] < valm )
                                                        if( p[pixel[10]] < valm )
                                                            if( p[pixel[11]] < valm )
                                                                if( p[pixel[12]] < valm )
                                                                    if( p[pixel[13]] < valm )
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                else
                                    if( p[pixel[12]] > valp )
                                        if( p[pixel[13]] > valp )
                                            if( p[pixel[14]] > valp )
                                                if( p[pixel[15]] > valp )
                                                {}
                                                else
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                            if( p[pixel[8]] > valp )
                                                                if( p[pixel[9]] > valp )
                                                                    if( p[pixel[10]] > valp )
                                                                        if( p[pixel[11]] > valp )
                                                                        {}
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else if( p[pixel[12]] < valm )
                                        if( p[pixel[7]] < valm )
                                            if( p[pixel[8]] < valm )
                                                if( p[pixel[9]] < valm )
                                                    if( p[pixel[10]] < valm )
                                                        if( p[pixel[11]] < valm )
                                                            if( p[pixel[13]] < valm )
                                                                if( p[pixel[14]] < valm )
                                                                    if( p[pixel[6]] < valm )
                                                                    {}
                                                                    else
                                                                        if( p[pixel[15]] < valm )
                                                                        {}
                                                                        else
                                                                            continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                            else if( p[pixel[4]] < valm )
                                if( p[pixel[13]] > valp )
                                    if( p[pixel[11]] > valp )
                                        if( p[pixel[12]] > valp )
                                            if( p[pixel[14]] > valp )
                                                if( p[pixel[15]] > valp )
                                                {}
                                                else
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                            if( p[pixel[8]] > valp )
                                                                if( p[pixel[9]] > valp )
                                                                    if( p[pixel[10]] > valp )
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[5]] > valp )
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                            if( p[pixel[8]] > valp )
                                                                if( p[pixel[9]] > valp )
                                                                    if( p[pixel[10]] > valp )
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            continue;
                                    else if( p[pixel[11]] < valm )
                                        if( p[pixel[5]] < valm )
                                            if( p[pixel[6]] < valm )
                                                if( p[pixel[7]] < valm )
                                                    if( p[pixel[8]] < valm )
                                                        if( p[pixel[9]] < valm )
                                                            if( p[pixel[10]] < valm )
                                                                if( p[pixel[12]] < valm )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else if( p[pixel[13]] < valm )
                                    if( p[pixel[7]] < valm )
                                        if( p[pixel[8]] < valm )
                                            if( p[pixel[9]] < valm )
                                                if( p[pixel[10]] < valm )
                                                    if( p[pixel[11]] < valm )
                                                        if( p[pixel[12]] < valm )
                                                            if( p[pixel[6]] < valm )
                                                                if( p[pixel[5]] < valm )
                                                                {}
                                                                else
                                                                    if( p[pixel[14]] < valm )
                                                                    {}
                                                                    else
                                                                        continue;
                                                            else
                                                                if( p[pixel[14]] < valm )
                                                                    if( p[pixel[15]] < valm )
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else
                                    if( p[pixel[5]] < valm )
                                        if( p[pixel[6]] < valm )
                                            if( p[pixel[7]] < valm )
                                                if( p[pixel[8]] < valm )
                                                    if( p[pixel[9]] < valm )
                                                        if( p[pixel[10]] < valm )
                                                            if( p[pixel[11]] < valm )
                                                                if( p[pixel[12]] < valm )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                            else
                                if( p[pixel[11]] > valp )
                                    if( p[pixel[12]] > valp )
                                        if( p[pixel[13]] > valp )
                                            if( p[pixel[14]] > valp )
                                                if( p[pixel[15]] > valp )
                                                {}
                                                else
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                            if( p[pixel[8]] > valp )
                                                                if( p[pixel[9]] > valp )
                                                                    if( p[pixel[10]] > valp )
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[5]] > valp )
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                            if( p[pixel[8]] > valp )
                                                                if( p[pixel[9]] > valp )
                                                                    if( p[pixel[10]] > valp )
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else if( p[pixel[11]] < valm )
                                    if( p[pixel[7]] < valm )
                                        if( p[pixel[8]] < valm )
                                            if( p[pixel[9]] < valm )
                                                if( p[pixel[10]] < valm )
                                                    if( p[pixel[12]] < valm )
                                                        if( p[pixel[13]] < valm )
                                                            if( p[pixel[6]] < valm )
                                                                if( p[pixel[5]] < valm )
                                                                {}
                                                                else
                                                                    if( p[pixel[14]] < valm )
                                                                    {}
                                                                    else
                                                                        continue;
                                                            else
                                                                if( p[pixel[14]] < valm )
                                                                    if( p[pixel[15]] < valm )
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else
                                    continue;
                        else if( p[pixel[3]] < valm )
                            if( p[pixel[10]] > valp )
                                if( p[pixel[11]] > valp )
                                    if( p[pixel[12]] > valp )
                                        if( p[pixel[13]] > valp )
                                            if( p[pixel[14]] > valp )
                                                if( p[pixel[15]] > valp )
                                                {}
                                                else
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                            if( p[pixel[8]] > valp )
                                                                if( p[pixel[9]] > valp )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[5]] > valp )
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                            if( p[pixel[8]] > valp )
                                                                if( p[pixel[9]] > valp )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if( p[pixel[4]] > valp )
                                                if( p[pixel[5]] > valp )
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                            if( p[pixel[8]] > valp )
                                                                if( p[pixel[9]] > valp )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        continue;
                                else
                                    continue;
                            else if( p[pixel[10]] < valm )
                                if( p[pixel[7]] < valm )
                                    if( p[pixel[8]] < valm )
                                        if( p[pixel[9]] < valm )
                                            if( p[pixel[11]] < valm )
                                                if( p[pixel[6]] < valm )
                                                    if( p[pixel[5]] < valm )
                                                        if( p[pixel[4]] < valm )
                                                        {}
                                                        else
                                                            if( p[pixel[12]] < valm )
                                                                if( p[pixel[13]] < valm )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                    else
                                                        if( p[pixel[12]] < valm )
                                                            if( p[pixel[13]] < valm )
                                                                if( p[pixel[14]] < valm )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if( p[pixel[12]] < valm )
                                                        if( p[pixel[13]] < valm )
                                                            if( p[pixel[14]] < valm )
                                                                if( p[pixel[15]] < valm )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else
                                    continue;
                            else
                                continue;
                        else
                            if( p[pixel[10]] > valp )
                                if( p[pixel[11]] > valp )
                                    if( p[pixel[12]] > valp )
                                        if( p[pixel[13]] > valp )
                                            if( p[pixel[14]] > valp )
                                                if( p[pixel[15]] > valp )
                                                {}
                                                else
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                            if( p[pixel[8]] > valp )
                                                                if( p[pixel[9]] > valp )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[5]] > valp )
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                            if( p[pixel[8]] > valp )
                                                                if( p[pixel[9]] > valp )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if( p[pixel[4]] > valp )
                                                if( p[pixel[5]] > valp )
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                            if( p[pixel[8]] > valp )
                                                                if( p[pixel[9]] > valp )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        continue;
                                else
                                    continue;
                            else if( p[pixel[10]] < valm )
                                if( p[pixel[7]] < valm )
                                    if( p[pixel[8]] < valm )
                                        if( p[pixel[9]] < valm )
                                            if( p[pixel[11]] < valm )
                                                if( p[pixel[12]] < valm )
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[5]] < valm )
                                                            if( p[pixel[4]] < valm )
                                                            {}
                                                            else
                                                                if( p[pixel[13]] < valm )
                                                                {}
                                                                else
                                                                    continue;
                                                        else
                                                            if( p[pixel[13]] < valm )
                                                                if( p[pixel[14]] < valm )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                    else
                                                        if( p[pixel[13]] < valm )
                                                            if( p[pixel[14]] < valm )
                                                                if( p[pixel[15]] < valm )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else
                                    continue;
                            else
                                continue;
                    else if( p[pixel[2]] < valm )
                        if( p[pixel[9]] > valp )
                            if( p[pixel[10]] > valp )
                                if( p[pixel[11]] > valp )
                                    if( p[pixel[12]] > valp )
                                        if( p[pixel[13]] > valp )
                                            if( p[pixel[14]] > valp )
                                                if( p[pixel[15]] > valp )
                                                {}
                                                else
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                            if( p[pixel[8]] > valp )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[5]] > valp )
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                            if( p[pixel[8]] > valp )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if( p[pixel[4]] > valp )
                                                if( p[pixel[5]] > valp )
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                            if( p[pixel[8]] > valp )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        if( p[pixel[3]] > valp )
                                            if( p[pixel[4]] > valp )
                                                if( p[pixel[5]] > valp )
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                            if( p[pixel[8]] > valp )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                else
                                    continue;
                            else
                                continue;
                        else if( p[pixel[9]] < valm )
                            if( p[pixel[7]] < valm )
                                if( p[pixel[8]] < valm )
                                    if( p[pixel[10]] < valm )
                                        if( p[pixel[6]] < valm )
                                            if( p[pixel[5]] < valm )
                                                if( p[pixel[4]] < valm )
                                                    if( p[pixel[3]] < valm )
                                                    {}
                                                    else
                                                        if( p[pixel[11]] < valm )
                                                            if( p[pixel[12]] < valm )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if( p[pixel[11]] < valm )
                                                        if( p[pixel[12]] < valm )
                                                            if( p[pixel[13]] < valm )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[11]] < valm )
                                                    if( p[pixel[12]] < valm )
                                                        if( p[pixel[13]] < valm )
                                                            if( p[pixel[14]] < valm )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if( p[pixel[11]] < valm )
                                                if( p[pixel[12]] < valm )
                                                    if( p[pixel[13]] < valm )
                                                        if( p[pixel[14]] < valm )
                                                            if( p[pixel[15]] < valm )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        continue;
                                else
                                    continue;
                            else
                                continue;
                        else
                            continue;
                    else
                        if( p[pixel[9]] > valp )
                            if( p[pixel[10]] > valp )
                                if( p[pixel[11]] > valp )
                                    if( p[pixel[12]] > valp )
                                        if( p[pixel[13]] > valp )
                                            if( p[pixel[14]] > valp )
                                                if( p[pixel[15]] > valp )
                                                {}
                                                else
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                            if( p[pixel[8]] > valp )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[5]] > valp )
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                            if( p[pixel[8]] > valp )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if( p[pixel[4]] > valp )
                                                if( p[pixel[5]] > valp )
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                            if( p[pixel[8]] > valp )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        if( p[pixel[3]] > valp )
                                            if( p[pixel[4]] > valp )
                                                if( p[pixel[5]] > valp )
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                            if( p[pixel[8]] > valp )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                else
                                    continue;
                            else
                                continue;
                        else if( p[pixel[9]] < valm )
                            if( p[pixel[7]] < valm )
                                if( p[pixel[8]] < valm )
                                    if( p[pixel[10]] < valm )
                                        if( p[pixel[11]] < valm )
                                            if( p[pixel[6]] < valm )
                                                if( p[pixel[5]] < valm )
                                                    if( p[pixel[4]] < valm )
                                                        if( p[pixel[3]] < valm )
                                                        {}
                                                        else
                                                            if( p[pixel[12]] < valm )
                                                            {}
                                                            else
                                                                continue;
                                                    else
                                                        if( p[pixel[12]] < valm )
                                                            if( p[pixel[13]] < valm )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if( p[pixel[12]] < valm )
                                                        if( p[pixel[13]] < valm )
                                                            if( p[pixel[14]] < valm )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[12]] < valm )
                                                    if( p[pixel[13]] < valm )
                                                        if( p[pixel[14]] < valm )
                                                            if( p[pixel[15]] < valm )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else
                                    continue;
                            else
                                continue;
                        else
                            continue;
                else if( p[pixel[1]] < valm )
                    if( p[pixel[8]] > valp )
                        if( p[pixel[9]] > valp )
                            if( p[pixel[10]] > valp )
                                if( p[pixel[11]] > valp )
                                    if( p[pixel[12]] > valp )
                                        if( p[pixel[13]] > valp )
                                            if( p[pixel[14]] > valp )
                                                if( p[pixel[15]] > valp )
                                                {}
                                                else
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[5]] > valp )
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if( p[pixel[4]] > valp )
                                                if( p[pixel[5]] > valp )
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        if( p[pixel[3]] > valp )
                                            if( p[pixel[4]] > valp )
                                                if( p[pixel[5]] > valp )
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                else
                                    if( p[pixel[2]] > valp )
                                        if( p[pixel[3]] > valp )
                                            if( p[pixel[4]] > valp )
                                                if( p[pixel[5]] > valp )
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                            else
                                continue;
                        else
                            continue;
                    else if( p[pixel[8]] < valm )
                        if( p[pixel[7]] < valm )
                            if( p[pixel[9]] < valm )
                                if( p[pixel[6]] < valm )
                                    if( p[pixel[5]] < valm )
                                        if( p[pixel[4]] < valm )
                                            if( p[pixel[3]] < valm )
                                                if( p[pixel[2]] < valm )
                                                {}
                                                else
                                                    if( p[pixel[10]] < valm )
                                                        if( p[pixel[11]] < valm )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[10]] < valm )
                                                    if( p[pixel[11]] < valm )
                                                        if( p[pixel[12]] < valm )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if( p[pixel[10]] < valm )
                                                if( p[pixel[11]] < valm )
                                                    if( p[pixel[12]] < valm )
                                                        if( p[pixel[13]] < valm )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        if( p[pixel[10]] < valm )
                                            if( p[pixel[11]] < valm )
                                                if( p[pixel[12]] < valm )
                                                    if( p[pixel[13]] < valm )
                                                        if( p[pixel[14]] < valm )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                else
                                    if( p[pixel[10]] < valm )
                                        if( p[pixel[11]] < valm )
                                            if( p[pixel[12]] < valm )
                                                if( p[pixel[13]] < valm )
                                                    if( p[pixel[14]] < valm )
                                                        if( p[pixel[15]] < valm )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                            else
                                continue;
                        else
                            continue;
                    else
                        continue;
                else
                    if( p[pixel[8]] > valp )
                        if( p[pixel[9]] > valp )
                            if( p[pixel[10]] > valp )
                                if( p[pixel[11]] > valp )
                                    if( p[pixel[12]] > valp )
                                        if( p[pixel[13]] > valp )
                                            if( p[pixel[14]] > valp )
                                                if( p[pixel[15]] > valp )
                                                {}
                                                else
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[5]] > valp )
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if( p[pixel[4]] > valp )
                                                if( p[pixel[5]] > valp )
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        if( p[pixel[3]] > valp )
                                            if( p[pixel[4]] > valp )
                                                if( p[pixel[5]] > valp )
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                else
                                    if( p[pixel[2]] > valp )
                                        if( p[pixel[3]] > valp )
                                            if( p[pixel[4]] > valp )
                                                if( p[pixel[5]] > valp )
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[7]] > valp )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                            else
                                continue;
                        else
                            continue;
                    else if( p[pixel[8]] < valm )
                        if( p[pixel[7]] < valm )
                            if( p[pixel[9]] < valm )
                                if( p[pixel[10]] < valm )
                                    if( p[pixel[6]] < valm )
                                        if( p[pixel[5]] < valm )
                                            if( p[pixel[4]] < valm )
                                                if( p[pixel[3]] < valm )
                                                    if( p[pixel[2]] < valm )
                                                    {}
                                                    else
                                                        if( p[pixel[11]] < valm )
                                                        {}
                                                        else
                                                            continue;
                                                else
                                                    if( p[pixel[11]] < valm )
                                                        if( p[pixel[12]] < valm )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[11]] < valm )
                                                    if( p[pixel[12]] < valm )
                                                        if( p[pixel[13]] < valm )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if( p[pixel[11]] < valm )
                                                if( p[pixel[12]] < valm )
                                                    if( p[pixel[13]] < valm )
                                                        if( p[pixel[14]] < valm )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        if( p[pixel[11]] < valm )
                                            if( p[pixel[12]] < valm )
                                                if( p[pixel[13]] < valm )
                                                    if( p[pixel[14]] < valm )
                                                        if( p[pixel[15]] < valm )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                else
                                    continue;
                            else
                                continue;
                        else
                            continue;
                    else
                        continue;
            else if( p[pixel[0]] < valm )
                if( p[pixel[1]] > valp )
                    if( p[pixel[8]] > valp )
                        if( p[pixel[7]] > valp )
                            if( p[pixel[9]] > valp )
                                if( p[pixel[6]] > valp )
                                    if( p[pixel[5]] > valp )
                                        if( p[pixel[4]] > valp )
                                            if( p[pixel[3]] > valp )
                                                if( p[pixel[2]] > valp )
                                                {}
                                                else
                                                    if( p[pixel[10]] > valp )
                                                        if( p[pixel[11]] > valp )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[10]] > valp )
                                                    if( p[pixel[11]] > valp )
                                                        if( p[pixel[12]] > valp )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if( p[pixel[10]] > valp )
                                                if( p[pixel[11]] > valp )
                                                    if( p[pixel[12]] > valp )
                                                        if( p[pixel[13]] > valp )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        if( p[pixel[10]] > valp )
                                            if( p[pixel[11]] > valp )
                                                if( p[pixel[12]] > valp )
                                                    if( p[pixel[13]] > valp )
                                                        if( p[pixel[14]] > valp )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                else
                                    if( p[pixel[10]] > valp )
                                        if( p[pixel[11]] > valp )
                                            if( p[pixel[12]] > valp )
                                                if( p[pixel[13]] > valp )
                                                    if( p[pixel[14]] > valp )
                                                        if( p[pixel[15]] > valp )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                            else
                                continue;
                        else
                            continue;
                    else if( p[pixel[8]] < valm )
                        if( p[pixel[9]] < valm )
                            if( p[pixel[10]] < valm )
                                if( p[pixel[11]] < valm )
                                    if( p[pixel[12]] < valm )
                                        if( p[pixel[13]] < valm )
                                            if( p[pixel[14]] < valm )
                                                if( p[pixel[15]] < valm )
                                                {}
                                                else
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[5]] < valm )
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if( p[pixel[4]] < valm )
                                                if( p[pixel[5]] < valm )
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        if( p[pixel[3]] < valm )
                                            if( p[pixel[4]] < valm )
                                                if( p[pixel[5]] < valm )
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                else
                                    if( p[pixel[2]] < valm )
                                        if( p[pixel[3]] < valm )
                                            if( p[pixel[4]] < valm )
                                                if( p[pixel[5]] < valm )
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                            else
                                continue;
                        else
                            continue;
                    else
                        continue;
                else if( p[pixel[1]] < valm )
                    if( p[pixel[2]] > valp )
                        if( p[pixel[9]] > valp )
                            if( p[pixel[7]] > valp )
                                if( p[pixel[8]] > valp )
                                    if( p[pixel[10]] > valp )
                                        if( p[pixel[6]] > valp )
                                            if( p[pixel[5]] > valp )
                                                if( p[pixel[4]] > valp )
                                                    if( p[pixel[3]] > valp )
                                                    {}
                                                    else
                                                        if( p[pixel[11]] > valp )
                                                            if( p[pixel[12]] > valp )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if( p[pixel[11]] > valp )
                                                        if( p[pixel[12]] > valp )
                                                            if( p[pixel[13]] > valp )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[11]] > valp )
                                                    if( p[pixel[12]] > valp )
                                                        if( p[pixel[13]] > valp )
                                                            if( p[pixel[14]] > valp )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if( p[pixel[11]] > valp )
                                                if( p[pixel[12]] > valp )
                                                    if( p[pixel[13]] > valp )
                                                        if( p[pixel[14]] > valp )
                                                            if( p[pixel[15]] > valp )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        continue;
                                else
                                    continue;
                            else
                                continue;
                        else if( p[pixel[9]] < valm )
                            if( p[pixel[10]] < valm )
                                if( p[pixel[11]] < valm )
                                    if( p[pixel[12]] < valm )
                                        if( p[pixel[13]] < valm )
                                            if( p[pixel[14]] < valm )
                                                if( p[pixel[15]] < valm )
                                                {}
                                                else
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                            if( p[pixel[8]] < valm )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[5]] < valm )
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                            if( p[pixel[8]] < valm )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if( p[pixel[4]] < valm )
                                                if( p[pixel[5]] < valm )
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                            if( p[pixel[8]] < valm )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        if( p[pixel[3]] < valm )
                                            if( p[pixel[4]] < valm )
                                                if( p[pixel[5]] < valm )
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                            if( p[pixel[8]] < valm )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                else
                                    continue;
                            else
                                continue;
                        else
                            continue;
                    else if( p[pixel[2]] < valm )
                        if( p[pixel[3]] > valp )
                            if( p[pixel[10]] > valp )
                                if( p[pixel[7]] > valp )
                                    if( p[pixel[8]] > valp )
                                        if( p[pixel[9]] > valp )
                                            if( p[pixel[11]] > valp )
                                                if( p[pixel[6]] > valp )
                                                    if( p[pixel[5]] > valp )
                                                        if( p[pixel[4]] > valp )
                                                        {}
                                                        else
                                                            if( p[pixel[12]] > valp )
                                                                if( p[pixel[13]] > valp )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                    else
                                                        if( p[pixel[12]] > valp )
                                                            if( p[pixel[13]] > valp )
                                                                if( p[pixel[14]] > valp )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if( p[pixel[12]] > valp )
                                                        if( p[pixel[13]] > valp )
                                                            if( p[pixel[14]] > valp )
                                                                if( p[pixel[15]] > valp )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else
                                    continue;
                            else if( p[pixel[10]] < valm )
                                if( p[pixel[11]] < valm )
                                    if( p[pixel[12]] < valm )
                                        if( p[pixel[13]] < valm )
                                            if( p[pixel[14]] < valm )
                                                if( p[pixel[15]] < valm )
                                                {}
                                                else
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                            if( p[pixel[8]] < valm )
                                                                if( p[pixel[9]] < valm )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[5]] < valm )
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                            if( p[pixel[8]] < valm )
                                                                if( p[pixel[9]] < valm )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if( p[pixel[4]] < valm )
                                                if( p[pixel[5]] < valm )
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                            if( p[pixel[8]] < valm )
                                                                if( p[pixel[9]] < valm )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        continue;
                                else
                                    continue;
                            else
                                continue;
                        else if( p[pixel[3]] < valm )
                            if( p[pixel[4]] > valp )
                                if( p[pixel[13]] > valp )
                                    if( p[pixel[7]] > valp )
                                        if( p[pixel[8]] > valp )
                                            if( p[pixel[9]] > valp )
                                                if( p[pixel[10]] > valp )
                                                    if( p[pixel[11]] > valp )
                                                        if( p[pixel[12]] > valp )
                                                            if( p[pixel[6]] > valp )
                                                                if( p[pixel[5]] > valp )
                                                                {}
                                                                else
                                                                    if( p[pixel[14]] > valp )
                                                                    {}
                                                                    else
                                                                        continue;
                                                            else
                                                                if( p[pixel[14]] > valp )
                                                                    if( p[pixel[15]] > valp )
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else if( p[pixel[13]] < valm )
                                    if( p[pixel[11]] > valp )
                                        if( p[pixel[5]] > valp )
                                            if( p[pixel[6]] > valp )
                                                if( p[pixel[7]] > valp )
                                                    if( p[pixel[8]] > valp )
                                                        if( p[pixel[9]] > valp )
                                                            if( p[pixel[10]] > valp )
                                                                if( p[pixel[12]] > valp )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else if( p[pixel[11]] < valm )
                                        if( p[pixel[12]] < valm )
                                            if( p[pixel[14]] < valm )
                                                if( p[pixel[15]] < valm )
                                                {}
                                                else
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                            if( p[pixel[8]] < valm )
                                                                if( p[pixel[9]] < valm )
                                                                    if( p[pixel[10]] < valm )
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[5]] < valm )
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                            if( p[pixel[8]] < valm )
                                                                if( p[pixel[9]] < valm )
                                                                    if( p[pixel[10]] < valm )
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else
                                    if( p[pixel[5]] > valp )
                                        if( p[pixel[6]] > valp )
                                            if( p[pixel[7]] > valp )
                                                if( p[pixel[8]] > valp )
                                                    if( p[pixel[9]] > valp )
                                                        if( p[pixel[10]] > valp )
                                                            if( p[pixel[11]] > valp )
                                                                if( p[pixel[12]] > valp )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                            else if( p[pixel[4]] < valm )
                                if( p[pixel[5]] > valp )
                                    if( p[pixel[14]] > valp )
                                        if( p[pixel[7]] > valp )
                                            if( p[pixel[8]] > valp )
                                                if( p[pixel[9]] > valp )
                                                    if( p[pixel[10]] > valp )
                                                        if( p[pixel[11]] > valp )
                                                            if( p[pixel[12]] > valp )
                                                                if( p[pixel[13]] > valp )
                                                                    if( p[pixel[6]] > valp )
                                                                    {}
                                                                    else
                                                                        if( p[pixel[15]] > valp )
                                                                        {}
                                                                        else
                                                                            continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else if( p[pixel[14]] < valm )
                                        if( p[pixel[12]] > valp )
                                            if( p[pixel[6]] > valp )
                                                if( p[pixel[7]] > valp )
                                                    if( p[pixel[8]] > valp )
                                                        if( p[pixel[9]] > valp )
                                                            if( p[pixel[10]] > valp )
                                                                if( p[pixel[11]] > valp )
                                                                    if( p[pixel[13]] > valp )
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else if( p[pixel[12]] < valm )
                                            if( p[pixel[13]] < valm )
                                                if( p[pixel[15]] < valm )
                                                {}
                                                else
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                            if( p[pixel[8]] < valm )
                                                                if( p[pixel[9]] < valm )
                                                                    if( p[pixel[10]] < valm )
                                                                        if( p[pixel[11]] < valm )
                                                                        {}
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        if( p[pixel[6]] > valp )
                                            if( p[pixel[7]] > valp )
                                                if( p[pixel[8]] > valp )
                                                    if( p[pixel[9]] > valp )
                                                        if( p[pixel[10]] > valp )
                                                            if( p[pixel[11]] > valp )
                                                                if( p[pixel[12]] > valp )
                                                                    if( p[pixel[13]] > valp )
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                else if( p[pixel[5]] < valm )
                                    if( p[pixel[6]] > valp )
                                        if( p[pixel[15]] < valm )
                                            if( p[pixel[13]] > valp )
                                                if( p[pixel[7]] > valp )
                                                    if( p[pixel[8]] > valp )
                                                        if( p[pixel[9]] > valp )
                                                            if( p[pixel[10]] > valp )
                                                                if( p[pixel[11]] > valp )
                                                                    if( p[pixel[12]] > valp )
                                                                        if( p[pixel[14]] > valp )
                                                                        {}
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else if( p[pixel[13]] < valm )
                                                if( p[pixel[14]] < valm )
                                                {}
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            if( p[pixel[7]] > valp )
                                                if( p[pixel[8]] > valp )
                                                    if( p[pixel[9]] > valp )
                                                        if( p[pixel[10]] > valp )
                                                            if( p[pixel[11]] > valp )
                                                                if( p[pixel[12]] > valp )
                                                                    if( p[pixel[13]] > valp )
                                                                        if( p[pixel[14]] > valp )
                                                                        {}
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else if( p[pixel[6]] < valm )
                                        if( p[pixel[7]] > valp )
                                            if( p[pixel[14]] > valp )
                                                if( p[pixel[8]] > valp )
                                                    if( p[pixel[9]] > valp )
                                                        if( p[pixel[10]] > valp )
                                                            if( p[pixel[11]] > valp )
                                                                if( p[pixel[12]] > valp )
                                                                    if( p[pixel[13]] > valp )
                                                                        if( p[pixel[15]] > valp )
                                                                        {}
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else if( p[pixel[14]] < valm )
                                                if( p[pixel[15]] < valm )
                                                {}
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else if( p[pixel[7]] < valm )
                                            if( p[pixel[8]] < valm )
                                            {}
                                            else
                                                if( p[pixel[15]] < valm )
                                                {}
                                                else
                                                    continue;
                                        else
                                            if( p[pixel[14]] < valm )
                                                if( p[pixel[15]] < valm )
                                                {}
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        if( p[pixel[13]] > valp )
                                            if( p[pixel[7]] > valp )
                                                if( p[pixel[8]] > valp )
                                                    if( p[pixel[9]] > valp )
                                                        if( p[pixel[10]] > valp )
                                                            if( p[pixel[11]] > valp )
                                                                if( p[pixel[12]] > valp )
                                                                    if( p[pixel[14]] > valp )
                                                                        if( p[pixel[15]] > valp )
                                                                        {}
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else if( p[pixel[13]] < valm )
                                            if( p[pixel[14]] < valm )
                                                if( p[pixel[15]] < valm )
                                                {}
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                else
                                    if( p[pixel[12]] > valp )
                                        if( p[pixel[7]] > valp )
                                            if( p[pixel[8]] > valp )
                                                if( p[pixel[9]] > valp )
                                                    if( p[pixel[10]] > valp )
                                                        if( p[pixel[11]] > valp )
                                                            if( p[pixel[13]] > valp )
                                                                if( p[pixel[14]] > valp )
                                                                    if( p[pixel[6]] > valp )
                                                                    {}
                                                                    else
                                                                        if( p[pixel[15]] > valp )
                                                                        {}
                                                                        else
                                                                            continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else if( p[pixel[12]] < valm )
                                        if( p[pixel[13]] < valm )
                                            if( p[pixel[14]] < valm )
                                                if( p[pixel[15]] < valm )
                                                {}
                                                else
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                            if( p[pixel[8]] < valm )
                                                                if( p[pixel[9]] < valm )
                                                                    if( p[pixel[10]] < valm )
                                                                        if( p[pixel[11]] < valm )
                                                                        {}
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                            else
                                if( p[pixel[11]] > valp )
                                    if( p[pixel[7]] > valp )
                                        if( p[pixel[8]] > valp )
                                            if( p[pixel[9]] > valp )
                                                if( p[pixel[10]] > valp )
                                                    if( p[pixel[12]] > valp )
                                                        if( p[pixel[13]] > valp )
                                                            if( p[pixel[6]] > valp )
                                                                if( p[pixel[5]] > valp )
                                                                {}
                                                                else
                                                                    if( p[pixel[14]] > valp )
                                                                    {}
                                                                    else
                                                                        continue;
                                                            else
                                                                if( p[pixel[14]] > valp )
                                                                    if( p[pixel[15]] > valp )
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else if( p[pixel[11]] < valm )
                                    if( p[pixel[12]] < valm )
                                        if( p[pixel[13]] < valm )
                                            if( p[pixel[14]] < valm )
                                                if( p[pixel[15]] < valm )
                                                {}
                                                else
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                            if( p[pixel[8]] < valm )
                                                                if( p[pixel[9]] < valm )
                                                                    if( p[pixel[10]] < valm )
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[5]] < valm )
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                            if( p[pixel[8]] < valm )
                                                                if( p[pixel[9]] < valm )
                                                                    if( p[pixel[10]] < valm )
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else
                                    continue;
                        else
                            if( p[pixel[10]] > valp )
                                if( p[pixel[7]] > valp )
                                    if( p[pixel[8]] > valp )
                                        if( p[pixel[9]] > valp )
                                            if( p[pixel[11]] > valp )
                                                if( p[pixel[12]] > valp )
                                                    if( p[pixel[6]] > valp )
                                                        if( p[pixel[5]] > valp )
                                                            if( p[pixel[4]] > valp )
                                                            {}
                                                            else
                                                                if( p[pixel[13]] > valp )
                                                                {}
                                                                else
                                                                    continue;
                                                        else
                                                            if( p[pixel[13]] > valp )
                                                                if( p[pixel[14]] > valp )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                    else
                                                        if( p[pixel[13]] > valp )
                                                            if( p[pixel[14]] > valp )
                                                                if( p[pixel[15]] > valp )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else
                                    continue;
                            else if( p[pixel[10]] < valm )
                                if( p[pixel[11]] < valm )
                                    if( p[pixel[12]] < valm )
                                        if( p[pixel[13]] < valm )
                                            if( p[pixel[14]] < valm )
                                                if( p[pixel[15]] < valm )
                                                {}
                                                else
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                            if( p[pixel[8]] < valm )
                                                                if( p[pixel[9]] < valm )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[5]] < valm )
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                            if( p[pixel[8]] < valm )
                                                                if( p[pixel[9]] < valm )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if( p[pixel[4]] < valm )
                                                if( p[pixel[5]] < valm )
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                            if( p[pixel[8]] < valm )
                                                                if( p[pixel[9]] < valm )
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        continue;
                                else
                                    continue;
                            else
                                continue;
                    else
                        if( p[pixel[9]] > valp )
                            if( p[pixel[7]] > valp )
                                if( p[pixel[8]] > valp )
                                    if( p[pixel[10]] > valp )
                                        if( p[pixel[11]] > valp )
                                            if( p[pixel[6]] > valp )
                                                if( p[pixel[5]] > valp )
                                                    if( p[pixel[4]] > valp )
                                                        if( p[pixel[3]] > valp )
                                                        {}
                                                        else
                                                            if( p[pixel[12]] > valp )
                                                            {}
                                                            else
                                                                continue;
                                                    else
                                                        if( p[pixel[12]] > valp )
                                                            if( p[pixel[13]] > valp )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if( p[pixel[12]] > valp )
                                                        if( p[pixel[13]] > valp )
                                                            if( p[pixel[14]] > valp )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[12]] > valp )
                                                    if( p[pixel[13]] > valp )
                                                        if( p[pixel[14]] > valp )
                                                            if( p[pixel[15]] > valp )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else
                                    continue;
                            else
                                continue;
                        else if( p[pixel[9]] < valm )
                            if( p[pixel[10]] < valm )
                                if( p[pixel[11]] < valm )
                                    if( p[pixel[12]] < valm )
                                        if( p[pixel[13]] < valm )
                                            if( p[pixel[14]] < valm )
                                                if( p[pixel[15]] < valm )
                                                {}
                                                else
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                            if( p[pixel[8]] < valm )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[5]] < valm )
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                            if( p[pixel[8]] < valm )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if( p[pixel[4]] < valm )
                                                if( p[pixel[5]] < valm )
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                            if( p[pixel[8]] < valm )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        if( p[pixel[3]] < valm )
                                            if( p[pixel[4]] < valm )
                                                if( p[pixel[5]] < valm )
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                            if( p[pixel[8]] < valm )
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                else
                                    continue;
                            else
                                continue;
                        else
                            continue;
                else
                    if( p[pixel[8]] > valp )
                        if( p[pixel[7]] > valp )
                            if( p[pixel[9]] > valp )
                                if( p[pixel[10]] > valp )
                                    if( p[pixel[6]] > valp )
                                        if( p[pixel[5]] > valp )
                                            if( p[pixel[4]] > valp )
                                                if( p[pixel[3]] > valp )
                                                    if( p[pixel[2]] > valp )
                                                    {}
                                                    else
                                                        if( p[pixel[11]] > valp )
                                                        {}
                                                        else
                                                            continue;
                                                else
                                                    if( p[pixel[11]] > valp )
                                                        if( p[pixel[12]] > valp )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[11]] > valp )
                                                    if( p[pixel[12]] > valp )
                                                        if( p[pixel[13]] > valp )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if( p[pixel[11]] > valp )
                                                if( p[pixel[12]] > valp )
                                                    if( p[pixel[13]] > valp )
                                                        if( p[pixel[14]] > valp )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        if( p[pixel[11]] > valp )
                                            if( p[pixel[12]] > valp )
                                                if( p[pixel[13]] > valp )
                                                    if( p[pixel[14]] > valp )
                                                        if( p[pixel[15]] > valp )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                else
                                    continue;
                            else
                                continue;
                        else
                            continue;
                    else if( p[pixel[8]] < valm )
                        if( p[pixel[9]] < valm )
                            if( p[pixel[10]] < valm )
                                if( p[pixel[11]] < valm )
                                    if( p[pixel[12]] < valm )
                                        if( p[pixel[13]] < valm )
                                            if( p[pixel[14]] < valm )
                                                if( p[pixel[15]] < valm )
                                                {}
                                                else
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[5]] < valm )
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if( p[pixel[4]] < valm )
                                                if( p[pixel[5]] < valm )
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        if( p[pixel[3]] < valm )
                                            if( p[pixel[4]] < valm )
                                                if( p[pixel[5]] < valm )
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                else
                                    if( p[pixel[2]] < valm )
                                        if( p[pixel[3]] < valm )
                                            if( p[pixel[4]] < valm )
                                                if( p[pixel[5]] < valm )
                                                    if( p[pixel[6]] < valm )
                                                        if( p[pixel[7]] < valm )
                                                        {}
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                            else
                                continue;
                        else
                            continue;
                    else
                        continue;
            else
                if( p[pixel[7]] > valp )
                    if( p[pixel[8]] > valp )
                        if( p[pixel[9]] > valp )
                            if( p[pixel[6]] > valp )
                                if( p[pixel[5]] > valp )
                                    if( p[pixel[4]] > valp )
                                        if( p[pixel[3]] > valp )
                                            if( p[pixel[2]] > valp )
                                                if( p[pixel[1]] > valp )
                                                {}
                                                else
                                                    if( p[pixel[10]] > valp )
                                                    {}
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[10]] > valp )
                                                    if( p[pixel[11]] > valp )
                                                    {}
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if( p[pixel[10]] > valp )
                                                if( p[pixel[11]] > valp )
                                                    if( p[pixel[12]] > valp )
                                                    {}
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        if( p[pixel[10]] > valp )
                                            if( p[pixel[11]] > valp )
                                                if( p[pixel[12]] > valp )
                                                    if( p[pixel[13]] > valp )
                                                    {}
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                else
                                    if( p[pixel[10]] > valp )
                                        if( p[pixel[11]] > valp )
                                            if( p[pixel[12]] > valp )
                                                if( p[pixel[13]] > valp )
                                                    if( p[pixel[14]] > valp )
                                                    {}
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                            else
                                if( p[pixel[10]] > valp )
                                    if( p[pixel[11]] > valp )
                                        if( p[pixel[12]] > valp )
                                            if( p[pixel[13]] > valp )
                                                if( p[pixel[14]] > valp )
                                                    if( p[pixel[15]] > valp )
                                                    {}
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else
                                    continue;
                        else
                            continue;
                    else
                        continue;
                else if( p[pixel[7]] < valm )
                    if( p[pixel[8]] < valm )
                        if( p[pixel[9]] < valm )
                            if( p[pixel[6]] < valm )
                                if( p[pixel[5]] < valm )
                                    if( p[pixel[4]] < valm )
                                        if( p[pixel[3]] < valm )
                                            if( p[pixel[2]] < valm )
                                                if( p[pixel[1]] < valm )
                                                {}
                                                else
                                                    if( p[pixel[10]] < valm )
                                                    {}
                                                    else
                                                        continue;
                                            else
                                                if( p[pixel[10]] < valm )
                                                    if( p[pixel[11]] < valm )
                                                    {}
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if( p[pixel[10]] < valm )
                                                if( p[pixel[11]] < valm )
                                                    if( p[pixel[12]] < valm )
                                                    {}
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        if( p[pixel[10]] < valm )
                                            if( p[pixel[11]] < valm )
                                                if( p[pixel[12]] < valm )
                                                    if( p[pixel[13]] < valm )
                                                    {}
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                else
                                    if( p[pixel[10]] < valm )
                                        if( p[pixel[11]] < valm )
                                            if( p[pixel[12]] < valm )
                                                if( p[pixel[13]] < valm )
                                                    if( p[pixel[14]] < valm )
                                                    {}
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                            else
                                if( p[pixel[10]] < valm )
                                    if( p[pixel[11]] < valm )
                                        if( p[pixel[12]] < valm )
                                            if( p[pixel[13]] < valm )
                                                if( p[pixel[14]] < valm )
                                                    if( p[pixel[15]] < valm )
                                                    {}
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else
                                    continue;
                        else
                            continue;
                    else
                        continue;
                else
                    continue;

            if( num_corners == max_num )
            {
                max_num *= 2;
                ret_corners = (xy*)realloc( ret_corners , sizeof(xy) * max_num );
            }

            ret_corners[num_corners].x = x;
            ret_corners[num_corners].y = y;
            num_corners++;

        }

    *ret_num_corners = num_corners;
    return ret_corners;
}

}

#endif
