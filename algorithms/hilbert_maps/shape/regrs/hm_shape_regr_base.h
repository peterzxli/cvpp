#ifndef HM_SHAPE_REGRESSOR_BASE_H
#define HM_SHAPE_REGRESSOR_BASE_H

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

    Matd ctrs,modes;
    SeqMatd covs,icovs,vals,vecs;

public:

    virtual const void start( const unsigned& ) {}

    virtual const void add( const Matd& ) { disp( "BASE HM REGRESSOR ADD"); }
    virtual const void add( const Matd& , const SeqMatd& ) { disp( "BASE HM REGRESSOR ADD"); }
    virtual const void add( const Matd& , const SeqMatd& , const SeqMatd& ,
                            const SeqMatd& , const SeqMatd& ) { disp( "BASE HM REGRESSOR ADD"); }
    virtual const void add( const Matd& , const Matd& , const SeqMatd& , const SeqMatd& ,
                            const SeqMatd& , const SeqMatd& ) { disp( "BASE HM REGRESSOR ADD"); }

    virtual const void train( const Matd& , const Matd& ) {}

    virtual Matd query( const Matd& ) const {}
    virtual const void query( const Matd& , Matd& , Matd& ) const {}

};

}

#endif



