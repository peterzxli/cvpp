#ifndef DEFINITIONS_NLOPT_H
#define DEFINITIONS_NLOPT_H
#ifdef NLOPT_FOUND

#include <nlopt.hpp>

namespace cvpp
{

using NLopt = nlopt::opt;
using NLres = nlopt::result;

}

#endif
#endif
