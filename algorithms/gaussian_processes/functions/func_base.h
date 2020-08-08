#ifndef FUNC_BASE_H
#define FUNC_BASE_H

#include <cvpp/auxiliar/macros.h>

#include <cvpp/containers/matrix.h>
#include <cvpp/containers/vector.h>

#include <cvpp/auxiliar/definitions/definitions_gp.h>

namespace cvpp
{

class FuncBase
{

protected:

public:

    virtual const unsigned n() const { return 0; }

};

}

#endif
