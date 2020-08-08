#ifndef EXTRACTOR_FAST
#define EXTRACTOR_FAST

#include <cvpp/containers/image.h>
#include <cvpp/containers/vector.h>

#include <cvpp/algorithms/features/fast/extractor_fast_detect.h>
#include <cvpp/algorithms/features/fast/extractor_fast_score.h>
#include <cvpp/algorithms/features/fast/extractor_fast_nonmax.h>

namespace cvpp
{

TPL_TC
Pts2i extractFAST(const Image<T,C>& img , const int& b )
{
    xy *corners , *nonmax ;
    int num_corners , ret_num_corners , *scores;

    const unsigned char* data = img.cv_data();
    int nc = img.c() , nr = img.r() , ns = img.c();

    corners = extractFASTdetect( data , nr , nc , ns , b , &num_corners );
    scores  = extractFASTscore(  data , ns , corners , num_corners , b );
    nonmax  = extractFASTnonmax( corners , scores , num_corners , &ret_num_corners );

    free(corners);
    free(scores);

    Pts2i pts( ret_num_corners );
    forLOOPi( pts.n() ) pts[i] = Pt2i( nonmax[i].x , nonmax[i].y );

    return pts;
}

}

#endif
