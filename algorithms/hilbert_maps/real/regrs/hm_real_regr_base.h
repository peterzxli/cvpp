#ifndef HM_REAL_REGRESSOR_BASE_H
#define HM_REAL_REGRESSOR_BASE_H

#include <cvpp/auxiliar/macros.h>
#include <cvpp/auxiliar/timer.h>

#include <cvpp/containers/matrix.h>
#include <cvpp/containers/sparse.h>

#include <cvpp/algorithms/kdtree/kdtree.h>

namespace cvpp
{

class HMregrBase
{

public:

    unsigned ndims;
    KDtreed kdtree;

    Matd ctrs,weights,qty;
    SeqMatd means,vars,covs,icovs;

public:

    virtual const void start() {}
    virtual const void add( const SeqMatd& , const SeqMatd& , const Seq<Matd>& ) {}

};

}

#endif



