#ifndef TIMER_H
#define TIMER_H

#include <cvpp/auxiliar/definitions.h>

namespace cvpp
{

class Timer
{

protected:

    Time last;
    String name;

public:

    Timer( const String& str = "" )
    {
        name = str;
        tick();
    }

    double check()
    {
        Time curr = Clock::now();
        MilliSec duration = boost::chrono::duration_cast< MilliSec >( curr - last );
        return duration.count();
    }

    double tick()
    {
        Time curr = Clock::now();
        MilliSec duration = boost::chrono::duration_cast< MilliSec >( curr - last );
        last = curr; return duration.count();
    }

    void pcheck()
    { std::cout << "Time-checking : " << name << check() << " msec" << std::endl; }

    void ptick( const String& str = "" )
    { std::cout << "Time-ticking : " << name << " " << str << " : " << tick() << " msec" << std::endl; }

};

}

#endif
