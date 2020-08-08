#ifndef HM_REAL_FEATURE_H
#define HM_REAL_FEATURE_H

#include <cvpp/auxiliar/macros.h>
#include <cvpp/auxiliar/timer.h>

#include <cvpp/containers/matrix.h>
#include <cvpp/containers/sparse.h>

#include <cvpp/algorithms/kdtree/kdtree.h>

namespace cvpp
{

class HMfeatBase
{

public:

    double rad,thr;
    unsigned ndims;

public:

    HMfeatBase()
    {
    }

    virtual double kernel( const EIG<double>& , const Matd& ) const {}



};

}

#endif
