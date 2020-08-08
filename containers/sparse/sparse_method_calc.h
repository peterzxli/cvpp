#include "../sparse.h"

namespace cvpp
{

// Transpose (NEW)
TPL_T inline Sparse<T>
Sparse<T>::t() const
{
    Sparse<T> tmp( c() , r() );
    tmp.eig() = eig().transpose();
    return tmp;
}

// Denominator (NEW)
TPL_T inline Sparse<T>
Sparse<T>::denominator() const
{
    return clone().Denominator();
}

// Denominator (SELF)
TPL_T inline Sparse<T>&
Sparse<T>::Denominator()
{
    #pragma omp parallel for
    forLOOPsprp it.valueRef() = 1.0 / it.valueRef();
    return *this;
}

// Pow (NEW)
TPL_T inline Sparse<T>
Sparse<T>::pow( const double& val ) const
{
    return clone().Pow( val );
}

// Pow (SELF)
TPL_T inline Sparse<T>&
Sparse<T>::Pow( const double& val )
{
    #pragma omp parallel for
    forLOOPsprp it.valueRef() = std::pow( it.valueRef() , val );
    return *this;
}

// Sqrt (NEW)
TPL_T inline Sparse<T>
Sparse<T>::sqrt() const
{
    return clone().Sqrt();
}

// Sqrt (SELF)
TPL_T inline Sparse<T>&
Sparse<T>::Sqrt()
{
    #pragma omp parallel for
    forLOOPsprp it.valueRef() = std::sqrt( it.valueRef() );
    return *this;
}

// Cbrt (NEW)
TPL_T inline Sparse<T>
Sparse<T>::cbrt() const
{
    return clone().Cbrt();
}

// Cbrt (SELF)
TPL_T inline Sparse<T>&
Sparse<T>::Cbrt()
{
    #pragma omp parallel for
    forLOOPsprp it.valueRef() = std::cbrt( it.valueRef() );
    return *this;
}

// Exp (NEW)
TPL_T inline Sparse<T>
Sparse<T>::exp() const
{
    return clone().Exp();
}

// Exp (SELF)
TPL_T inline Sparse<T>&
Sparse<T>::Exp()
{
    #pragma omp parallel for
    forLOOPsprp it.valueRef() = std::exp( it.valueRef() );
    return *this;
}

// Log (NEW)
TPL_T inline Sparse<T>
Sparse<T>::log() const
{
    return clone().Log();
}

// Log (SELF)
TPL_T inline Sparse<T>&
Sparse<T>::Log()
{
    #pragma omp parallel for
    forLOOPsprp it.valueRef() = std::log( it.valueRef() );
    return *this;
}

// Sin (NEW)
TPL_T inline Sparse<T>
Sparse<T>::sin() const
{
    return clone().Sin();
}

// Sin (SELF)
TPL_T inline Sparse<T>&
Sparse<T>::Sin()
{
    #pragma omp parallel for
    forLOOPsprp it.valueRef() = std::sin( it.valueRef() );
    return *this;
}

// Cos (NEW)
TPL_T inline Sparse<T>
Sparse<T>::cos() const
{
    return clone().Cos();
}

// Cos (SELF)
TPL_T inline Sparse<T>&
Sparse<T>::Cos()
{
    #pragma omp parallel for
    forLOOPsprp it.valueRef() = std::cos( it.valueRef() );
    return *this;
}

// ArcSin (NEW)
TPL_T inline Sparse<T>
Sparse<T>::asin() const
{
    return clone().Asin();
}

// ArcSin (SELF)
TPL_T inline Sparse<T>&
Sparse<T>::Asin()
{
    #pragma omp parallel for
    forLOOPsprp it.valueRef() = std::asin( it.valueRef() );
    return *this;
}

// ArcCos (NEW)
TPL_T inline Sparse<T>
Sparse<T>::acos() const
{
    return clone().Acos();
}

// ArcCos (SELF)
TPL_T inline Sparse<T>&
Sparse<T>::Acos()
{
    #pragma omp parallel for
    forLOOPsprp it.valueRef() = std::acos( it.valueRef() );
    return *this;
}

// Abs (NEW)
TPL_T inline Sparse<T>
Sparse<T>::abs() const
{
    return clone().Abs();
}

// Abs (SELF)
TPL_T inline Sparse<T>&
Sparse<T>::Abs()
{
    #pragma omp parallel for
    forLOOPsprp it.valueRef() = std::abs( it.valueRef() );
    return *this;
}

}
