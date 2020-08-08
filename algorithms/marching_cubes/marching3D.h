#ifndef MARCHING3D_H
#define MARCHING3D_H

#include <cvpp/containers/matrix.h>
#include <cvpp/containers/vector.h>

namespace cvpp
{

TPL_T Matrix<T>
marching3D( const Matrix<T>& ,
            const Matrix<T>& , const T& );

TPL_T Matrix<T>
marching3D( const Matrix<T>& , const Matrix<int>& ,
            const Matrix<T>& , const T& );


TPL_T  Pts3<T>
marching3D( const Matrix<int>& ,  const Matrix<T>& ,
            const Matrix<T>& , const Matrix<int>& ,
            const Matrix<T>& , const T& );

TPL_T Matrix<T>
marching3D( const Matrix<T>& , const Matrix<int>& ,
            const Matrix<T>& , const T& , const T& );

}

#endif
