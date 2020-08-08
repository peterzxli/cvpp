#ifndef EXTRACTOR_FAST_NONMAX
#define EXTRACTOR_FAST_NONMAX

#include <cvpp/containers/image.h>
#include <cvpp/algorithms/features/fast/extractor_fast_detect.h>

namespace cvpp
{

xy* extractFASTnonmax( const xy* corners , const int* scores ,
                       int num_corners , int* ret_num_nonmax )
{
    xy* ret_nonmax;
    int* row_start;

    int point_above = 0;
    int point_below = 0;
    int last_row , num_nonmax = 0;

    last_row = corners[num_corners-1].y;

    ret_nonmax = (xy*)malloc( num_corners * sizeof(xy) );
    row_start = (int*)malloc( (last_row + 1) * sizeof(int) );

    for( int i = 0; i < last_row + 1 ; ++i )
        row_start[i] = -1;

    int prev_row = -1;
    for( int i = 0 ; i < num_corners ; ++i )
    {
        if( corners[i].y != prev_row )
        {
            row_start[corners[i].y] = i;
            prev_row = corners[i].y;
        }
    }

    for( int i = 0 ; i < num_corners ; ++i )
    {
        int score = scores[i];
        xy pos = corners[i];

        if( i > 0 )
            if( corners[i-1].x == pos.x - 1 &&
                corners[i-1].y == pos.y && ( scores[i-1] >= score ) )
                continue;

        if( i < num_corners - 1 )
            if( corners[i+1].x == pos.x + 1 &&
                corners[i+1].y == pos.y && ( scores[i+1] >= score ) )
                continue;

        if( pos.y != 0 && row_start[pos.y-1] != -1 )
        {
            if( corners[point_above].y < pos.y - 1 )
                point_above = row_start[pos.y-1];

            for( ; corners[point_above].y < pos.y &&
                   corners[point_above].x < pos.x - 1 ; point_above++ );

            for( int j = point_above ; corners[j].y < pos.y && corners[j].x <= pos.x + 1 ; ++j )
            {
                int x = corners[j].x;
                if( ( x == pos.x - 1 || x == pos.x || x == pos.x+1 ) && ( scores[j] >= score ) )
                    goto is_max;
            }
        }

        if( pos.y != last_row && row_start[pos.y+1] != -1 && point_below < num_corners )
        {
            if( corners[point_below].y < pos.y + 1 )
                point_below = row_start[pos.y+1];

            for( ; point_below < num_corners && corners[point_below].y == pos.y + 1 &&
                                                corners[point_below].x  < pos.x - 1 ; point_below++ );

            for( int j = point_below ; j < num_corners && corners[j].y == pos.y + 1 &&
                                                          corners[j].x <= pos.x + 1 ; j++ )
            {
                int x = corners[j].x;
                if( ( x == pos.x - 1 || x == pos.x || x == pos.x + 1 ) && ( scores[j] >= score ) )
                    goto is_max;
            }
        }

        ret_nonmax[num_nonmax++] = corners[i];

is_max:
        ;
    }

    free(row_start);
    *ret_num_nonmax = num_nonmax;

    return ret_nonmax;
}

}

#endif
