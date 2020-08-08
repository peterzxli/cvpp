#ifndef EXTRACTOR_FAST_SCORE
#define EXTRACTOR_FAST_SCORE

#include <cvpp/containers/image.h>
#include <cvpp/algorithms/features/fast/extractor_fast_detect.h>

namespace cvpp
{

int
extractFASTscore( const byte* p , const int pixel[] , int thr_start )
{
    int thr_min = thr_start , thr_max = 255;
    int thr = ( thr_max + thr_min ) / 2;

    for(;;)
    {
        int cbp = *p + thr;
        int cbn = *p - thr;

        if( p[pixel[0]] > cbp )
            if( p[pixel[1]] > cbp )
                if( p[pixel[2]] > cbp )
                    if( p[pixel[3]] > cbp )
                        if( p[pixel[4]] > cbp )
                            if( p[pixel[5]] > cbp )
                                if( p[pixel[6]] > cbp )
                                    if( p[pixel[7]] > cbp )
                                        if( p[pixel[8]] > cbp )
                                            goto is_a_corner;
                                        else
                                            if( p[pixel[15]] > cbp )
                                                goto is_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else if( p[pixel[7]] < cbn )
                                        if( p[pixel[14]] > cbp )
                                            if( p[pixel[15]] > cbp )
                                                goto is_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else if( p[pixel[14]] < cbn )
                                            if( p[pixel[8]] < cbn )
                                                if( p[pixel[9]] < cbn )
                                                    if( p[pixel[10]] < cbn )
                                                        if( p[pixel[11]] < cbn )
                                                            if( p[pixel[12]] < cbn )
                                                                if( p[pixel[13]] < cbn )
                                                                    if( p[pixel[15]] < cbn )
                                                                        goto is_a_corner;
                                                                    else
                                                                        goto is_not_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        if( p[pixel[14]] > cbp )
                                            if( p[pixel[15]] > cbp )
                                                goto is_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else if( p[pixel[6]] < cbn )
                                    if( p[pixel[15]] > cbp )
                                        if( p[pixel[13]] > cbp )
                                            if( p[pixel[14]] > cbp )
                                                goto is_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else if( p[pixel[13]] < cbn )
                                            if( p[pixel[7]] < cbn )
                                                if( p[pixel[8]] < cbn )
                                                    if( p[pixel[9]] < cbn )
                                                        if( p[pixel[10]] < cbn )
                                                            if( p[pixel[11]] < cbn )
                                                                if( p[pixel[12]] < cbn )
                                                                    if( p[pixel[14]] < cbn )
                                                                        goto is_a_corner;
                                                                    else
                                                                        goto is_not_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        if( p[pixel[7]] < cbn )
                                            if( p[pixel[8]] < cbn )
                                                if( p[pixel[9]] < cbn )
                                                    if( p[pixel[10]] < cbn )
                                                        if( p[pixel[11]] < cbn )
                                                            if( p[pixel[12]] < cbn )
                                                                if( p[pixel[13]] < cbn )
                                                                    if( p[pixel[14]] < cbn )
                                                                        goto is_a_corner;
                                                                    else
                                                                        goto is_not_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if( p[pixel[13]] > cbp )
                                        if( p[pixel[14]] > cbp )
                                            if( p[pixel[15]] > cbp )
                                                goto is_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else if( p[pixel[13]] < cbn )
                                        if( p[pixel[7]] < cbn )
                                            if( p[pixel[8]] < cbn )
                                                if( p[pixel[9]] < cbn )
                                                    if( p[pixel[10]] < cbn )
                                                        if( p[pixel[11]] < cbn )
                                                            if( p[pixel[12]] < cbn )
                                                                if( p[pixel[14]] < cbn )
                                                                    if( p[pixel[15]] < cbn )
                                                                        goto is_a_corner;
                                                                    else
                                                                        goto is_not_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else if( p[pixel[5]] < cbn )
                                if( p[pixel[14]] > cbp )
                                    if( p[pixel[12]] > cbp )
                                        if( p[pixel[13]] > cbp )
                                            if( p[pixel[15]] > cbp )
                                                goto is_a_corner;
                                            else
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        if( p[pixel[8]] > cbp )
                                                            if( p[pixel[9]] > cbp )
                                                                if( p[pixel[10]] > cbp )
                                                                    if( p[pixel[11]] > cbp )
                                                                        goto is_a_corner;
                                                                    else
                                                                        goto is_not_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else if( p[pixel[12]] < cbn )
                                        if( p[pixel[6]] < cbn )
                                            if( p[pixel[7]] < cbn )
                                                if( p[pixel[8]] < cbn )
                                                    if( p[pixel[9]] < cbn )
                                                        if( p[pixel[10]] < cbn )
                                                            if( p[pixel[11]] < cbn )
                                                                if( p[pixel[13]] < cbn )
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else if( p[pixel[14]] < cbn )
                                    if( p[pixel[7]] < cbn )
                                        if( p[pixel[8]] < cbn )
                                            if( p[pixel[9]] < cbn )
                                                if( p[pixel[10]] < cbn )
                                                    if( p[pixel[11]] < cbn )
                                                        if( p[pixel[12]] < cbn )
                                                            if( p[pixel[13]] < cbn )
                                                                if( p[pixel[6]] < cbn )
                                                                    goto is_a_corner;
                                                                else
                                                                    if( p[pixel[15]] < cbn )
                                                                        goto is_a_corner;
                                                                    else
                                                                        goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    if( p[pixel[6]] < cbn )
                                        if( p[pixel[7]] < cbn )
                                            if( p[pixel[8]] < cbn )
                                                if( p[pixel[9]] < cbn )
                                                    if( p[pixel[10]] < cbn )
                                                        if( p[pixel[11]] < cbn )
                                                            if( p[pixel[12]] < cbn )
                                                                if( p[pixel[13]] < cbn )
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                if( p[pixel[12]] > cbp )
                                    if( p[pixel[13]] > cbp )
                                        if( p[pixel[14]] > cbp )
                                            if( p[pixel[15]] > cbp )
                                                goto is_a_corner;
                                            else
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        if( p[pixel[8]] > cbp )
                                                            if( p[pixel[9]] > cbp )
                                                                if( p[pixel[10]] > cbp )
                                                                    if( p[pixel[11]] > cbp )
                                                                        goto is_a_corner;
                                                                    else
                                                                        goto is_not_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else if( p[pixel[12]] < cbn )
                                    if( p[pixel[7]] < cbn )
                                        if( p[pixel[8]] < cbn )
                                            if( p[pixel[9]] < cbn )
                                                if( p[pixel[10]] < cbn )
                                                    if( p[pixel[11]] < cbn )
                                                        if( p[pixel[13]] < cbn )
                                                            if( p[pixel[14]] < cbn )
                                                                if( p[pixel[6]] < cbn )
                                                                    goto is_a_corner;
                                                                else
                                                                    if( p[pixel[15]] < cbn )
                                                                        goto is_a_corner;
                                                                    else
                                                                        goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                        else if( p[pixel[4]] < cbn )
                            if( p[pixel[13]] > cbp )
                                if( p[pixel[11]] > cbp )
                                    if( p[pixel[12]] > cbp )
                                        if( p[pixel[14]] > cbp )
                                            if( p[pixel[15]] > cbp )
                                                goto is_a_corner;
                                            else
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        if( p[pixel[8]] > cbp )
                                                            if( p[pixel[9]] > cbp )
                                                                if( p[pixel[10]] > cbp )
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[5]] > cbp )
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        if( p[pixel[8]] > cbp )
                                                            if( p[pixel[9]] > cbp )
                                                                if( p[pixel[10]] > cbp )
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else if( p[pixel[11]] < cbn )
                                    if( p[pixel[5]] < cbn )
                                        if( p[pixel[6]] < cbn )
                                            if( p[pixel[7]] < cbn )
                                                if( p[pixel[8]] < cbn )
                                                    if( p[pixel[9]] < cbn )
                                                        if( p[pixel[10]] < cbn )
                                                            if( p[pixel[12]] < cbn )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else if( p[pixel[13]] < cbn )
                                if( p[pixel[7]] < cbn )
                                    if( p[pixel[8]] < cbn )
                                        if( p[pixel[9]] < cbn )
                                            if( p[pixel[10]] < cbn )
                                                if( p[pixel[11]] < cbn )
                                                    if( p[pixel[12]] < cbn )
                                                        if( p[pixel[6]] < cbn )
                                                            if( p[pixel[5]] < cbn )
                                                                goto is_a_corner;
                                                            else
                                                                if( p[pixel[14]] < cbn )
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                        else
                                                            if( p[pixel[14]] < cbn )
                                                                if( p[pixel[15]] < cbn )
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                if( p[pixel[5]] < cbn )
                                    if( p[pixel[6]] < cbn )
                                        if( p[pixel[7]] < cbn )
                                            if( p[pixel[8]] < cbn )
                                                if( p[pixel[9]] < cbn )
                                                    if( p[pixel[10]] < cbn )
                                                        if( p[pixel[11]] < cbn )
                                                            if( p[pixel[12]] < cbn )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                        else
                            if( p[pixel[11]] > cbp )
                                if( p[pixel[12]] > cbp )
                                    if( p[pixel[13]] > cbp )
                                        if( p[pixel[14]] > cbp )
                                            if( p[pixel[15]] > cbp )
                                                goto is_a_corner;
                                            else
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        if( p[pixel[8]] > cbp )
                                                            if( p[pixel[9]] > cbp )
                                                                if( p[pixel[10]] > cbp )
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[5]] > cbp )
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        if( p[pixel[8]] > cbp )
                                                            if( p[pixel[9]] > cbp )
                                                                if( p[pixel[10]] > cbp )
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else if( p[pixel[11]] < cbn )
                                if( p[pixel[7]] < cbn )
                                    if( p[pixel[8]] < cbn )
                                        if( p[pixel[9]] < cbn )
                                            if( p[pixel[10]] < cbn )
                                                if( p[pixel[12]] < cbn )
                                                    if( p[pixel[13]] < cbn )
                                                        if( p[pixel[6]] < cbn )
                                                            if( p[pixel[5]] < cbn )
                                                                goto is_a_corner;
                                                            else
                                                                if( p[pixel[14]] < cbn )
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                        else
                                                            if( p[pixel[14]] < cbn )
                                                                if( p[pixel[15]] < cbn )
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                    else if( p[pixel[3]] < cbn )
                        if( p[pixel[10]] > cbp )
                            if( p[pixel[11]] > cbp )
                                if( p[pixel[12]] > cbp )
                                    if( p[pixel[13]] > cbp )
                                        if( p[pixel[14]] > cbp )
                                            if( p[pixel[15]] > cbp )
                                                goto is_a_corner;
                                            else
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        if( p[pixel[8]] > cbp )
                                                            if( p[pixel[9]] > cbp )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[5]] > cbp )
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        if( p[pixel[8]] > cbp )
                                                            if( p[pixel[9]] > cbp )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if( p[pixel[4]] > cbp )
                                            if( p[pixel[5]] > cbp )
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        if( p[pixel[8]] > cbp )
                                                            if( p[pixel[9]] > cbp )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else if( p[pixel[10]] < cbn )
                            if( p[pixel[7]] < cbn )
                                if( p[pixel[8]] < cbn )
                                    if( p[pixel[9]] < cbn )
                                        if( p[pixel[11]] < cbn )
                                            if( p[pixel[6]] < cbn )
                                                if( p[pixel[5]] < cbn )
                                                    if( p[pixel[4]] < cbn )
                                                        goto is_a_corner;
                                                    else
                                                        if( p[pixel[12]] < cbn )
                                                            if( p[pixel[13]] < cbn )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                else
                                                    if( p[pixel[12]] < cbn )
                                                        if( p[pixel[13]] < cbn )
                                                            if( p[pixel[14]] < cbn )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if( p[pixel[12]] < cbn )
                                                    if( p[pixel[13]] < cbn )
                                                        if( p[pixel[14]] < cbn )
                                                            if( p[pixel[15]] < cbn )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else
                        if( p[pixel[10]] > cbp )
                            if( p[pixel[11]] > cbp )
                                if( p[pixel[12]] > cbp )
                                    if( p[pixel[13]] > cbp )
                                        if( p[pixel[14]] > cbp )
                                            if( p[pixel[15]] > cbp )
                                                goto is_a_corner;
                                            else
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        if( p[pixel[8]] > cbp )
                                                            if( p[pixel[9]] > cbp )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[5]] > cbp )
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        if( p[pixel[8]] > cbp )
                                                            if( p[pixel[9]] > cbp )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if( p[pixel[4]] > cbp )
                                            if( p[pixel[5]] > cbp )
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        if( p[pixel[8]] > cbp )
                                                            if( p[pixel[9]] > cbp )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else if( p[pixel[10]] < cbn )
                            if( p[pixel[7]] < cbn )
                                if( p[pixel[8]] < cbn )
                                    if( p[pixel[9]] < cbn )
                                        if( p[pixel[11]] < cbn )
                                            if( p[pixel[12]] < cbn )
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[5]] < cbn )
                                                        if( p[pixel[4]] < cbn )
                                                            goto is_a_corner;
                                                        else
                                                            if( p[pixel[13]] < cbn )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                    else
                                                        if( p[pixel[13]] < cbn )
                                                            if( p[pixel[14]] < cbn )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                else
                                                    if( p[pixel[13]] < cbn )
                                                        if( p[pixel[14]] < cbn )
                                                            if( p[pixel[15]] < cbn )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                else if( p[pixel[2]] < cbn )
                    if( p[pixel[9]] > cbp )
                        if( p[pixel[10]] > cbp )
                            if( p[pixel[11]] > cbp )
                                if( p[pixel[12]] > cbp )
                                    if( p[pixel[13]] > cbp )
                                        if( p[pixel[14]] > cbp )
                                            if( p[pixel[15]] > cbp )
                                                goto is_a_corner;
                                            else
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        if( p[pixel[8]] > cbp )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[5]] > cbp )
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        if( p[pixel[8]] > cbp )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if( p[pixel[4]] > cbp )
                                            if( p[pixel[5]] > cbp )
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        if( p[pixel[8]] > cbp )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if( p[pixel[3]] > cbp )
                                        if( p[pixel[4]] > cbp )
                                            if( p[pixel[5]] > cbp )
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        if( p[pixel[8]] > cbp )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else if( p[pixel[9]] < cbn )
                        if( p[pixel[7]] < cbn )
                            if( p[pixel[8]] < cbn )
                                if( p[pixel[10]] < cbn )
                                    if( p[pixel[6]] < cbn )
                                        if( p[pixel[5]] < cbn )
                                            if( p[pixel[4]] < cbn )
                                                if( p[pixel[3]] < cbn )
                                                    goto is_a_corner;
                                                else
                                                    if( p[pixel[11]] < cbn )
                                                        if( p[pixel[12]] < cbn )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if( p[pixel[11]] < cbn )
                                                    if( p[pixel[12]] < cbn )
                                                        if( p[pixel[13]] < cbn )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[11]] < cbn )
                                                if( p[pixel[12]] < cbn )
                                                    if( p[pixel[13]] < cbn )
                                                        if( p[pixel[14]] < cbn )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if( p[pixel[11]] < cbn )
                                            if( p[pixel[12]] < cbn )
                                                if( p[pixel[13]] < cbn )
                                                    if( p[pixel[14]] < cbn )
                                                        if( p[pixel[15]] < cbn )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                else
                    if( p[pixel[9]] > cbp )
                        if( p[pixel[10]] > cbp )
                            if( p[pixel[11]] > cbp )
                                if( p[pixel[12]] > cbp )
                                    if( p[pixel[13]] > cbp )
                                        if( p[pixel[14]] > cbp )
                                            if( p[pixel[15]] > cbp )
                                                goto is_a_corner;
                                            else
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        if( p[pixel[8]] > cbp )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[5]] > cbp )
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        if( p[pixel[8]] > cbp )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if( p[pixel[4]] > cbp )
                                            if( p[pixel[5]] > cbp )
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        if( p[pixel[8]] > cbp )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if( p[pixel[3]] > cbp )
                                        if( p[pixel[4]] > cbp )
                                            if( p[pixel[5]] > cbp )
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        if( p[pixel[8]] > cbp )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else if( p[pixel[9]] < cbn )
                        if( p[pixel[7]] < cbn )
                            if( p[pixel[8]] < cbn )
                                if( p[pixel[10]] < cbn )
                                    if( p[pixel[11]] < cbn )
                                        if( p[pixel[6]] < cbn )
                                            if( p[pixel[5]] < cbn )
                                                if( p[pixel[4]] < cbn )
                                                    if( p[pixel[3]] < cbn )
                                                        goto is_a_corner;
                                                    else
                                                        if( p[pixel[12]] < cbn )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                else
                                                    if( p[pixel[12]] < cbn )
                                                        if( p[pixel[13]] < cbn )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if( p[pixel[12]] < cbn )
                                                    if( p[pixel[13]] < cbn )
                                                        if( p[pixel[14]] < cbn )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[12]] < cbn )
                                                if( p[pixel[13]] < cbn )
                                                    if( p[pixel[14]] < cbn )
                                                        if( p[pixel[15]] < cbn )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
            else if( p[pixel[1]] < cbn )
                if( p[pixel[8]] > cbp )
                    if( p[pixel[9]] > cbp )
                        if( p[pixel[10]] > cbp )
                            if( p[pixel[11]] > cbp )
                                if( p[pixel[12]] > cbp )
                                    if( p[pixel[13]] > cbp )
                                        if( p[pixel[14]] > cbp )
                                            if( p[pixel[15]] > cbp )
                                                goto is_a_corner;
                                            else
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[5]] > cbp )
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if( p[pixel[4]] > cbp )
                                            if( p[pixel[5]] > cbp )
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if( p[pixel[3]] > cbp )
                                        if( p[pixel[4]] > cbp )
                                            if( p[pixel[5]] > cbp )
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                if( p[pixel[2]] > cbp )
                                    if( p[pixel[3]] > cbp )
                                        if( p[pixel[4]] > cbp )
                                            if( p[pixel[5]] > cbp )
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                else if( p[pixel[8]] < cbn )
                    if( p[pixel[7]] < cbn )
                        if( p[pixel[9]] < cbn )
                            if( p[pixel[6]] < cbn )
                                if( p[pixel[5]] < cbn )
                                    if( p[pixel[4]] < cbn )
                                        if( p[pixel[3]] < cbn )
                                            if( p[pixel[2]] < cbn )
                                                goto is_a_corner;
                                            else
                                                if( p[pixel[10]] < cbn )
                                                    if( p[pixel[11]] < cbn )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[10]] < cbn )
                                                if( p[pixel[11]] < cbn )
                                                    if( p[pixel[12]] < cbn )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if( p[pixel[10]] < cbn )
                                            if( p[pixel[11]] < cbn )
                                                if( p[pixel[12]] < cbn )
                                                    if( p[pixel[13]] < cbn )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if( p[pixel[10]] < cbn )
                                        if( p[pixel[11]] < cbn )
                                            if( p[pixel[12]] < cbn )
                                                if( p[pixel[13]] < cbn )
                                                    if( p[pixel[14]] < cbn )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                if( p[pixel[10]] < cbn )
                                    if( p[pixel[11]] < cbn )
                                        if( p[pixel[12]] < cbn )
                                            if( p[pixel[13]] < cbn )
                                                if( p[pixel[14]] < cbn )
                                                    if( p[pixel[15]] < cbn )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                else
                    goto is_not_a_corner;
            else
                if( p[pixel[8]] > cbp )
                    if( p[pixel[9]] > cbp )
                        if( p[pixel[10]] > cbp )
                            if( p[pixel[11]] > cbp )
                                if( p[pixel[12]] > cbp )
                                    if( p[pixel[13]] > cbp )
                                        if( p[pixel[14]] > cbp )
                                            if( p[pixel[15]] > cbp )
                                                goto is_a_corner;
                                            else
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[5]] > cbp )
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if( p[pixel[4]] > cbp )
                                            if( p[pixel[5]] > cbp )
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if( p[pixel[3]] > cbp )
                                        if( p[pixel[4]] > cbp )
                                            if( p[pixel[5]] > cbp )
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                if( p[pixel[2]] > cbp )
                                    if( p[pixel[3]] > cbp )
                                        if( p[pixel[4]] > cbp )
                                            if( p[pixel[5]] > cbp )
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[7]] > cbp )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                else if( p[pixel[8]] < cbn )
                    if( p[pixel[7]] < cbn )
                        if( p[pixel[9]] < cbn )
                            if( p[pixel[10]] < cbn )
                                if( p[pixel[6]] < cbn )
                                    if( p[pixel[5]] < cbn )
                                        if( p[pixel[4]] < cbn )
                                            if( p[pixel[3]] < cbn )
                                                if( p[pixel[2]] < cbn )
                                                    goto is_a_corner;
                                                else
                                                    if( p[pixel[11]] < cbn )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if( p[pixel[11]] < cbn )
                                                    if( p[pixel[12]] < cbn )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[11]] < cbn )
                                                if( p[pixel[12]] < cbn )
                                                    if( p[pixel[13]] < cbn )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if( p[pixel[11]] < cbn )
                                            if( p[pixel[12]] < cbn )
                                                if( p[pixel[13]] < cbn )
                                                    if( p[pixel[14]] < cbn )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if( p[pixel[11]] < cbn )
                                        if( p[pixel[12]] < cbn )
                                            if( p[pixel[13]] < cbn )
                                                if( p[pixel[14]] < cbn )
                                                    if( p[pixel[15]] < cbn )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                else
                    goto is_not_a_corner;
        else if( p[pixel[0]] < cbn )
            if( p[pixel[1]] > cbp )
                if( p[pixel[8]] > cbp )
                    if( p[pixel[7]] > cbp )
                        if( p[pixel[9]] > cbp )
                            if( p[pixel[6]] > cbp )
                                if( p[pixel[5]] > cbp )
                                    if( p[pixel[4]] > cbp )
                                        if( p[pixel[3]] > cbp )
                                            if( p[pixel[2]] > cbp )
                                                goto is_a_corner;
                                            else
                                                if( p[pixel[10]] > cbp )
                                                    if( p[pixel[11]] > cbp )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[10]] > cbp )
                                                if( p[pixel[11]] > cbp )
                                                    if( p[pixel[12]] > cbp )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if( p[pixel[10]] > cbp )
                                            if( p[pixel[11]] > cbp )
                                                if( p[pixel[12]] > cbp )
                                                    if( p[pixel[13]] > cbp )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if( p[pixel[10]] > cbp )
                                        if( p[pixel[11]] > cbp )
                                            if( p[pixel[12]] > cbp )
                                                if( p[pixel[13]] > cbp )
                                                    if( p[pixel[14]] > cbp )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                if( p[pixel[10]] > cbp )
                                    if( p[pixel[11]] > cbp )
                                        if( p[pixel[12]] > cbp )
                                            if( p[pixel[13]] > cbp )
                                                if( p[pixel[14]] > cbp )
                                                    if( p[pixel[15]] > cbp )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                else if( p[pixel[8]] < cbn )
                    if( p[pixel[9]] < cbn )
                        if( p[pixel[10]] < cbn )
                            if( p[pixel[11]] < cbn )
                                if( p[pixel[12]] < cbn )
                                    if( p[pixel[13]] < cbn )
                                        if( p[pixel[14]] < cbn )
                                            if( p[pixel[15]] < cbn )
                                                goto is_a_corner;
                                            else
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[5]] < cbn )
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if( p[pixel[4]] < cbn )
                                            if( p[pixel[5]] < cbn )
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if( p[pixel[3]] < cbn )
                                        if( p[pixel[4]] < cbn )
                                            if( p[pixel[5]] < cbn )
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                if( p[pixel[2]] < cbn )
                                    if( p[pixel[3]] < cbn )
                                        if( p[pixel[4]] < cbn )
                                            if( p[pixel[5]] < cbn )
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                else
                    goto is_not_a_corner;
            else if( p[pixel[1]] < cbn )
                if( p[pixel[2]] > cbp )
                    if( p[pixel[9]] > cbp )
                        if( p[pixel[7]] > cbp )
                            if( p[pixel[8]] > cbp )
                                if( p[pixel[10]] > cbp )
                                    if( p[pixel[6]] > cbp )
                                        if( p[pixel[5]] > cbp )
                                            if( p[pixel[4]] > cbp )
                                                if( p[pixel[3]] > cbp )
                                                    goto is_a_corner;
                                                else
                                                    if( p[pixel[11]] > cbp )
                                                        if( p[pixel[12]] > cbp )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if( p[pixel[11]] > cbp )
                                                    if( p[pixel[12]] > cbp )
                                                        if( p[pixel[13]] > cbp )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[11]] > cbp )
                                                if( p[pixel[12]] > cbp )
                                                    if( p[pixel[13]] > cbp )
                                                        if( p[pixel[14]] > cbp )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if( p[pixel[11]] > cbp )
                                            if( p[pixel[12]] > cbp )
                                                if( p[pixel[13]] > cbp )
                                                    if( p[pixel[14]] > cbp )
                                                        if( p[pixel[15]] > cbp )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else if( p[pixel[9]] < cbn )
                        if( p[pixel[10]] < cbn )
                            if( p[pixel[11]] < cbn )
                                if( p[pixel[12]] < cbn )
                                    if( p[pixel[13]] < cbn )
                                        if( p[pixel[14]] < cbn )
                                            if( p[pixel[15]] < cbn )
                                                goto is_a_corner;
                                            else
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        if( p[pixel[8]] < cbn )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[5]] < cbn )
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        if( p[pixel[8]] < cbn )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if( p[pixel[4]] < cbn )
                                            if( p[pixel[5]] < cbn )
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        if( p[pixel[8]] < cbn )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if( p[pixel[3]] < cbn )
                                        if( p[pixel[4]] < cbn )
                                            if( p[pixel[5]] < cbn )
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        if( p[pixel[8]] < cbn )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                else if( p[pixel[2]] < cbn )
                    if( p[pixel[3]] > cbp )
                        if( p[pixel[10]] > cbp )
                            if( p[pixel[7]] > cbp )
                                if( p[pixel[8]] > cbp )
                                    if( p[pixel[9]] > cbp )
                                        if( p[pixel[11]] > cbp )
                                            if( p[pixel[6]] > cbp )
                                                if( p[pixel[5]] > cbp )
                                                    if( p[pixel[4]] > cbp )
                                                        goto is_a_corner;
                                                    else
                                                        if( p[pixel[12]] > cbp )
                                                            if( p[pixel[13]] > cbp )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                else
                                                    if( p[pixel[12]] > cbp )
                                                        if( p[pixel[13]] > cbp )
                                                            if( p[pixel[14]] > cbp )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if( p[pixel[12]] > cbp )
                                                    if( p[pixel[13]] > cbp )
                                                        if( p[pixel[14]] > cbp )
                                                            if( p[pixel[15]] > cbp )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else if( p[pixel[10]] < cbn )
                            if( p[pixel[11]] < cbn )
                                if( p[pixel[12]] < cbn )
                                    if( p[pixel[13]] < cbn )
                                        if( p[pixel[14]] < cbn )
                                            if( p[pixel[15]] < cbn )
                                                goto is_a_corner;
                                            else
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        if( p[pixel[8]] < cbn )
                                                            if( p[pixel[9]] < cbn )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[5]] < cbn )
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        if( p[pixel[8]] < cbn )
                                                            if( p[pixel[9]] < cbn )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if( p[pixel[4]] < cbn )
                                            if( p[pixel[5]] < cbn )
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        if( p[pixel[8]] < cbn )
                                                            if( p[pixel[9]] < cbn )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else if( p[pixel[3]] < cbn )
                        if( p[pixel[4]] > cbp )
                            if( p[pixel[13]] > cbp )
                                if( p[pixel[7]] > cbp )
                                    if( p[pixel[8]] > cbp )
                                        if( p[pixel[9]] > cbp )
                                            if( p[pixel[10]] > cbp )
                                                if( p[pixel[11]] > cbp )
                                                    if( p[pixel[12]] > cbp )
                                                        if( p[pixel[6]] > cbp )
                                                            if( p[pixel[5]] > cbp )
                                                                goto is_a_corner;
                                                            else
                                                                if( p[pixel[14]] > cbp )
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                        else
                                                            if( p[pixel[14]] > cbp )
                                                                if( p[pixel[15]] > cbp )
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else if( p[pixel[13]] < cbn )
                                if( p[pixel[11]] > cbp )
                                    if( p[pixel[5]] > cbp )
                                        if( p[pixel[6]] > cbp )
                                            if( p[pixel[7]] > cbp )
                                                if( p[pixel[8]] > cbp )
                                                    if( p[pixel[9]] > cbp )
                                                        if( p[pixel[10]] > cbp )
                                                            if( p[pixel[12]] > cbp )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else if( p[pixel[11]] < cbn )
                                    if( p[pixel[12]] < cbn )
                                        if( p[pixel[14]] < cbn )
                                            if( p[pixel[15]] < cbn )
                                                goto is_a_corner;
                                            else
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        if( p[pixel[8]] < cbn )
                                                            if( p[pixel[9]] < cbn )
                                                                if( p[pixel[10]] < cbn )
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[5]] < cbn )
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        if( p[pixel[8]] < cbn )
                                                            if( p[pixel[9]] < cbn )
                                                                if( p[pixel[10]] < cbn )
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                if( p[pixel[5]] > cbp )
                                    if( p[pixel[6]] > cbp )
                                        if( p[pixel[7]] > cbp )
                                            if( p[pixel[8]] > cbp )
                                                if( p[pixel[9]] > cbp )
                                                    if( p[pixel[10]] > cbp )
                                                        if( p[pixel[11]] > cbp )
                                                            if( p[pixel[12]] > cbp )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                        else if( p[pixel[4]] < cbn )
                            if( p[pixel[5]] > cbp )
                                if( p[pixel[14]] > cbp )
                                    if( p[pixel[7]] > cbp )
                                        if( p[pixel[8]] > cbp )
                                            if( p[pixel[9]] > cbp )
                                                if( p[pixel[10]] > cbp )
                                                    if( p[pixel[11]] > cbp )
                                                        if( p[pixel[12]] > cbp )
                                                            if( p[pixel[13]] > cbp )
                                                                if( p[pixel[6]] > cbp )
                                                                    goto is_a_corner;
                                                                else
                                                                    if( p[pixel[15]] > cbp )
                                                                        goto is_a_corner;
                                                                    else
                                                                        goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else if( p[pixel[14]] < cbn )
                                    if( p[pixel[12]] > cbp )
                                        if( p[pixel[6]] > cbp )
                                            if( p[pixel[7]] > cbp )
                                                if( p[pixel[8]] > cbp )
                                                    if( p[pixel[9]] > cbp )
                                                        if( p[pixel[10]] > cbp )
                                                            if( p[pixel[11]] > cbp )
                                                                if( p[pixel[13]] > cbp )
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else if( p[pixel[12]] < cbn )
                                        if( p[pixel[13]] < cbn )
                                            if( p[pixel[15]] < cbn )
                                                goto is_a_corner;
                                            else
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        if( p[pixel[8]] < cbn )
                                                            if( p[pixel[9]] < cbn )
                                                                if( p[pixel[10]] < cbn )
                                                                    if( p[pixel[11]] < cbn )
                                                                        goto is_a_corner;
                                                                    else
                                                                        goto is_not_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    if( p[pixel[6]] > cbp )
                                        if( p[pixel[7]] > cbp )
                                            if( p[pixel[8]] > cbp )
                                                if( p[pixel[9]] > cbp )
                                                    if( p[pixel[10]] > cbp )
                                                        if( p[pixel[11]] > cbp )
                                                            if( p[pixel[12]] > cbp )
                                                                if( p[pixel[13]] > cbp )
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else if( p[pixel[5]] < cbn )
                                if( p[pixel[6]] > cbp )
                                    if( p[pixel[15]] < cbn )
                                        if( p[pixel[13]] > cbp )
                                            if( p[pixel[7]] > cbp )
                                                if( p[pixel[8]] > cbp )
                                                    if( p[pixel[9]] > cbp )
                                                        if( p[pixel[10]] > cbp )
                                                            if( p[pixel[11]] > cbp )
                                                                if( p[pixel[12]] > cbp )
                                                                    if( p[pixel[14]] > cbp )
                                                                        goto is_a_corner;
                                                                    else
                                                                        goto is_not_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else if( p[pixel[13]] < cbn )
                                            if( p[pixel[14]] < cbn )
                                                goto is_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        if( p[pixel[7]] > cbp )
                                            if( p[pixel[8]] > cbp )
                                                if( p[pixel[9]] > cbp )
                                                    if( p[pixel[10]] > cbp )
                                                        if( p[pixel[11]] > cbp )
                                                            if( p[pixel[12]] > cbp )
                                                                if( p[pixel[13]] > cbp )
                                                                    if( p[pixel[14]] > cbp )
                                                                        goto is_a_corner;
                                                                    else
                                                                        goto is_not_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else if( p[pixel[6]] < cbn )
                                    if( p[pixel[7]] > cbp )
                                        if( p[pixel[14]] > cbp )
                                            if( p[pixel[8]] > cbp )
                                                if( p[pixel[9]] > cbp )
                                                    if( p[pixel[10]] > cbp )
                                                        if( p[pixel[11]] > cbp )
                                                            if( p[pixel[12]] > cbp )
                                                                if( p[pixel[13]] > cbp )
                                                                    if( p[pixel[15]] > cbp )
                                                                        goto is_a_corner;
                                                                    else
                                                                        goto is_not_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else if( p[pixel[14]] < cbn )
                                            if( p[pixel[15]] < cbn )
                                                goto is_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else if( p[pixel[7]] < cbn )
                                        if( p[pixel[8]] < cbn )
                                            goto is_a_corner;
                                        else
                                            if( p[pixel[15]] < cbn )
                                                goto is_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if( p[pixel[14]] < cbn )
                                            if( p[pixel[15]] < cbn )
                                                goto is_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if( p[pixel[13]] > cbp )
                                        if( p[pixel[7]] > cbp )
                                            if( p[pixel[8]] > cbp )
                                                if( p[pixel[9]] > cbp )
                                                    if( p[pixel[10]] > cbp )
                                                        if( p[pixel[11]] > cbp )
                                                            if( p[pixel[12]] > cbp )
                                                                if( p[pixel[14]] > cbp )
                                                                    if( p[pixel[15]] > cbp )
                                                                        goto is_a_corner;
                                                                    else
                                                                        goto is_not_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else if( p[pixel[13]] < cbn )
                                        if( p[pixel[14]] < cbn )
                                            if( p[pixel[15]] < cbn )
                                                goto is_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                if( p[pixel[12]] > cbp )
                                    if( p[pixel[7]] > cbp )
                                        if( p[pixel[8]] > cbp )
                                            if( p[pixel[9]] > cbp )
                                                if( p[pixel[10]] > cbp )
                                                    if( p[pixel[11]] > cbp )
                                                        if( p[pixel[13]] > cbp )
                                                            if( p[pixel[14]] > cbp )
                                                                if( p[pixel[6]] > cbp )
                                                                    goto is_a_corner;
                                                                else
                                                                    if( p[pixel[15]] > cbp )
                                                                        goto is_a_corner;
                                                                    else
                                                                        goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else if( p[pixel[12]] < cbn )
                                    if( p[pixel[13]] < cbn )
                                        if( p[pixel[14]] < cbn )
                                            if( p[pixel[15]] < cbn )
                                                goto is_a_corner;
                                            else
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        if( p[pixel[8]] < cbn )
                                                            if( p[pixel[9]] < cbn )
                                                                if( p[pixel[10]] < cbn )
                                                                    if( p[pixel[11]] < cbn )
                                                                        goto is_a_corner;
                                                                    else
                                                                        goto is_not_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                        else
                            if( p[pixel[11]] > cbp )
                                if( p[pixel[7]] > cbp )
                                    if( p[pixel[8]] > cbp )
                                        if( p[pixel[9]] > cbp )
                                            if( p[pixel[10]] > cbp )
                                                if( p[pixel[12]] > cbp )
                                                    if( p[pixel[13]] > cbp )
                                                        if( p[pixel[6]] > cbp )
                                                            if( p[pixel[5]] > cbp )
                                                                goto is_a_corner;
                                                            else
                                                                if( p[pixel[14]] > cbp )
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                        else
                                                            if( p[pixel[14]] > cbp )
                                                                if( p[pixel[15]] > cbp )
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else if( p[pixel[11]] < cbn )
                                if( p[pixel[12]] < cbn )
                                    if( p[pixel[13]] < cbn )
                                        if( p[pixel[14]] < cbn )
                                            if( p[pixel[15]] < cbn )
                                                goto is_a_corner;
                                            else
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        if( p[pixel[8]] < cbn )
                                                            if( p[pixel[9]] < cbn )
                                                                if( p[pixel[10]] < cbn )
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[5]] < cbn )
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        if( p[pixel[8]] < cbn )
                                                            if( p[pixel[9]] < cbn )
                                                                if( p[pixel[10]] < cbn )
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                    else
                        if( p[pixel[10]] > cbp )
                            if( p[pixel[7]] > cbp )
                                if( p[pixel[8]] > cbp )
                                    if( p[pixel[9]] > cbp )
                                        if( p[pixel[11]] > cbp )
                                            if( p[pixel[12]] > cbp )
                                                if( p[pixel[6]] > cbp )
                                                    if( p[pixel[5]] > cbp )
                                                        if( p[pixel[4]] > cbp )
                                                            goto is_a_corner;
                                                        else
                                                            if( p[pixel[13]] > cbp )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                    else
                                                        if( p[pixel[13]] > cbp )
                                                            if( p[pixel[14]] > cbp )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                else
                                                    if( p[pixel[13]] > cbp )
                                                        if( p[pixel[14]] > cbp )
                                                            if( p[pixel[15]] > cbp )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else if( p[pixel[10]] < cbn )
                            if( p[pixel[11]] < cbn )
                                if( p[pixel[12]] < cbn )
                                    if( p[pixel[13]] < cbn )
                                        if( p[pixel[14]] < cbn )
                                            if( p[pixel[15]] < cbn )
                                                goto is_a_corner;
                                            else
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        if( p[pixel[8]] < cbn )
                                                            if( p[pixel[9]] < cbn )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[5]] < cbn )
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        if( p[pixel[8]] < cbn )
                                                            if( p[pixel[9]] < cbn )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if( p[pixel[4]] < cbn )
                                            if( p[pixel[5]] < cbn )
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        if( p[pixel[8]] < cbn )
                                                            if( p[pixel[9]] < cbn )
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                else
                    if( p[pixel[9]] > cbp )
                        if( p[pixel[7]] > cbp )
                            if( p[pixel[8]] > cbp )
                                if( p[pixel[10]] > cbp )
                                    if( p[pixel[11]] > cbp )
                                        if( p[pixel[6]] > cbp )
                                            if( p[pixel[5]] > cbp )
                                                if( p[pixel[4]] > cbp )
                                                    if( p[pixel[3]] > cbp )
                                                        goto is_a_corner;
                                                    else
                                                        if( p[pixel[12]] > cbp )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                else
                                                    if( p[pixel[12]] > cbp )
                                                        if( p[pixel[13]] > cbp )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if( p[pixel[12]] > cbp )
                                                    if( p[pixel[13]] > cbp )
                                                        if( p[pixel[14]] > cbp )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[12]] > cbp )
                                                if( p[pixel[13]] > cbp )
                                                    if( p[pixel[14]] > cbp )
                                                        if( p[pixel[15]] > cbp )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else if( p[pixel[9]] < cbn )
                        if( p[pixel[10]] < cbn )
                            if( p[pixel[11]] < cbn )
                                if( p[pixel[12]] < cbn )
                                    if( p[pixel[13]] < cbn )
                                        if( p[pixel[14]] < cbn )
                                            if( p[pixel[15]] < cbn )
                                                goto is_a_corner;
                                            else
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        if( p[pixel[8]] < cbn )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[5]] < cbn )
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        if( p[pixel[8]] < cbn )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if( p[pixel[4]] < cbn )
                                            if( p[pixel[5]] < cbn )
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        if( p[pixel[8]] < cbn )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if( p[pixel[3]] < cbn )
                                        if( p[pixel[4]] < cbn )
                                            if( p[pixel[5]] < cbn )
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        if( p[pixel[8]] < cbn )
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
            else
                if( p[pixel[8]] > cbp )
                    if( p[pixel[7]] > cbp )
                        if( p[pixel[9]] > cbp )
                            if( p[pixel[10]] > cbp )
                                if( p[pixel[6]] > cbp )
                                    if( p[pixel[5]] > cbp )
                                        if( p[pixel[4]] > cbp )
                                            if( p[pixel[3]] > cbp )
                                                if( p[pixel[2]] > cbp )
                                                    goto is_a_corner;
                                                else
                                                    if( p[pixel[11]] > cbp )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if( p[pixel[11]] > cbp )
                                                    if( p[pixel[12]] > cbp )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[11]] > cbp )
                                                if( p[pixel[12]] > cbp )
                                                    if( p[pixel[13]] > cbp )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if( p[pixel[11]] > cbp )
                                            if( p[pixel[12]] > cbp )
                                                if( p[pixel[13]] > cbp )
                                                    if( p[pixel[14]] > cbp )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if( p[pixel[11]] > cbp )
                                        if( p[pixel[12]] > cbp )
                                            if( p[pixel[13]] > cbp )
                                                if( p[pixel[14]] > cbp )
                                                    if( p[pixel[15]] > cbp )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                else if( p[pixel[8]] < cbn )
                    if( p[pixel[9]] < cbn )
                        if( p[pixel[10]] < cbn )
                            if( p[pixel[11]] < cbn )
                                if( p[pixel[12]] < cbn )
                                    if( p[pixel[13]] < cbn )
                                        if( p[pixel[14]] < cbn )
                                            if( p[pixel[15]] < cbn )
                                                goto is_a_corner;
                                            else
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[5]] < cbn )
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if( p[pixel[4]] < cbn )
                                            if( p[pixel[5]] < cbn )
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if( p[pixel[3]] < cbn )
                                        if( p[pixel[4]] < cbn )
                                            if( p[pixel[5]] < cbn )
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                if( p[pixel[2]] < cbn )
                                    if( p[pixel[3]] < cbn )
                                        if( p[pixel[4]] < cbn )
                                            if( p[pixel[5]] < cbn )
                                                if( p[pixel[6]] < cbn )
                                                    if( p[pixel[7]] < cbn )
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                else
                    goto is_not_a_corner;
        else
            if( p[pixel[7]] > cbp )
                if( p[pixel[8]] > cbp )
                    if( p[pixel[9]] > cbp )
                        if( p[pixel[6]] > cbp )
                            if( p[pixel[5]] > cbp )
                                if( p[pixel[4]] > cbp )
                                    if( p[pixel[3]] > cbp )
                                        if( p[pixel[2]] > cbp )
                                            if( p[pixel[1]] > cbp )
                                                goto is_a_corner;
                                            else
                                                if( p[pixel[10]] > cbp )
                                                    goto is_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[10]] > cbp )
                                                if( p[pixel[11]] > cbp )
                                                    goto is_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if( p[pixel[10]] > cbp )
                                            if( p[pixel[11]] > cbp )
                                                if( p[pixel[12]] > cbp )
                                                    goto is_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if( p[pixel[10]] > cbp )
                                        if( p[pixel[11]] > cbp )
                                            if( p[pixel[12]] > cbp )
                                                if( p[pixel[13]] > cbp )
                                                    goto is_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                if( p[pixel[10]] > cbp )
                                    if( p[pixel[11]] > cbp )
                                        if( p[pixel[12]] > cbp )
                                            if( p[pixel[13]] > cbp )
                                                if( p[pixel[14]] > cbp )
                                                    goto is_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                        else
                            if( p[pixel[10]] > cbp )
                                if( p[pixel[11]] > cbp )
                                    if( p[pixel[12]] > cbp )
                                        if( p[pixel[13]] > cbp )
                                            if( p[pixel[14]] > cbp )
                                                if( p[pixel[15]] > cbp )
                                                    goto is_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                else
                    goto is_not_a_corner;
            else if( p[pixel[7]] < cbn )
                if( p[pixel[8]] < cbn )
                    if( p[pixel[9]] < cbn )
                        if( p[pixel[6]] < cbn )
                            if( p[pixel[5]] < cbn )
                                if( p[pixel[4]] < cbn )
                                    if( p[pixel[3]] < cbn )
                                        if( p[pixel[2]] < cbn )
                                            if( p[pixel[1]] < cbn )
                                                goto is_a_corner;
                                            else
                                                if( p[pixel[10]] < cbn )
                                                    goto is_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if( p[pixel[10]] < cbn )
                                                if( p[pixel[11]] < cbn )
                                                    goto is_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if( p[pixel[10]] < cbn )
                                            if( p[pixel[11]] < cbn )
                                                if( p[pixel[12]] < cbn )
                                                    goto is_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if( p[pixel[10]] < cbn )
                                        if( p[pixel[11]] < cbn )
                                            if( p[pixel[12]] < cbn )
                                                if( p[pixel[13]] < cbn )
                                                    goto is_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                if( p[pixel[10]] < cbn )
                                    if( p[pixel[11]] < cbn )
                                        if( p[pixel[12]] < cbn )
                                            if( p[pixel[13]] < cbn )
                                                if( p[pixel[14]] < cbn )
                                                    goto is_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                        else
                            if( p[pixel[10]] < cbn )
                                if( p[pixel[11]] < cbn )
                                    if( p[pixel[12]] < cbn )
                                        if( p[pixel[13]] < cbn )
                                            if( p[pixel[14]] < cbn )
                                                if( p[pixel[15]] < cbn )
                                                    goto is_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                else
                    goto is_not_a_corner;
            else
                goto is_not_a_corner;

is_a_corner:

        thr_min = thr;
        goto end_if;

is_not_a_corner:

        thr_max = thr;
        goto end_if;

end_if:

        if( thr_min == thr_max - 1 || thr_min == thr_max )
            return thr_min;
        thr = ( thr_min + thr_max ) / 2;
    }
}

int*
extractFASTscore( const unsigned char* data , const int& ns ,
                  xy* corners , int num_corners , int thr )
{
    int* scores = (int*)malloc( sizeof(int) * num_corners );

    int pixel[16];
    makeOffsets( pixel, ns );

    for( int n = 0 ; n < num_corners ; ++n )
        scores[n] = extractFASTscore( data + corners[n].y * ns + corners[n].x , pixel , thr );

    return scores;
}

}

#endif
