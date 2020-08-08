#ifndef ACQ_RACING_H
#define ACQ_RACING_H

#include "../acq_base.h"

namespace cvpp
{

class AcqRacing : public AcqBase
{
    unsigned n_hyps() const { return 1; }

    double eval( const Matd& pts , const Matd& rnd , const double& mf , const double& vf )
    {
//        return sqrt( mf ) / vf;
        return mf / ( 2.0 * sqrt( vf ) );
//        return 1.0 / vf;

    }

};

}

#endif
