#ifndef ALGL_H
#define ALGL_H

#include <cvpp/containers/matrix.h>

namespace cvpp {
namespace algl
{

// CALC

TPL_T T dot( const Matrix<T>& , const Matrix<T>& );

TPL_T Matrix<T> cross( const Matrix<T>& , const Matrix<T>& );

TPL_T Matrix<T> normal( const Matrix<T>& );
TPL_T Matrix<T> normal( const Matrix<T>& , const Matrix<T>& );
TPL_T Matrix<T> normal( const Matrix<T>& , const Matrix<T>& , const Matrix<T>& );

// ROTATION

TPL_T Matrix<T> rotationAxis( const Matrix<T>& , const T& );
TPL_T Matrix<T> rotationAxis( const Matrix<T>& , const Matrix<T>& , const T& );

TPL_T Matrix<T> rotationTwoVec( const Matrix<T>& , const Matrix<T>& );
TPL_T Matrix<T> rotationAlign( const Matrix<T>& , const Matrix<T>& );

TPL_T void rotationAuxMat( const Matrix<T>& , Matrix<T>& , Matrix<T>& );

}}

#include "algl_src.h"

#endif
