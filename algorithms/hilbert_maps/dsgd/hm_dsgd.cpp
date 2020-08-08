#include "./hm_dsgd.h"

namespace cvpp
{

// Constructor
HMdsgd::HMdsgd( HMregrBase* regr , RKSfeatBase* feat )
{
    this->regr = regr;
    this->regr->setFeature( feat );
}

// Destructor
HMdsgd::~HMdsgd()
{
    delete regr;
}

// Train
const void
HMdsgd::train()
{
    regr->train();
}

// Query
Matd
HMdsgd::query( const Matd& X ) const
{
    return regr->query( X );
}

}
