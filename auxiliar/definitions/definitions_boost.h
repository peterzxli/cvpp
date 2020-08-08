#ifndef DEFINITIONS_BOOST_H
#define DEFINITIONS_BOOST_H

#include <boost/thread.hpp>
#include <boost/chrono.hpp>

namespace cvpp
{

using MilliSec = boost::chrono::milliseconds;
using MicroSec = boost::chrono::microseconds;
using NanoSec  = boost::chrono::nanoseconds;

using Clock = boost::chrono::system_clock;
using Time  = boost::chrono::time_point< Clock >;

using Mutex  = boost::mutex;
using Thread = boost::thread;

}

#endif
