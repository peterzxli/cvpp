#ifndef LIK_LOGISTIC_H
#define LIK_LOGISTIC_H

#include "../lik_base.h"

namespace cvpp
{

class LikLogistic : public LikBase
{

protected:

    Matd dlp , d2lp;
    Matd m , y , s , p , ps ;

public:

    LikLogistic()
    {
    }

    Matd calc( const Matd& m , const Matd& y )
    {
        this->m = m , this->y = y;

        s = - y % m , ps = s.floor(0);
        Matd lp = - ( ps + ( ( - ps ).exp() + ( s - ps ).exp() ).log() );

        s = m.ceil(0);
        p = s.exp() / ( s.exp() + ( s - m ).exp() );

        return lp;
    }

    Matd grad1() const
    {
        return ( y + 1.0 ) / 2.0 - p;
    }

    Matd grad2() const
    {
        return - ( 2.0 * s - m ).exp() / ( s.exp() + ( s - m ).exp() ).square();
    }

    Matd grad3() const
    {
        return 2.0 * grad2() % ( 0.5 - p );
    }

};

}

#endif
