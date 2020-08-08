#ifndef STRUCT_KMEANS_H
#define STRUCT_KMEANS_H

#include <cvpp/containers/matrix.h>
#include <cvpp/containers/vector.h>

namespace cvpp
{

struct KMdata
{
    Matd X,Z,M,P;
    Mati I; Seqi idx;

    int n,m,d,c,t;
    Vecd pot,err;
};

}

#endif

