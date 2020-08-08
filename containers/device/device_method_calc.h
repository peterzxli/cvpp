#include "../device.h"

namespace cvpp
{

// Inverse
TPL_T Device<T>
Device<T>::inv() const
{
    return af::inverse( arr() );
}

}
