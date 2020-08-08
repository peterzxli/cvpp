#ifndef ACQ_VARIANCE_H
#define ACQ_VARIANCE_H

#include "../acq_base.h"

namespace cvpp
{

class AcqVariance : public AcqBase
{
    unsigned n_hyps() const { return 1; }

    double eval( const Matd& pts , const Matd& rnd , const double& mf , const double& vf )
    {
        return - std::pow( vf , hyps[0] );
    }

};

}

#endif
