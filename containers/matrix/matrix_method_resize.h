#include "../matrix.h"

namespace cvpp
{

// Resize (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::Resize( const int& r , const int& c )
{
    if( !raw_ptr )
        initialise( r , c );
    else
    {
        if( this->r() != r || this->c() != c )
        {
            raw_ptr->resize( r , c );
            update();
        }
    }

    return *this;
}

// Append (SELF)
TPL_T inline Matrix<T>&
Matrix<T>::Append( const int& r , const int& c )
{
    if( !raw_ptr )
        initialise( r , c );
    else
    {
        raw_ptr->conservativeResize( this->r() + r ,
                                     this->c() + c );
        update();
    }

    return *this;
}

// Append (SELF)
TPL_T inline Matrix<T>
Matrix<T>::append( const int& r , const int& c ) const
{
    Matrix<T> tmp( this->r() + r , this->c() + c );
    tmp.blu( this->r() , this->c() ) = *this;
    return tmp;
}

// Repeat Rows (NEW)
TPL_T Matrix<T>
Matrix<T>::repRows( const int& nr ) const
{
    Matrix<T> tmp( nr * r() , c() );
    tmp.eig().noalias() = eig().replicate( nr , 1 );
    return tmp;
}

// Repeat Cols (NEW)
TPL_T Matrix<T>
Matrix<T>::repCols( const int& nc ) const
{
    Matrix<T> tmp( r() , nc * c() );
    tmp.eig().noalias() = eig().replicate( 1 , nc );
    return tmp;
}

// Append Left (NEW)
TPL_T Matrix<T>
Matrix<T>::appL( const int& n ) const
{
    Matrix<T> tmp( r() , c() + n );
    tmp.cr( c() ) = *this;
    return tmp;
}

// Append Up (NEW)
TPL_T Matrix<T>
Matrix<T>::appU( const int& n ) const
{
    Matrix<T> tmp( r() + n , c() );
    tmp.rd( r() ) = *this;
    return tmp;
}

// Append Right (NEW)
TPL_T Matrix<T>
Matrix<T>::appR( const int& n ) const
{
    return append( 0 , n );
}

// Append Down (NEW)
TPL_T Matrix<T>
Matrix<T>::appD( const int& n ) const
{
    return append( n , 0 );
}

// Append Left (SELF)
TPL_T Matrix<T>&
Matrix<T>::AppL( const int& n )
{
    unsigned m = c();
    AppR( n ); cr( m ) = cl( m ).clone();
    return *this;
}

// Append Up (SELF)
TPL_T Matrix<T>&
Matrix<T>::AppU( const int& n )
{
    unsigned m = r();
    AppD( n ); rd( m ) = ru( m ).clone();
    return *this;
}

// Append Right (SELF)
TPL_T Matrix<T>&
Matrix<T>::AppR( const int& n )
{
    return Append( 0 , n );
}

// Append Down (SELF)
TPL_T Matrix<T>&
Matrix<T>::AppD( const int& n )
{
    return Append( n , 0 );
}

// Append Left (NEW)
TPL_T Matrix<T>
Matrix<T>::appL( const Matrix<T>& mat ) const
{
    Matrix<T> tmp = appL( mat.c() );
    tmp.cl( mat.c() ) = mat;
    return tmp;
}

// Append Up (NEW)
TPL_T Matrix<T>
Matrix<T>::appU( const Matrix<T>& mat ) const
{
    Matrix<T> tmp = appU( mat.r() );
    tmp.ru( mat.r() ) = mat;
    return tmp;
}

// Append Right (NEW)
TPL_T Matrix<T>
Matrix<T>::appR( const Matrix<T>& mat ) const
{
    Matrix<T> tmp = appR( mat.c() );
    tmp.cr( mat.c() ) = mat;
    return tmp;
}

// Append Down (NEW)
TPL_T Matrix<T>
Matrix<T>::appD( const Matrix<T>& mat ) const
{
    Matrix<T> tmp = appD( mat.r() );
    tmp.rd( mat.r() ) = mat;
    return tmp;
}

// Append Left (SELF)
TPL_T Matrix<T>&
Matrix<T>::AppL( const Matrix<T>& mat )
{
    if( empty() ) return *this << mat;
    AppL( mat.c() ); cl( mat.c() ) = mat;
    return *this;
}

// Append Up (SELF)
TPL_T Matrix<T>&
Matrix<T>::AppU( const Matrix<T>& mat )
{
    if( empty() ) return *this << mat;
    AppU( mat.r() ); ru( mat.r() ) = mat;
    return *this;
}

// Append Right (SELF)
TPL_T Matrix<T>&
Matrix<T>::AppR( const Matrix<T>& mat )
{
    if( empty() ) return *this << mat;
    AppR( mat.c() ); cr( mat.c() ) = mat;
    return *this;
}

// Append Down (SELF)
TPL_T Matrix<T>&
Matrix<T>::AppD( const Matrix<T>& mat )
{
    if( empty() ) return *this << mat;
    AppD( mat.r() ); rd( mat.r() ) = mat;
    return *this;
}

// Delete Left (NEW)
TPL_T Matrix<T>
Matrix<T>::delL( const int& n ) const
{
    return cr( c() - n ).clone();
}

// Delete Up (NEW)
TPL_T Matrix<T>
Matrix<T>::delU( const int& n ) const
{
    return rd( r() - n ).clone();
}

// Delete Right (NEW)
TPL_T Matrix<T>
Matrix<T>::delR( const int& n ) const
{
    return cl( c() - n ).clone();
}

// Delete Down (NEW)
TPL_T Matrix<T>
Matrix<T>::delD( const int& n ) const
{
    return ru( r() - n ).clone();
}

// Delete Left (SELF)
TPL_T Matrix<T>&
Matrix<T>::DelL( const int& n )
{
    cl( c() - n ) = cr( c() - n ).clone();
    return DelR( n );
}

// Delete Up (SELF)
TPL_T Matrix<T>&
Matrix<T>::DelU( const int& n )
{
    ru( r() - n ) = rd( r() - n ).clone();
    return DelD( n );
}

// Delete Right (SELF)
TPL_T Matrix<T>&
Matrix<T>::DelR( const int& n )
{
    return Append( 0 , - n );
}

// Delete Down (SELF)
TPL_T Matrix<T>&
Matrix<T>::DelD( const int& n )
{
    return Append( - n , 0 );
}

// Append Rows (NEW)
TPL_T Matrix<T>
Matrix<T>::appRows( const int& r , const int& n ) const
{
    Matrix<T> tmp = clone();
    return tmp.AppRows( r , n );
}

// Append Cols (NEW)
TPL_T Matrix<T>
Matrix<T>::appCols( const int& c , const int& n ) const
{
    Matrix<T> tmp = clone();
    return tmp.AppCols( c , n );
}

// Append Rows (SELF)
TPL_T Matrix<T>&
Matrix<T>::AppRows( const int& i , const int& n )
{
    unsigned m = r(); AppD( n );
    rm( ridx(i) + n , 0 ) = rm( ridx(i) , n ).clone();
    return *this;
}

// Append Cols (SELF)
TPL_T Matrix<T>&
Matrix<T>::AppCols( const int& i , const int& n )
{
    unsigned m = c(); AppR( n );
    cm( cidx(i) + n , 0 ) = cm( cidx(i) , n ).clone();
    return *this;
}

// Append Rows (NEW)
TPL_T Matrix<T>
Matrix<T>::appRows( const int& r , const Matrix<T>& mat ) const
{
    Matrix<T> tmp = clone();
    return tmp.AppRows( r , mat );
}

// Append Cols (NEW)
TPL_T Matrix<T>
Matrix<T>::appCols( const int& c , const Matrix<T>& mat ) const
{
    Matrix<T> tmp = clone();
    return tmp.AppCols( c , mat );
}

// Append Rows (SELF)
TPL_T Matrix<T>&
Matrix<T>::AppRows( const int& i , const Matrix<T>& mat )
{
    AppRows( mat.r() );
    r( i , mat.r() ) = mat;
    return *this;
}

// Append Cols (SELF)
TPL_T Matrix<T>&
Matrix<T>::AppCols( const int& i , const Matrix<T>& mat )
{
    AppCols( mat.c() );
    c( i , mat.c() ) = mat;
    return *this;
}

// Delete Rows (NEW)
TPL_T Matrix<T>
Matrix<T>::delRows( const int& r , const int& n ) const
{
    Matrix<T> tmp = clone();
    return tmp.DelRows( r , n );

}

// Delete Cols (NEW)
TPL_T Matrix<T>
Matrix<T>::delCols( const int& c , const int& n ) const
{
    Matrix<T> tmp = clone();
    return tmp.DelCols( c , n );

}

// Delete Rows (SELF)
TPL_T Matrix<T>&
Matrix<T>::DelRows( const int& r , const int& n )
{
    rm( ridx(r) , n ) = rm( ridx(r) + n , 0 );
    return DelD( n );
}

// Delete Cols (SELF)
TPL_T Matrix<T>&
Matrix<T>::DelCols( const int& c , const int& n )
{
    cm( cidx(c) , n ) = cm( cidx(c) + n , 0 );
    return DelR( n );
}

// Keep Rows (NEW)
TPL_T Matrix<T>
Matrix<T>::keepRows( const int& r , const int& n ) const
{
    return this->r( ridx(r) , n ).clone();
}

// Keep Cols (NEW)
TPL_T Matrix<T>
Matrix<T>::keepCols( const int& c , const int& n ) const
{
    return this->c( cidx(c) , n ).clone();
}

// Keep Rows (SELF)
TPL_T Matrix<T>&
Matrix<T>::KeepRows( const int& r , const int& n )
{
    return DelU( ridx(r) ).DelD( this->r() - n - 1 );
}

// Keep Cols (SELF)
TPL_T Matrix<T>&
Matrix<T>::KeepCols( const int& c , const int& n )
{
    return DelL( cidx(c) ).DelR( this->c() - n - 1 );
}

}
