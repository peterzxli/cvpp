#ifndef HM_LARD_REGRESSOR_BASE_H
#define HM_LARD_REGRESSOR_BASE_H

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

    Matd weights,qty;
    SeqMatd orientations;

public:

    virtual const void start( const unsigned& ) {}

    virtual const void add( const Matd& ) {}
    virtual const void add( const Matd& , const Seq<Matd>& ) {}

    virtual const void train( const Sprd& , const Matd& ) {}

    virtual Matd query( const Sprd& ) const {}
    virtual const void query( const Sprd& , Matd& , Matd& ) const {}

};

}

#endif



