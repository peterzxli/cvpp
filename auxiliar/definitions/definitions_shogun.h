#ifndef DEFINITIONS_SHOGUN_H
#define DEFINITIONS_SHOGUN_H
#ifdef SHOGUN_FOUND

#include "definitions_template.h"

#include <shogun/base/init.h>
#include <shogun/lib/common.h>

namespace cvpp
{

TPL_T using SGMatrix = shogun::SGMatrix<T>;
TPL_T using SGVector = shogun::SGVector<T>;

}

#endif
#endif
