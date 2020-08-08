/*
Copyright 2011. All rights reserved.
Institute of Measurement and Control Systems
Karlsruhe Institute of Technology, Germany

Authors: Andreas Geiger

MatICP is free software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or any later version.

MatICP is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
MatICP; if not, write to the Free Software Foundation, Inc., 51 Franklin
Street, Fifth Floor, Boston, MA 02110-1301, USA 
*/

#ifndef MatICP_H
#define MatICP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#ifndef _MSC_VER
  #include <stdint.h>
#else
  typedef signed __int8     int8_t;
  typedef signed __int16    int16_t;
  typedef signed __int32    int32_t;
  typedef signed __int64    int64_t;
  typedef unsigned __int8   uint8_t;
  typedef unsigned __int16  uint16_t;
  typedef unsigned __int32  uint32_t;
  typedef unsigned __int64  uint64_t;
#endif

#define endll endl << endl // double end line definition

typedef double FLOAT;      // double precision
//typedef float  FLOAT;    // single precision

namespace libicp
{

class MatICP {

public:

  // constructor / deconstructor
  MatICP ();                                                  // init empty 0x0 MatICP
  MatICP (const int32_t m,const int32_t n);                   // init empty mxn MatICP
  MatICP (const int32_t m,const int32_t n,const FLOAT* val_); // init mxn MatICP with values from array 'val'
  MatICP (const MatICP &M);                                   // creates deepcopy of M
  ~MatICP ();

  // assignment operator, copies contents of M
  MatICP& operator= (const MatICP &M);

  // copies subMatICP of M into array 'val', default values copy whole row/column/MatICP
  void getData(FLOAT* val_,int32_t i1=0,int32_t j1=0,int32_t i2=-1,int32_t j2=-1);

  // set or get submatrices of current MatICP
  MatICP getMat(int32_t i1,int32_t j1,int32_t i2=-1,int32_t j2=-1);
  void   setMat(const MatICP &M,const int32_t i,const int32_t j);

  // set sub-MatICP to scalar (default 0), -1 as end replaces whole row/column/MatICP
  void setVal(FLOAT s,int32_t i1=0,int32_t j1=0,int32_t i2=-1,int32_t j2=-1);

  // set (part of) diagonal to scalar, -1 as end replaces whole diagonal
  void setDiag(FLOAT s,int32_t i1=0,int32_t i2=-1);

  // clear MatICP
  void zero();
  
  // extract columns with given index
  MatICP extractCols (std::vector<int> idx);

  // create identity MatICP
  static MatICP eye (const int32_t m);
  void          eye ();

  // create MatICP with ones
  static MatICP ones(const int32_t m,const int32_t n);

  // create diagonal MatICP with nx1 or 1xn MatICP M as elements
  static MatICP diag(const MatICP &M);
  
  // returns the m-by-n MatICP whose elements are taken column-wise from M
  static MatICP reshape(const MatICP &M,int32_t m,int32_t n);

  // create 3x3 rotation matrices (convention: http://en.wikipedia.org/wiki/Rotation_MatICP)
  static MatICP rotMatX(const FLOAT &angle);
  static MatICP rotMatY(const FLOAT &angle);
  static MatICP rotMatZ(const FLOAT &angle);

  // simple arithmetic operations
  MatICP  operator+ (const MatICP &M); // add MatICP
  MatICP  operator- (const MatICP &M); // subtract MatICP
  MatICP  operator* (const MatICP &M); // multiply with MatICP
  MatICP  operator* (const FLOAT &s);  // multiply with scalar
  MatICP  operator/ (const MatICP &M); // divide elementwise by MatICP (or vector)
  MatICP  operator/ (const FLOAT &s);  // divide by scalar
  MatICP  operator- ();                // negative MatICP
  MatICP  operator~ ();                // transpose
  FLOAT   l2norm ();                   // euclidean norm (vectors) / frobenius norm (matrices)
  FLOAT   mean ();                     // mean of all elements in MatICP

  // complex arithmetic operations
  static MatICP cross (const MatICP &a, const MatICP &b);    // cross product of two vectors
  static MatICP inv (const MatICP &M);                       // invert MatICP M
  bool   inv ();                                             // invert this MatICP
  FLOAT  det ();                                             // returns determinant of MatICP
  bool   solve (const MatICP &M,FLOAT eps=1e-20);            // solve linear system M*x=B, replaces *this and M
  bool   lu(int32_t *idx, FLOAT &d, FLOAT eps=1e-20);        // replace *this by lower upper decomposition
  void   svd(MatICP &U,MatICP &W,MatICP &V);                 // singular value decomposition *this = U*diag(W)*V^T

  // print MatICP to stream
  friend std::ostream& operator<< (std::ostream& out,const MatICP& M);

  // direct data access
  FLOAT   **val;
  int32_t   m,n;

private:

  void allocateMemory (const int32_t m_,const int32_t n_);
  void releaseMemory ();
  inline FLOAT pythag(FLOAT a,FLOAT b);

};
}

#endif // MatICP_H
